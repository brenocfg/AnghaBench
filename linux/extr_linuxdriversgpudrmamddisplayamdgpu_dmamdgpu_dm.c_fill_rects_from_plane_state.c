#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_plane_state {int src_x; int src_y; int src_w; int src_h; scalar_t__ crtc_w; scalar_t__ crtc_h; int rotation; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; } ;
struct TYPE_4__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_3__ {int x; int y; int width; int height; } ;
struct dc_plane_state {void* rotation; TYPE_2__ dst_rect; TYPE_2__ clip_rect; TYPE_1__ src_rect; } ;

/* Variables and functions */
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 int DRM_MODE_ROTATE_MASK ; 
 void* ROTATION_ANGLE_0 ; 
 void* ROTATION_ANGLE_180 ; 
 void* ROTATION_ANGLE_270 ; 
 void* ROTATION_ANGLE_90 ; 

__attribute__((used)) static bool fill_rects_from_plane_state(const struct drm_plane_state *state,
					struct dc_plane_state *plane_state)
{
	plane_state->src_rect.x = state->src_x >> 16;
	plane_state->src_rect.y = state->src_y >> 16;
	/*we ignore for now mantissa and do not to deal with floating pixels :(*/
	plane_state->src_rect.width = state->src_w >> 16;

	if (plane_state->src_rect.width == 0)
		return false;

	plane_state->src_rect.height = state->src_h >> 16;
	if (plane_state->src_rect.height == 0)
		return false;

	plane_state->dst_rect.x = state->crtc_x;
	plane_state->dst_rect.y = state->crtc_y;

	if (state->crtc_w == 0)
		return false;

	plane_state->dst_rect.width = state->crtc_w;

	if (state->crtc_h == 0)
		return false;

	plane_state->dst_rect.height = state->crtc_h;

	plane_state->clip_rect = plane_state->dst_rect;

	switch (state->rotation & DRM_MODE_ROTATE_MASK) {
	case DRM_MODE_ROTATE_0:
		plane_state->rotation = ROTATION_ANGLE_0;
		break;
	case DRM_MODE_ROTATE_90:
		plane_state->rotation = ROTATION_ANGLE_90;
		break;
	case DRM_MODE_ROTATE_180:
		plane_state->rotation = ROTATION_ANGLE_180;
		break;
	case DRM_MODE_ROTATE_270:
		plane_state->rotation = ROTATION_ANGLE_270;
		break;
	default:
		plane_state->rotation = ROTATION_ANGLE_0;
		break;
	}

	return true;
}