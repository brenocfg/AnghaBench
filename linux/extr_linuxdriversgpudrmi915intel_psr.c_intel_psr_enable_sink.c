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
typedef  int /*<<< orphan*/  u8 ;
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct TYPE_6__ {struct drm_device* dev; } ;
struct TYPE_5__ {TYPE_3__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct TYPE_4__ {scalar_t__ psr2_enabled; scalar_t__ link_standby; } ;
struct drm_i915_private {TYPE_1__ psr; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ALPM_ENABLE ; 
 int /*<<< orphan*/  DP_PSR_CRC_VERIFICATION ; 
 int /*<<< orphan*/  DP_PSR_ENABLE ; 
 int /*<<< orphan*/  DP_PSR_ENABLE_PSR2 ; 
 int /*<<< orphan*/  DP_PSR_EN_CFG ; 
 int /*<<< orphan*/  DP_PSR_MAIN_LINK_ACTIVE ; 
 int /*<<< orphan*/  DP_RECEIVER_ALPM_CONFIG ; 
 int /*<<< orphan*/  DP_SET_POWER ; 
 int /*<<< orphan*/  DP_SET_POWER_D0 ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

__attribute__((used)) static void intel_psr_enable_sink(struct intel_dp *intel_dp)
{
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	struct drm_device *dev = dig_port->base.base.dev;
	struct drm_i915_private *dev_priv = to_i915(dev);
	u8 dpcd_val = DP_PSR_ENABLE;

	/* Enable ALPM at sink for psr2 */
	if (dev_priv->psr.psr2_enabled) {
		drm_dp_dpcd_writeb(&intel_dp->aux, DP_RECEIVER_ALPM_CONFIG,
				   DP_ALPM_ENABLE);
		dpcd_val |= DP_PSR_ENABLE_PSR2;
	}

	if (dev_priv->psr.link_standby)
		dpcd_val |= DP_PSR_MAIN_LINK_ACTIVE;
	if (!dev_priv->psr.psr2_enabled && INTEL_GEN(dev_priv) >= 8)
		dpcd_val |= DP_PSR_CRC_VERIFICATION;
	drm_dp_dpcd_writeb(&intel_dp->aux, DP_PSR_EN_CFG, dpcd_val);

	drm_dp_dpcd_writeb(&intel_dp->aux, DP_SET_POWER, DP_SET_POWER_D0);
}