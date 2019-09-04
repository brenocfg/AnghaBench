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
struct intel_dp {char** psr_dpcd; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {scalar_t__ port; TYPE_1__ base; } ;
struct intel_digital_port {TYPE_3__ base; } ;
struct drm_display_mode {int flags; int crtc_vtotal; int crtc_vdisplay; } ;
struct TYPE_6__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int has_psr; scalar_t__ has_psr2; int /*<<< orphan*/  cpu_transcoder; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  enable_psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int /*<<< orphan*/  HSW_STEREO_3D_CTL (int /*<<< orphan*/ ) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ PORT_A ; 
 int S3D_ENABLE ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int drm_dp_psr_setup_time (char**) ; 
 TYPE_4__ i915_modparams ; 
 scalar_t__ intel_psr2_config_valid (struct intel_dp*,struct intel_crtc_state*) ; 
 int intel_usecs_to_scanlines (struct drm_display_mode const*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

void intel_psr_compute_config(struct intel_dp *intel_dp,
			      struct intel_crtc_state *crtc_state)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv = to_i915(dig_port->base.base.dev);
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;
	int psr_setup_time;

	if (!CAN_PSR(dev_priv))
		return;

	if (!i915_modparams.enable_psr) {
		DRM_DEBUG_KMS("PSR disable by flag\n");
		return;
	}

	/*
	 * HSW spec explicitly says PSR is tied to port A.
	 * BDW+ platforms with DDI implementation of PSR have different
	 * PSR registers per transcoder and we only implement transcoder EDP
	 * ones. Since by Display design transcoder EDP is tied to port A
	 * we can safely escape based on the port A.
	 */
	if (dig_port->base.port != PORT_A) {
		DRM_DEBUG_KMS("PSR condition failed: Port not supported\n");
		return;
	}

	if (IS_HASWELL(dev_priv) &&
	    I915_READ(HSW_STEREO_3D_CTL(crtc_state->cpu_transcoder)) &
		      S3D_ENABLE) {
		DRM_DEBUG_KMS("PSR condition failed: Stereo 3D is Enabled\n");
		return;
	}

	if (IS_HASWELL(dev_priv) &&
	    adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) {
		DRM_DEBUG_KMS("PSR condition failed: Interlaced is Enabled\n");
		return;
	}

	psr_setup_time = drm_dp_psr_setup_time(intel_dp->psr_dpcd);
	if (psr_setup_time < 0) {
		DRM_DEBUG_KMS("PSR condition failed: Invalid PSR setup time (0x%02x)\n",
			      intel_dp->psr_dpcd[1]);
		return;
	}

	if (intel_usecs_to_scanlines(adjusted_mode, psr_setup_time) >
	    adjusted_mode->crtc_vtotal - adjusted_mode->crtc_vdisplay - 1) {
		DRM_DEBUG_KMS("PSR condition failed: PSR setup time (%d us) too long\n",
			      psr_setup_time);
		return;
	}

	crtc_state->has_psr = true;
	crtc_state->has_psr2 = intel_psr2_config_valid(intel_dp, crtc_state);
	DRM_DEBUG_KMS("Enabling PSR%s\n", crtc_state->has_psr2 ? "2" : "");
}