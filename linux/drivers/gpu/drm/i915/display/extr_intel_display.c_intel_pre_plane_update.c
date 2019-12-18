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
struct TYPE_6__ {int /*<<< orphan*/  visible; } ;
struct intel_plane_state {TYPE_2__ base; } ;
struct TYPE_7__ {scalar_t__ active; struct drm_atomic_state* state; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {scalar_t__ update_wm_pre; TYPE_3__ base; scalar_t__ disable_lp_wm; scalar_t__ disable_cxsr; } ;
struct TYPE_5__ {struct drm_plane* primary; struct drm_device* dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_plane_state {scalar_t__ visible; } ;
struct drm_plane {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* initial_watermarks ) (struct intel_atomic_state*,struct intel_crtc_state*) ;} ;
struct drm_i915_private {TYPE_4__ display; } ;
struct drm_device {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_GMCH (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 struct drm_plane_state* drm_atomic_get_old_plane_state (struct drm_atomic_state*,struct drm_plane*) ; 
 int /*<<< orphan*/  hsw_disable_ips (struct intel_crtc_state*) ; 
 scalar_t__ hsw_pre_update_disable_ips (struct intel_crtc_state*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  icl_wa_scalerclkgating (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ilk_disable_lp_wm (struct drm_device*) ; 
 struct intel_plane_state* intel_atomic_get_new_plane_state (struct intel_atomic_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_fbc_pre_update (struct intel_crtc*,struct intel_crtc_state*,struct intel_plane_state*) ; 
 int /*<<< orphan*/  intel_set_cpu_fifo_underrun_reporting (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ intel_set_memory_cxsr (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  intel_update_watermarks (struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_wait_for_vblank (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int needs_modeset (struct intel_crtc_state*) ; 
 scalar_t__ needs_nv12_wa (struct drm_i915_private*,struct intel_crtc_state*) ; 
 scalar_t__ needs_scalerclk_wa (struct drm_i915_private*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  skl_wa_827 (struct drm_i915_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_plane (struct drm_plane*) ; 

__attribute__((used)) static void intel_pre_plane_update(struct intel_crtc_state *old_crtc_state,
				   struct intel_crtc_state *pipe_config)
{
	struct intel_crtc *crtc = to_intel_crtc(old_crtc_state->base.crtc);
	struct drm_device *dev = crtc->base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct drm_atomic_state *state = old_crtc_state->base.state;
	struct drm_plane *primary = crtc->base.primary;
	struct drm_plane_state *old_primary_state =
		drm_atomic_get_old_plane_state(state, primary);
	bool modeset = needs_modeset(pipe_config);
	struct intel_atomic_state *intel_state =
		to_intel_atomic_state(state);

	if (hsw_pre_update_disable_ips(old_crtc_state, pipe_config))
		hsw_disable_ips(old_crtc_state);

	if (old_primary_state) {
		struct intel_plane_state *new_primary_state =
			intel_atomic_get_new_plane_state(intel_state,
							 to_intel_plane(primary));

		intel_fbc_pre_update(crtc, pipe_config, new_primary_state);
		/*
		 * Gen2 reports pipe underruns whenever all planes are disabled.
		 * So disable underrun reporting before all the planes get disabled.
		 */
		if (IS_GEN(dev_priv, 2) && old_primary_state->visible &&
		    (modeset || !new_primary_state->base.visible))
			intel_set_cpu_fifo_underrun_reporting(dev_priv, crtc->pipe, false);
	}

	/* Display WA 827 */
	if (!needs_nv12_wa(dev_priv, old_crtc_state) &&
	    needs_nv12_wa(dev_priv, pipe_config))
		skl_wa_827(dev_priv, crtc->pipe, true);

	/* Wa_2006604312:icl */
	if (!needs_scalerclk_wa(dev_priv, old_crtc_state) &&
	    needs_scalerclk_wa(dev_priv, pipe_config))
		icl_wa_scalerclkgating(dev_priv, crtc->pipe, true);

	/*
	 * Vblank time updates from the shadow to live plane control register
	 * are blocked if the memory self-refresh mode is active at that
	 * moment. So to make sure the plane gets truly disabled, disable
	 * first the self-refresh mode. The self-refresh enable bit in turn
	 * will be checked/applied by the HW only at the next frame start
	 * event which is after the vblank start event, so we need to have a
	 * wait-for-vblank between disabling the plane and the pipe.
	 */
	if (HAS_GMCH(dev_priv) && old_crtc_state->base.active &&
	    pipe_config->disable_cxsr && intel_set_memory_cxsr(dev_priv, false))
		intel_wait_for_vblank(dev_priv, crtc->pipe);

	/*
	 * IVB workaround: must disable low power watermarks for at least
	 * one frame before enabling scaling.  LP watermarks can be re-enabled
	 * when scaling is disabled.
	 *
	 * WaCxSRDisabledForSpriteScaling:ivb
	 */
	if (pipe_config->disable_lp_wm && ilk_disable_lp_wm(dev) &&
	    old_crtc_state->base.active)
		intel_wait_for_vblank(dev_priv, crtc->pipe);

	/*
	 * If we're doing a modeset, we're done.  No need to do any pre-vblank
	 * watermark programming here.
	 */
	if (needs_modeset(pipe_config))
		return;

	/*
	 * For platforms that support atomic watermarks, program the
	 * 'intermediate' watermarks immediately.  On pre-gen9 platforms, these
	 * will be the intermediate values that are safe for both pre- and
	 * post- vblank; when vblank happens, the 'active' values will be set
	 * to the final 'target' values and we'll do this again to get the
	 * optimal watermarks.  For gen9+ platforms, the values we program here
	 * will be the final target values which will get automatically latched
	 * at vblank time; no further programming will be necessary.
	 *
	 * If a platform hasn't been transitioned to atomic watermarks yet,
	 * we'll continue to update watermarks the old way, if flags tell
	 * us to.
	 */
	if (dev_priv->display.initial_watermarks != NULL)
		dev_priv->display.initial_watermarks(intel_state,
						     pipe_config);
	else if (pipe_config->update_wm_pre)
		intel_update_watermarks(crtc);
}