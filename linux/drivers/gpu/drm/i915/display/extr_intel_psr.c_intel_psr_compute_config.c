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
struct intel_dp {int* psr_dpcd; } ;
struct TYPE_5__ {scalar_t__ port; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct drm_display_mode {int flags; int crtc_vtotal; int crtc_vdisplay; } ;
struct TYPE_4__ {struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {int has_psr; int /*<<< orphan*/  has_psr2; TYPE_1__ base; } ;
struct TYPE_6__ {scalar_t__ sink_not_reliable; struct intel_dp* dp; } ;
struct drm_i915_private {TYPE_3__ psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ PORT_A ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int drm_dp_psr_setup_time (int*) ; 
 int /*<<< orphan*/  intel_psr2_config_valid (struct intel_dp*,struct intel_crtc_state*) ; 
 int intel_usecs_to_scanlines (struct drm_display_mode const*,int) ; 

void intel_psr_compute_config(struct intel_dp *intel_dp,
			      struct intel_crtc_state *crtc_state)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	const struct drm_display_mode *adjusted_mode =
		&crtc_state->base.adjusted_mode;
	int psr_setup_time;

	if (!CAN_PSR(dev_priv))
		return;

	if (intel_dp != dev_priv->psr.dp)
		return;

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

	if (dev_priv->psr.sink_not_reliable) {
		DRM_DEBUG_KMS("PSR sink implementation is not reliable\n");
		return;
	}

	if (adjusted_mode->flags & DRM_MODE_FLAG_INTERLACE) {
		DRM_DEBUG_KMS("PSR condition failed: Interlaced mode enabled\n");
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
}