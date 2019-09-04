#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_lspcon {scalar_t__ active; } ;
struct intel_dp {int reset_link_params; int /*<<< orphan*/  active_pipe; int /*<<< orphan*/  output_reg; int /*<<< orphan*/  DP; } ;
struct drm_i915_private {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAS_DDI (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 struct intel_lspcon* dp_to_lspcon (struct intel_dp*) ; 
 struct intel_dp* enc_to_intel_dp (struct drm_encoder*) ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_pps_init (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_edp_panel_vdd_sanitize (struct intel_dp*) ; 
 int /*<<< orphan*/  lspcon_resume (struct intel_lspcon*) ; 
 int /*<<< orphan*/  pps_lock (struct intel_dp*) ; 
 int /*<<< orphan*/  pps_unlock (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_active_pipe (struct intel_dp*) ; 

void intel_dp_encoder_reset(struct drm_encoder *encoder)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->dev);
	struct intel_dp *intel_dp = enc_to_intel_dp(encoder);
	struct intel_lspcon *lspcon = dp_to_lspcon(intel_dp);

	if (!HAS_DDI(dev_priv))
		intel_dp->DP = I915_READ(intel_dp->output_reg);

	if (lspcon->active)
		lspcon_resume(lspcon);

	intel_dp->reset_link_params = true;

	pps_lock(intel_dp);

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		intel_dp->active_pipe = vlv_active_pipe(intel_dp);

	if (intel_dp_is_edp(intel_dp)) {
		/* Reinit the power sequencer, in case BIOS did something with it. */
		intel_dp_pps_init(intel_dp);
		intel_edp_panel_vdd_sanitize(intel_dp);
	}

	pps_unlock(intel_dp);
}