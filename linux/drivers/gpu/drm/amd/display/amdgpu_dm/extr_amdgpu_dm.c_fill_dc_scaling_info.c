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
struct drm_plane_state {int src_x; int src_y; int src_w; int src_h; scalar_t__ crtc_w; scalar_t__ crtc_h; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; } ;
struct TYPE_4__ {int x; int y; int width; int height; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct dc_scaling_info {TYPE_2__ src_rect; TYPE_1__ dst_rect; TYPE_1__ clip_rect; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (struct dc_scaling_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fill_dc_scaling_info(const struct drm_plane_state *state,
				struct dc_scaling_info *scaling_info)
{
	int scale_w, scale_h;

	memset(scaling_info, 0, sizeof(*scaling_info));

	/* Source is fixed 16.16 but we ignore mantissa for now... */
	scaling_info->src_rect.x = state->src_x >> 16;
	scaling_info->src_rect.y = state->src_y >> 16;

	scaling_info->src_rect.width = state->src_w >> 16;
	if (scaling_info->src_rect.width == 0)
		return -EINVAL;

	scaling_info->src_rect.height = state->src_h >> 16;
	if (scaling_info->src_rect.height == 0)
		return -EINVAL;

	scaling_info->dst_rect.x = state->crtc_x;
	scaling_info->dst_rect.y = state->crtc_y;

	if (state->crtc_w == 0)
		return -EINVAL;

	scaling_info->dst_rect.width = state->crtc_w;

	if (state->crtc_h == 0)
		return -EINVAL;

	scaling_info->dst_rect.height = state->crtc_h;

	/* DRM doesn't specify clipping on destination output. */
	scaling_info->clip_rect = scaling_info->dst_rect;

	/* TODO: Validate scaling per-format with DC plane caps */
	scale_w = scaling_info->dst_rect.width * 1000 /
		  scaling_info->src_rect.width;

	if (scale_w < 250 || scale_w > 16000)
		return -EINVAL;

	scale_h = scaling_info->dst_rect.height * 1000 /
		  scaling_info->src_rect.height;

	if (scale_h < 250 || scale_h > 16000)
		return -EINVAL;

	/*
	 * The "scaling_quality" can be ignored for now, quality = 0 has DC
	 * assume reasonable defaults based on the format.
	 */

	return 0;
}