#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {TYPE_4__* fb; struct drm_crtc* crtc; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct intel_plane_state {int /*<<< orphan*/  color_ctl; int /*<<< orphan*/  ctl; TYPE_5__ base; TYPE_2__ ckey; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {TYPE_1__ base; } ;
struct intel_crtc_state {int /*<<< orphan*/  base; } ;
struct drm_i915_private {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_9__ {TYPE_3__* format; } ;
struct TYPE_8__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int DRM_PLANE_HELPER_NO_SCALING ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 int drm_atomic_helper_check_plane_state (TYPE_5__*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  glk_plane_color_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int i9xx_check_plane_surface (struct intel_plane_state*) ; 
 int /*<<< orphan*/  i9xx_plane_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int skl_check_plane_surface (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int skl_max_scale (int /*<<< orphan*/ ,struct intel_crtc_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skl_plane_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int
intel_check_primary_plane(struct intel_plane *plane,
			  struct intel_crtc_state *crtc_state,
			  struct intel_plane_state *state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	struct drm_crtc *crtc = state->base.crtc;
	int min_scale = DRM_PLANE_HELPER_NO_SCALING;
	int max_scale = DRM_PLANE_HELPER_NO_SCALING;
	bool can_position = false;
	int ret;
	uint32_t pixel_format = 0;

	if (INTEL_GEN(dev_priv) >= 9) {
		/* use scaler when colorkey is not required */
		if (!state->ckey.flags) {
			min_scale = 1;
			if (state->base.fb)
				pixel_format = state->base.fb->format->format;
			max_scale = skl_max_scale(to_intel_crtc(crtc),
						  crtc_state, pixel_format);
		}
		can_position = true;
	}

	ret = drm_atomic_helper_check_plane_state(&state->base,
						  &crtc_state->base,
						  min_scale, max_scale,
						  can_position, true);
	if (ret)
		return ret;

	if (!state->base.fb)
		return 0;

	if (INTEL_GEN(dev_priv) >= 9) {
		ret = skl_check_plane_surface(crtc_state, state);
		if (ret)
			return ret;

		state->ctl = skl_plane_ctl(crtc_state, state);
	} else {
		ret = i9xx_check_plane_surface(state);
		if (ret)
			return ret;

		state->ctl = i9xx_plane_ctl(crtc_state, state);
	}

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		state->color_ctl = glk_plane_color_ctl(crtc_state, state);

	return 0;
}