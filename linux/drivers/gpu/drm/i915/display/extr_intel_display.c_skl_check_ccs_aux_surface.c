#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int x1; int y1; } ;
struct TYPE_6__ {TYPE_1__ src; struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_4__* color_plane; TYPE_2__ base; } ;
struct drm_framebuffer {TYPE_3__* format; } ;
struct TYPE_8__ {int x; int y; int /*<<< orphan*/  offset; } ;
struct TYPE_7__ {int hsub; int vsub; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_add_fb_offsets (int*,int*,struct intel_plane_state*,int) ; 
 int /*<<< orphan*/  intel_plane_compute_aligned_offset (int*,int*,struct intel_plane_state*,int) ; 

__attribute__((used)) static int skl_check_ccs_aux_surface(struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	int src_x = plane_state->base.src.x1 >> 16;
	int src_y = plane_state->base.src.y1 >> 16;
	int hsub = fb->format->hsub;
	int vsub = fb->format->vsub;
	int x = src_x / hsub;
	int y = src_y / vsub;
	u32 offset;

	intel_add_fb_offsets(&x, &y, plane_state, 1);
	offset = intel_plane_compute_aligned_offset(&x, &y, plane_state, 1);

	plane_state->color_plane[1].offset = offset;
	plane_state->color_plane[1].x = x * hsub + src_x % hsub;
	plane_state->color_plane[1].y = y * vsub + src_y % vsub;

	return 0;
}