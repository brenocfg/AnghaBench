#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_3__* color_plane; TYPE_1__ base; } ;
struct drm_framebuffer {TYPE_2__* format; } ;
struct TYPE_6__ {int x; int y; scalar_t__ offset; } ;
struct TYPE_5__ {int hsub; int vsub; } ;

/* Variables and functions */
 scalar_t__ intel_plane_adjust_aligned_offset (int*,int*,struct intel_plane_state*,int,scalar_t__,scalar_t__) ; 
 scalar_t__ intel_surf_alignment (struct drm_framebuffer const*,int) ; 

__attribute__((used)) static bool skl_check_main_ccs_coordinates(struct intel_plane_state *plane_state,
					   int main_x, int main_y, u32 main_offset)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	int hsub = fb->format->hsub;
	int vsub = fb->format->vsub;
	int aux_x = plane_state->color_plane[1].x;
	int aux_y = plane_state->color_plane[1].y;
	u32 aux_offset = plane_state->color_plane[1].offset;
	u32 alignment = intel_surf_alignment(fb, 1);

	while (aux_offset >= main_offset && aux_y <= main_y) {
		int x, y;

		if (aux_x == main_x && aux_y == main_y)
			break;

		if (aux_offset == 0)
			break;

		x = aux_x / hsub;
		y = aux_y / vsub;
		aux_offset = intel_plane_adjust_aligned_offset(&x, &y, plane_state, 1,
							       aux_offset, aux_offset - alignment);
		aux_x = x * hsub + aux_x % hsub;
		aux_y = y * vsub + aux_y % vsub;
	}

	if (aux_x != main_x || aux_y != main_y)
		return false;

	plane_state->color_plane[1].offset = aux_offset;
	plane_state->color_plane[1].x = aux_x;
	plane_state->color_plane[1].y = aux_y;

	return true;
}