#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ color_mgmt_changed; } ;
struct intel_crtc_state {scalar_t__ update_pipe; TYPE_2__ base; } ;
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* atomic_update_watermarks ) (struct intel_atomic_state*,struct intel_crtc_state*) ;} ;
struct drm_i915_private {TYPE_1__ display; } ;
struct drm_device {int dummy; } ;
struct drm_crtc_state {int /*<<< orphan*/  state; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_color_load_luts (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_color_set_csc (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_pipe_update_start (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_update_pipe_config (struct intel_crtc_state*,struct intel_crtc_state*) ; 
 int needs_modeset (TYPE_2__*) ; 
 int /*<<< orphan*/  skl_detach_scalers (struct intel_crtc*) ; 
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 
 struct intel_atomic_state* to_intel_atomic_state (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (struct drm_crtc*) ; 
 struct intel_crtc_state* to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static void intel_begin_crtc_commit(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_crtc_state)
{
	struct drm_device *dev = crtc->dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc);
	struct intel_crtc_state *old_intel_cstate =
		to_intel_crtc_state(old_crtc_state);
	struct intel_atomic_state *old_intel_state =
		to_intel_atomic_state(old_crtc_state->state);
	struct intel_crtc_state *intel_cstate =
		intel_atomic_get_new_crtc_state(old_intel_state, intel_crtc);
	bool modeset = needs_modeset(&intel_cstate->base);

	if (!modeset &&
	    (intel_cstate->base.color_mgmt_changed ||
	     intel_cstate->update_pipe)) {
		intel_color_set_csc(&intel_cstate->base);
		intel_color_load_luts(&intel_cstate->base);
	}

	/* Perform vblank evasion around commit operation */
	intel_pipe_update_start(intel_cstate);

	if (modeset)
		goto out;

	if (intel_cstate->update_pipe)
		intel_update_pipe_config(old_intel_cstate, intel_cstate);
	else if (INTEL_GEN(dev_priv) >= 9)
		skl_detach_scalers(intel_crtc);

out:
	if (dev_priv->display.atomic_update_watermarks)
		dev_priv->display.atomic_update_watermarks(old_intel_state,
							   intel_cstate);
}