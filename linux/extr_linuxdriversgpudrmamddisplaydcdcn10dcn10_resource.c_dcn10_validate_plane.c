#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ width; } ;
struct dc_plane_state {scalar_t__ format; TYPE_1__ src_rect; } ;
struct dc_caps {scalar_t__ max_video_width; } ;
typedef  enum dc_status { ____Placeholder_dc_status } dc_status ;

/* Variables and functions */
 int DC_FAIL_SURFACE_VALIDATE ; 
 int DC_OK ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 

__attribute__((used)) static enum dc_status dcn10_validate_plane(const struct dc_plane_state *plane_state, struct dc_caps *caps)
{
	if (plane_state->format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN
			&& caps->max_video_width != 0
			&& plane_state->src_rect.width > caps->max_video_width)
		return DC_FAIL_SURFACE_VALIDATE;

	return DC_OK;
}