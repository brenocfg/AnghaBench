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
struct TYPE_6__ {scalar_t__ enabled; } ;
struct TYPE_5__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int pipe_src_w; int pipe_src_h; TYPE_3__ pch_pfit; TYPE_2__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  dev; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; TYPE_1__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ HAS_PCH_SPLIT (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  PIPESRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icl_set_pipe_chicken (struct intel_crtc*) ; 
 int /*<<< orphan*/  ironlake_pfit_disable (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  ironlake_pfit_enable (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  skl_detach_scalers (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  skylake_pfit_enable (struct intel_crtc_state const*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_update_pipe_config(const struct intel_crtc_state *old_crtc_state,
				     const struct intel_crtc_state *new_crtc_state)
{
	struct intel_crtc *crtc = to_intel_crtc(new_crtc_state->base.crtc);
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);

	/* drm_atomic_helper_update_legacy_modeset_state might not be called. */
	crtc->base.mode = new_crtc_state->base.mode;

	/*
	 * Update pipe size and adjust fitter if needed: the reason for this is
	 * that in compute_mode_changes we check the native mode (not the pfit
	 * mode) to see if we can flip rather than do a full mode set. In the
	 * fastboot case, we'll flip, but if we don't update the pipesrc and
	 * pfit state, we'll end up with a big fb scanned out into the wrong
	 * sized surface.
	 */

	I915_WRITE(PIPESRC(crtc->pipe),
		   ((new_crtc_state->pipe_src_w - 1) << 16) |
		   (new_crtc_state->pipe_src_h - 1));

	/* on skylake this is done by detaching scalers */
	if (INTEL_GEN(dev_priv) >= 9) {
		skl_detach_scalers(new_crtc_state);

		if (new_crtc_state->pch_pfit.enabled)
			skylake_pfit_enable(new_crtc_state);
	} else if (HAS_PCH_SPLIT(dev_priv)) {
		if (new_crtc_state->pch_pfit.enabled)
			ironlake_pfit_enable(new_crtc_state);
		else if (old_crtc_state->pch_pfit.enabled)
			ironlake_pfit_disable(old_crtc_state);
	}

	if (INTEL_GEN(dev_priv) >= 11)
		icl_set_pipe_chicken(crtc);
}