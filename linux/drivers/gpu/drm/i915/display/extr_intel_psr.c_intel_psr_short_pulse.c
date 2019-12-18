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
typedef  int u8 ;
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct i915_psr {int sink_not_reliable; int /*<<< orphan*/  lock; struct intel_dp* dp; int /*<<< orphan*/  enabled; } ;
struct drm_i915_private {struct i915_psr psr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_PSR (struct drm_i915_private*) ; 
 int /*<<< orphan*/  DP_PSR_ERROR_STATUS ; 
 int DP_PSR_LINK_CRC_ERROR ; 
 int DP_PSR_RFB_STORAGE_ERROR ; 
 int DP_PSR_SINK_INTERNAL_ERROR ; 
 int DP_PSR_SINK_STATE_MASK ; 
 int /*<<< orphan*/  DP_PSR_STATUS ; 
 int DP_PSR_VSC_SDP_UNCORRECTABLE_ERROR ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_disable_locked (struct intel_dp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_psr_short_pulse(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	struct i915_psr *psr = &dev_priv->psr;
	u8 val;
	const u8 errors = DP_PSR_RFB_STORAGE_ERROR |
			  DP_PSR_VSC_SDP_UNCORRECTABLE_ERROR |
			  DP_PSR_LINK_CRC_ERROR;

	if (!CAN_PSR(dev_priv) || !intel_dp_is_edp(intel_dp))
		return;

	mutex_lock(&psr->lock);

	if (!psr->enabled || psr->dp != intel_dp)
		goto exit;

	if (drm_dp_dpcd_readb(&intel_dp->aux, DP_PSR_STATUS, &val) != 1) {
		DRM_ERROR("PSR_STATUS dpcd read failed\n");
		goto exit;
	}

	if ((val & DP_PSR_SINK_STATE_MASK) == DP_PSR_SINK_INTERNAL_ERROR) {
		DRM_DEBUG_KMS("PSR sink internal error, disabling PSR\n");
		intel_psr_disable_locked(intel_dp);
		psr->sink_not_reliable = true;
	}

	if (drm_dp_dpcd_readb(&intel_dp->aux, DP_PSR_ERROR_STATUS, &val) != 1) {
		DRM_ERROR("PSR_ERROR_STATUS dpcd read failed\n");
		goto exit;
	}

	if (val & DP_PSR_RFB_STORAGE_ERROR)
		DRM_DEBUG_KMS("PSR RFB storage error, disabling PSR\n");
	if (val & DP_PSR_VSC_SDP_UNCORRECTABLE_ERROR)
		DRM_DEBUG_KMS("PSR VSC SDP uncorrectable error, disabling PSR\n");
	if (val & DP_PSR_LINK_CRC_ERROR)
		DRM_ERROR("PSR Link CRC error, disabling PSR\n");

	if (val & ~errors)
		DRM_ERROR("PSR_ERROR_STATUS unhandled errors %x\n",
			  val & ~errors);
	if (val & errors) {
		intel_psr_disable_locked(intel_dp);
		psr->sink_not_reliable = true;
	}
	/* clear status register */
	drm_dp_dpcd_writeb(&intel_dp->aux, DP_PSR_ERROR_STATUS, val);
exit:
	mutex_unlock(&psr->lock);
}