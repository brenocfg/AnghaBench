#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct TYPE_2__ {scalar_t__ link_standby; scalar_t__ psr2_enabled; } ;
struct drm_i915_private {TYPE_1__ psr; } ;

/* Variables and functions */
 int DP_ALPM_ENABLE ; 
 int DP_PSR_CRC_VERIFICATION ; 
 int DP_PSR_ENABLE ; 
 int DP_PSR_ENABLE_PSR2 ; 
 int /*<<< orphan*/  DP_PSR_EN_CFG ; 
 int DP_PSR_IRQ_HPD_WITH_CRC_ERRORS ; 
 int DP_PSR_MAIN_LINK_ACTIVE ; 
 int /*<<< orphan*/  DP_RECEIVER_ALPM_CONFIG ; 
 int /*<<< orphan*/  DP_SET_POWER ; 
 int DP_SET_POWER_D0 ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void intel_psr_enable_sink(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	u8 dpcd_val = DP_PSR_ENABLE;

	/* Enable ALPM at sink for psr2 */
	if (dev_priv->psr.psr2_enabled) {
		drm_dp_dpcd_writeb(&intel_dp->aux, DP_RECEIVER_ALPM_CONFIG,
				   DP_ALPM_ENABLE);
		dpcd_val |= DP_PSR_ENABLE_PSR2 | DP_PSR_IRQ_HPD_WITH_CRC_ERRORS;
	} else {
		if (dev_priv->psr.link_standby)
			dpcd_val |= DP_PSR_MAIN_LINK_ACTIVE;

		if (INTEL_GEN(dev_priv) >= 8)
			dpcd_val |= DP_PSR_CRC_VERIFICATION;
	}

	drm_dp_dpcd_writeb(&intel_dp->aux, DP_PSR_EN_CFG, dpcd_val);

	drm_dp_dpcd_writeb(&intel_dp->aux, DP_SET_POWER, DP_SET_POWER_D0);
}