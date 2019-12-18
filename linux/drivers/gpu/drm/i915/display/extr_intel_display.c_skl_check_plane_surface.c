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
struct TYPE_6__ {int /*<<< orphan*/  visible; struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_2__* color_plane; TYPE_3__ base; } ;
struct drm_framebuffer {int /*<<< orphan*/  modifier; TYPE_1__* format; } ;
struct TYPE_5__ {int offset; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int intel_plane_compute_gtt (struct intel_plane_state*) ; 
 scalar_t__ is_ccs_modifier (int /*<<< orphan*/ ) ; 
 scalar_t__ is_planar_yuv_format (int /*<<< orphan*/ ) ; 
 int skl_check_ccs_aux_surface (struct intel_plane_state*) ; 
 int skl_check_main_surface (struct intel_plane_state*) ; 
 int skl_check_nv12_aux_surface (struct intel_plane_state*) ; 

int skl_check_plane_surface(struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;
	int ret;

	ret = intel_plane_compute_gtt(plane_state);
	if (ret)
		return ret;

	if (!plane_state->base.visible)
		return 0;

	/*
	 * Handle the AUX surface first since
	 * the main surface setup depends on it.
	 */
	if (is_planar_yuv_format(fb->format->format)) {
		ret = skl_check_nv12_aux_surface(plane_state);
		if (ret)
			return ret;
	} else if (is_ccs_modifier(fb->modifier)) {
		ret = skl_check_ccs_aux_surface(plane_state);
		if (ret)
			return ret;
	} else {
		plane_state->color_plane[1].offset = ~0xfff;
		plane_state->color_plane[1].x = 0;
		plane_state->color_plane[1].y = 0;
	}

	ret = skl_check_main_surface(plane_state);
	if (ret)
		return ret;

	return 0;
}