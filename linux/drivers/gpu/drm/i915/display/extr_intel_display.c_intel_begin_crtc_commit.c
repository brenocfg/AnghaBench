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
struct TYPE_4__ {scalar_t__ color_mgmt_changed; } ;
struct intel_crtc_state {scalar_t__ update_pipe; TYPE_1__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_crtc {TYPE_3__ base; } ;
struct intel_atomic_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* atomic_update_watermarks ) (struct intel_atomic_state*,struct intel_crtc_state*) ;} ;
struct drm_i915_private {TYPE_2__ display; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bdw_set_pipemisc (struct intel_crtc_state*) ; 
 struct intel_crtc_state* intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 struct intel_crtc_state* intel_atomic_get_old_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 int /*<<< orphan*/  intel_color_commit (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_pipe_update_start (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_update_pipe_config (struct intel_crtc_state*,struct intel_crtc_state*) ; 
 int needs_modeset (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  skl_detach_scalers (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  stub1 (struct intel_atomic_state*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_begin_crtc_commit(struct intel_atomic_state *state,
				    struct intel_crtc *crtc)
{
	struct drm_i915_private *dev_priv = to_i915(crtc->base.dev);
	struct intel_crtc_state *old_crtc_state =
		intel_atomic_get_old_crtc_state(state, crtc);
	struct intel_crtc_state *new_crtc_state =
		intel_atomic_get_new_crtc_state(state, crtc);
	bool modeset = needs_modeset(new_crtc_state);

	/* Perform vblank evasion around commit operation */
	intel_pipe_update_start(new_crtc_state);

	if (modeset)
		goto out;

	if (new_crtc_state->base.color_mgmt_changed ||
	    new_crtc_state->update_pipe)
		intel_color_commit(new_crtc_state);

	if (new_crtc_state->update_pipe)
		intel_update_pipe_config(old_crtc_state, new_crtc_state);
	else if (INTEL_GEN(dev_priv) >= 9)
		skl_detach_scalers(new_crtc_state);

	if (INTEL_GEN(dev_priv) >= 9 || IS_BROADWELL(dev_priv))
		bdw_set_pipemisc(new_crtc_state);

out:
	if (dev_priv->display.atomic_update_watermarks)
		dev_priv->display.atomic_update_watermarks(state,
							   new_crtc_state);
}