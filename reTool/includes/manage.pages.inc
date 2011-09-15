<?php

/**
 * Menu callback for project/%/manage/tools
 */
function project_manage_tools_list_callback($path){
    $project = load_project($path);
    if($project){
        drupal_add_css(drupal_get_path('module','reProject').'/css/manage.css');
        
        //get right part info
        $content = '<a href="'.url('project/'.$path.'/manage/tools/selete').'" class="add_link">Add new tool</a>';
        $rows = array();
        $header = array(
            array('data'=>'Tool'),
            array('data'=>'Name'),
            array('data'=>'Operation'),
        );
        
        $sql = "SELECT t.id id, t.name, t.logo FROM {research_project_tools_list} AS p, {research_tools} AS t WHERE p.project=%d AND p.tool=t.id";
        $res = db_query($sql, $project->id);
        while($row=db_fetch_object($res)){
            $rows[] = array(
                "<image src='{$row->logo}' width='100px' />",
                "<a href='".url('research/tools/view/'.$row->id)."' target='_blank'>{$row->name}</a>",
                "<a href='' class='delete_link'>Remove</a>",
            );
        }
        $content.= theme_table($header, $rows);
        $content.= theme('pager');
        $project->subtitle = 'Tools management';
        $project->right_part = $content;    
        return theme('project_manage_page',$project);
    }
    drupal_not_found();
}

/**
 * Menu callback for project/%/manage/tools/selete
 */
function project_manage_tools_selete_list_callback($path){
    $project = load_project($path);
    if($project){
        drupal_add_css(drupal_get_path('module','reProject').'/css/manage.css');
        
        //get right part info
        $rows = array();
        $header = array(
            array('data'=>'Tool'),
            array('data'=>'Name'),
            array('data'=>'Operation'),
        );
        
        $sql = "SELECT t.id id, t.name, t.logo FROM {research_tools} AS t ORDER BY t.changed DESC";
        $res = db_query($sql);
        while($row=db_fetch_object($res)){
            $rows[] = array(
                "<image src='{$row->logo}' width='100px' />",
                "<a href='".url('research/tools/view/'.$row->id)."' target='_blank'>{$row->name}</a>",
                "<a href='".url("project/$path/manage/tools/selete/{$row->id}")."' class='add_link'>Add to project</a>",
            );
        }
        $content.= theme_table($header, $rows);
        $content.= theme('pager');
        $project->subtitle = 'Tools management';
        $project->right_part = $content;    
        return theme('project_manage_page',$project);
    }
    drupal_not_found();
}

/**
 * Menu callback for project/%/manage/tools/selete/%
 */
function project_manage_tools_selete_new_callback($path, $id){
    $project = load_project($path);
    if($project){
        project_bind_tool($project, $id);
        drupal_goto('project/'.$path.'/manage/tools');
    }
    drupal_not_found();
}