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
struct TYPE_4__ {int /*<<< orphan*/  visible; int /*<<< orphan*/  fb; int /*<<< orphan*/  plane; } ;
struct intel_plane_state {int /*<<< orphan*/  ctl; TYPE_2__ base; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {TYPE_1__ base; } ;
struct intel_crtc_state {int /*<<< orphan*/  base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DRM_PLANE_HELPER_NO_SCALING ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 int drm_atomic_helper_check_plane_state (TYPE_2__*,int /*<<< orphan*/ *,int,int,int,int) ; 
 int g4x_sprite_check_scaling (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int /*<<< orphan*/  g4x_sprite_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int i9xx_check_plane_surface (struct intel_plane_state*) ; 
 scalar_t__ intel_fb_scalable (int /*<<< orphan*/ ) ; 
 int intel_plane_check_src_coordinates (struct intel_plane_state*) ; 
 int /*<<< orphan*/  ivb_sprite_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_plane* to_intel_plane (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g4x_sprite_check(struct intel_crtc_state *crtc_state,
		 struct intel_plane_state *plane_state)
{
	struct intel_plane *plane = to_intel_plane(plane_state->base.plane);
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	int min_scale = DRM_PLANE_HELPER_NO_SCALING;
	int max_scale = DRM_PLANE_HELPER_NO_SCALING;
	int ret;

	if (intel_fb_scalable(plane_state->base.fb)) {
		if (INTEL_GEN(dev_priv) < 7) {
			min_scale = 1;
			max_scale = 16 << 16;
		} else if (IS_IVYBRIDGE(dev_priv)) {
			min_scale = 1;
			max_scale = 2 << 16;
		}
	}

	ret = drm_atomic_helper_check_plane_state(&plane_state->base,
						  &crtc_state->base,
						  min_scale, max_scale,
						  true, true);
	if (ret)
		return ret;

	ret = i9xx_check_plane_surface(plane_state);
	if (ret)
		return ret;

	if (!plane_state->base.visible)
		return 0;

	ret = intel_plane_check_src_coordinates(plane_state);
	if (ret)
		return ret;

	ret = g4x_sprite_check_scaling(crtc_state, plane_state);
	if (ret)
		return ret;

	if (INTEL_GEN(dev_priv) >= 7)
		plane_state->ctl = ivb_sprite_ctl(crtc_state, plane_state);
	else
		plane_state->ctl = g4x_sprite_ctl(crtc_state, plane_state);

	return 0;
}