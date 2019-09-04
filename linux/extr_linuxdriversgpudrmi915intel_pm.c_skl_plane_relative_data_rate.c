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
typedef  int /*<<< orphan*/  uint_fixed_16_16_t ;
typedef  int uint32_t ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  src; int /*<<< orphan*/  visible; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct intel_plane {scalar_t__ id; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_plane_state {struct drm_framebuffer* fb; int /*<<< orphan*/  plane; } ;
struct drm_framebuffer {TYPE_2__* format; } ;
struct TYPE_4__ {scalar_t__ format; int* cpp; } ;

/* Variables and functions */
 scalar_t__ DRM_FORMAT_NV12 ; 
 scalar_t__ PLANE_CURSOR ; 
 int drm_rect_height (int /*<<< orphan*/ *) ; 
 int drm_rect_width (int /*<<< orphan*/ *) ; 
 unsigned int mul_round_up_u32_fixed16 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_plane_downscale_amount (struct intel_crtc_state const*,struct intel_plane_state*) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 
 struct intel_plane_state* to_intel_plane_state (struct drm_plane_state const*) ; 

__attribute__((used)) static unsigned int
skl_plane_relative_data_rate(const struct intel_crtc_state *cstate,
			     const struct drm_plane_state *pstate,
			     const int plane)
{
	struct intel_plane *intel_plane = to_intel_plane(pstate->plane);
	struct intel_plane_state *intel_pstate = to_intel_plane_state(pstate);
	uint32_t data_rate;
	uint32_t width = 0, height = 0;
	struct drm_framebuffer *fb;
	u32 format;
	uint_fixed_16_16_t down_scale_amount;

	if (!intel_pstate->base.visible)
		return 0;

	fb = pstate->fb;
	format = fb->format->format;

	if (intel_plane->id == PLANE_CURSOR)
		return 0;
	if (plane == 1 && format != DRM_FORMAT_NV12)
		return 0;

	/*
	 * Src coordinates are already rotated by 270 degrees for
	 * the 90/270 degree plane rotation cases (to match the
	 * GTT mapping), hence no need to account for rotation here.
	 */
	width = drm_rect_width(&intel_pstate->base.src) >> 16;
	height = drm_rect_height(&intel_pstate->base.src) >> 16;

	/* UV plane does 1/2 pixel sub-sampling */
	if (plane == 1 && format == DRM_FORMAT_NV12) {
		width /= 2;
		height /= 2;
	}

	data_rate = width * height * fb->format->cpp[plane];

	down_scale_amount = skl_plane_downscale_amount(cstate, intel_pstate);

	return mul_round_up_u32_fixed16(data_rate, down_scale_amount);
}