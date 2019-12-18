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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {TYPE_3__* attached_connector; } ;
struct TYPE_9__ {int /*<<< orphan*/  active; int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {int /*<<< orphan*/  cpu_transcoder; TYPE_4__ base; } ;
struct intel_crtc {int dummy; } ;
struct TYPE_10__ {scalar_t__ type; int refresh_rate_type; struct intel_dp* dp; } ;
struct drm_i915_private {TYPE_5__ drrs; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;
typedef  enum drrs_refresh_rate_type { ____Placeholder_drrs_refresh_rate_type } drrs_refresh_rate_type ;
struct TYPE_7__ {TYPE_1__* downclock_mode; } ;
struct TYPE_8__ {TYPE_2__ panel; } ;
struct TYPE_6__ {int vrefresh; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
#define  DRRS_HIGH_RR 130 
#define  DRRS_LOW_RR 129 
#define  DRRS_MAX_RR 128 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  M1_N1 ; 
 int /*<<< orphan*/  M2_N2 ; 
 int /*<<< orphan*/  PIPECONF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIPECONF_EDP_RR_MODE_SWITCH ; 
 int /*<<< orphan*/  PIPECONF_EDP_RR_MODE_SWITCH_VLV ; 
 scalar_t__ SEAMLESS_DRRS_SUPPORT ; 
 int /*<<< orphan*/  intel_dp_set_m_n (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dp_set_drrs_state(struct drm_i915_private *dev_priv,
				    const struct intel_crtc_state *crtc_state,
				    int refresh_rate)
{
	struct intel_dp *intel_dp = dev_priv->drrs.dp;
	struct intel_crtc *intel_crtc = to_intel_crtc(crtc_state->base.crtc);
	enum drrs_refresh_rate_type index = DRRS_HIGH_RR;

	if (refresh_rate <= 0) {
		DRM_DEBUG_KMS("Refresh rate should be positive non-zero.\n");
		return;
	}

	if (intel_dp == NULL) {
		DRM_DEBUG_KMS("DRRS not supported.\n");
		return;
	}

	if (!intel_crtc) {
		DRM_DEBUG_KMS("DRRS: intel_crtc not initialized\n");
		return;
	}

	if (dev_priv->drrs.type < SEAMLESS_DRRS_SUPPORT) {
		DRM_DEBUG_KMS("Only Seamless DRRS supported.\n");
		return;
	}

	if (intel_dp->attached_connector->panel.downclock_mode->vrefresh ==
			refresh_rate)
		index = DRRS_LOW_RR;

	if (index == dev_priv->drrs.refresh_rate_type) {
		DRM_DEBUG_KMS(
			"DRRS requested for previously set RR...ignoring\n");
		return;
	}

	if (!crtc_state->base.active) {
		DRM_DEBUG_KMS("eDP encoder disabled. CRTC not Active\n");
		return;
	}

	if (INTEL_GEN(dev_priv) >= 8 && !IS_CHERRYVIEW(dev_priv)) {
		switch (index) {
		case DRRS_HIGH_RR:
			intel_dp_set_m_n(crtc_state, M1_N1);
			break;
		case DRRS_LOW_RR:
			intel_dp_set_m_n(crtc_state, M2_N2);
			break;
		case DRRS_MAX_RR:
		default:
			DRM_ERROR("Unsupported refreshrate type\n");
		}
	} else if (INTEL_GEN(dev_priv) > 6) {
		i915_reg_t reg = PIPECONF(crtc_state->cpu_transcoder);
		u32 val;

		val = I915_READ(reg);
		if (index > DRRS_HIGH_RR) {
			if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
				val |= PIPECONF_EDP_RR_MODE_SWITCH_VLV;
			else
				val |= PIPECONF_EDP_RR_MODE_SWITCH;
		} else {
			if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
				val &= ~PIPECONF_EDP_RR_MODE_SWITCH_VLV;
			else
				val &= ~PIPECONF_EDP_RR_MODE_SWITCH;
		}
		I915_WRITE(reg, val);
	}

	dev_priv->drrs.refresh_rate_type = index;

	DRM_DEBUG_KMS("eDP Refresh Rate set to : %dHz\n", refresh_rate);
}