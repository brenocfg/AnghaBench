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
struct TYPE_3__ {scalar_t__ active; struct drm_atomic_state* state; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_1__ base; scalar_t__ update_wm_post; int /*<<< orphan*/  fb_bits; } ;
struct TYPE_4__ {struct drm_device* dev; struct drm_plane* primary; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_2__ base; } ;
struct drm_plane_state {scalar_t__ visible; } ;
struct drm_plane {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 struct drm_plane_state* drm_atomic_get_new_plane_state (struct drm_atomic_state*,struct drm_plane*) ; 
 struct drm_plane_state* drm_atomic_get_old_plane_state (struct drm_atomic_state*,struct drm_plane*) ; 
 int /*<<< orphan*/  hsw_enable_ips (struct intel_crtc_state*) ; 
 scalar_t__ hsw_post_update_enable_ips (struct intel_crtc_state*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  icl_wa_scalerclkgating (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (int /*<<< orphan*/ ,struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_fbc_post_update (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_frontbuffer_flip (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_post_enable_primary (TYPE_2__*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_update_watermarks (struct intel_crtc*) ; 
 scalar_t__ needs_modeset (struct intel_crtc_state*) ; 
 scalar_t__ needs_nv12_wa (struct drm_i915_private*,struct intel_crtc_state*) ; 
 scalar_t__ needs_scalerclk_wa (struct drm_i915_private*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  skl_wa_827 (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 int /*<<< orphan*/  to_intel_atomic_state (struct drm_atomic_state*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_post_plane_update(struct intel_crtc_state *old_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(old_crtc_state->base.crtc);
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_atomic_state *state = old_crtc_state->base.state;
	struct intel_crtc_state *pipe_config =
		intel_atomic_get_new_crtc_state(to_intel_atomic_state(state),
						crtc);
	struct drm_plane *primary = crtc->base.primary;
	struct drm_plane_state *old_primary_state =
		drm_atomic_get_old_plane_state(state, primary);

	intel_frontbuffer_flip(to_i915(crtc->base.dev), pipe_config->fb_bits);

	if (pipe_config->update_wm_post && pipe_config->base.active)
		intel_update_watermarks(crtc);

	if (hsw_post_update_enable_ips(old_crtc_state, pipe_config))
		hsw_enable_ips(pipe_config);

	if (old_primary_state) {
		struct drm_plane_state *new_primary_state =
			drm_atomic_get_new_plane_state(state, primary);

		intel_fbc_post_update(crtc);

		if (new_primary_state->visible &&
		    (needs_modeset(pipe_config) ||
		     !old_primary_state->visible))
			intel_post_enable_primary(&crtc->base, pipe_config);
	}

	if (needs_nv12_wa(dev_priv, old_crtc_state) &&
	    !needs_nv12_wa(dev_priv, pipe_config))
		skl_wa_827(dev_priv, crtc->pipe, false);

	if (needs_scalerclk_wa(dev_priv, old_crtc_state) &&
	    !needs_scalerclk_wa(dev_priv, pipe_config))
		icl_wa_scalerclkgating(dev_priv, crtc->pipe, false);
}