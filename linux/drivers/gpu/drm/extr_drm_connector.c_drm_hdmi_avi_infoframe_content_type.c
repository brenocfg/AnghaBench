#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hdmi_avi_infoframe {int itc; void* content_type; } ;
struct drm_connector_state {int content_type; } ;

/* Variables and functions */
#define  DRM_MODE_CONTENT_TYPE_CINEMA 131 
#define  DRM_MODE_CONTENT_TYPE_GAME 130 
#define  DRM_MODE_CONTENT_TYPE_GRAPHICS 129 
 int DRM_MODE_CONTENT_TYPE_NO_DATA ; 
#define  DRM_MODE_CONTENT_TYPE_PHOTO 128 
 void* HDMI_CONTENT_TYPE_CINEMA ; 
 void* HDMI_CONTENT_TYPE_GAME ; 
 void* HDMI_CONTENT_TYPE_GRAPHICS ; 
 void* HDMI_CONTENT_TYPE_PHOTO ; 

void drm_hdmi_avi_infoframe_content_type(struct hdmi_avi_infoframe *frame,
					 const struct drm_connector_state *conn_state)
{
	switch (conn_state->content_type) {
	case DRM_MODE_CONTENT_TYPE_GRAPHICS:
		frame->content_type = HDMI_CONTENT_TYPE_GRAPHICS;
		break;
	case DRM_MODE_CONTENT_TYPE_CINEMA:
		frame->content_type = HDMI_CONTENT_TYPE_CINEMA;
		break;
	case DRM_MODE_CONTENT_TYPE_GAME:
		frame->content_type = HDMI_CONTENT_TYPE_GAME;
		break;
	case DRM_MODE_CONTENT_TYPE_PHOTO:
		frame->content_type = HDMI_CONTENT_TYPE_PHOTO;
		break;
	default:
		/* Graphics is the default(0) */
		frame->content_type = HDMI_CONTENT_TYPE_GRAPHICS;
	}

	frame->itc = conn_state->content_type != DRM_MODE_CONTENT_TYPE_NO_DATA;
}