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
struct intel_dp {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_5__ base; } ;
struct intel_digital_port {TYPE_1__ base; } ;
struct TYPE_7__ {int crtc_hdisplay; int crtc_vdisplay; } ;
struct TYPE_8__ {TYPE_2__ adjusted_mode; } ;
struct intel_crtc_state {TYPE_3__ base; } ;
struct TYPE_9__ {int /*<<< orphan*/  sink_psr2_support; } ;
struct drm_i915_private {TYPE_4__ psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int,int,int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9 (struct drm_i915_private*) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool intel_psr2_config_valid(struct intel_dp *intel_dp,
				    struct intel_crtc_state *crtc_state)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv = to_i915(dig_port->base.base.dev);
	int crtc_hdisplay = crtc_state->base.adjusted_mode.crtc_hdisplay;
	int crtc_vdisplay = crtc_state->base.adjusted_mode.crtc_vdisplay;
	int psr_max_h = 0, psr_max_v = 0;

	/*
	 * FIXME psr2_support is messed up. It's both computed
	 * dynamically during PSR enable, and extracted from sink
	 * caps during eDP detection.
	 */
	if (!dev_priv->psr.sink_psr2_support)
		return false;

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv)) {
		psr_max_h = 4096;
		psr_max_v = 2304;
	} else if (IS_GEN9(dev_priv)) {
		psr_max_h = 3640;
		psr_max_v = 2304;
	}

	if (crtc_hdisplay > psr_max_h || crtc_vdisplay > psr_max_v) {
		DRM_DEBUG_KMS("PSR2 not enabled, resolution %dx%d > max supported %dx%d\n",
			      crtc_hdisplay, crtc_vdisplay,
			      psr_max_h, psr_max_v);
		return false;
	}

	return true;
}