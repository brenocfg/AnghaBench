#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct i915_psr {int /*<<< orphan*/  lock; struct intel_dp* enabled; } ;
struct drm_i915_private {struct i915_psr psr; } ;
struct drm_device {int dummy; } ;

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
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_psr_disable_locked (struct intel_dp*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_psr_short_pulse(struct intel_dp *intel_dp)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = intel_dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	struct i915_psr *psr = &dev_priv->psr;
	u8 val;
	const u8 errors = DP_PSR_RFB_STORAGE_ERROR |
			  DP_PSR_VSC_SDP_UNCORRECTABLE_ERROR |
			  DP_PSR_LINK_CRC_ERROR;

	if (!CAN_PSR(dev_priv) || !intel_dp_is_edp(intel_dp))
		return;

	mutex_lock(&psr->lock);

	if (psr->enabled != intel_dp)
		goto exit;

	if (drm_dp_dpcd_readb(&intel_dp->aux, DP_PSR_STATUS, &val) != 1) {
		DRM_ERROR("PSR_STATUS dpcd read failed\n");
		goto exit;
	}

	if ((val & DP_PSR_SINK_STATE_MASK) == DP_PSR_SINK_INTERNAL_ERROR) {
		DRM_DEBUG_KMS("PSR sink internal error, disabling PSR\n");
		intel_psr_disable_locked(intel_dp);
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
	if (val & errors)
		intel_psr_disable_locked(intel_dp);
	/* clear status register */
	drm_dp_dpcd_writeb(&intel_dp->aux, DP_PSR_ERROR_STATUS, val);

	/* TODO: handle PSR2 errors */
exit:
	mutex_unlock(&psr->lock);
}