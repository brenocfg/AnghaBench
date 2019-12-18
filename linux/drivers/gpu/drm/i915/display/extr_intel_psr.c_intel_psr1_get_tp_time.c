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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int /*<<< orphan*/  dpcd; } ;
struct TYPE_3__ {int tp1_wakeup_time_us; int tp2_tp3_wakeup_time_us; } ;
struct TYPE_4__ {TYPE_1__ psr; } ;
struct drm_i915_private {TYPE_2__ vbt; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDP_PSR_TP1_TIME_0us ; 
 int /*<<< orphan*/  EDP_PSR_TP1_TIME_100us ; 
 int /*<<< orphan*/  EDP_PSR_TP1_TIME_2500us ; 
 int /*<<< orphan*/  EDP_PSR_TP1_TIME_500us ; 
 int /*<<< orphan*/  EDP_PSR_TP1_TP2_SEL ; 
 int /*<<< orphan*/  EDP_PSR_TP1_TP3_SEL ; 
 int /*<<< orphan*/  EDP_PSR_TP2_TP3_TIME_0us ; 
 int /*<<< orphan*/  EDP_PSR_TP2_TP3_TIME_100us ; 
 int /*<<< orphan*/  EDP_PSR_TP2_TP3_TIME_2500us ; 
 int /*<<< orphan*/  EDP_PSR_TP2_TP3_TIME_500us ; 
 int /*<<< orphan*/  EDP_PSR_TP4_TIME_0US ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 struct drm_i915_private* dp_to_i915 (struct intel_dp*) ; 
 scalar_t__ drm_dp_tps3_supported (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_dp_source_supports_hbr2 (struct intel_dp*) ; 

__attribute__((used)) static u32 intel_psr1_get_tp_time(struct intel_dp *intel_dp)
{
	struct drm_i915_private *dev_priv = dp_to_i915(intel_dp);
	u32 val = 0;

	if (INTEL_GEN(dev_priv) >= 11)
		val |= EDP_PSR_TP4_TIME_0US;

	if (dev_priv->vbt.psr.tp1_wakeup_time_us == 0)
		val |= EDP_PSR_TP1_TIME_0us;
	else if (dev_priv->vbt.psr.tp1_wakeup_time_us <= 100)
		val |= EDP_PSR_TP1_TIME_100us;
	else if (dev_priv->vbt.psr.tp1_wakeup_time_us <= 500)
		val |= EDP_PSR_TP1_TIME_500us;
	else
		val |= EDP_PSR_TP1_TIME_2500us;

	if (dev_priv->vbt.psr.tp2_tp3_wakeup_time_us == 0)
		val |= EDP_PSR_TP2_TP3_TIME_0us;
	else if (dev_priv->vbt.psr.tp2_tp3_wakeup_time_us <= 100)
		val |= EDP_PSR_TP2_TP3_TIME_100us;
	else if (dev_priv->vbt.psr.tp2_tp3_wakeup_time_us <= 500)
		val |= EDP_PSR_TP2_TP3_TIME_500us;
	else
		val |= EDP_PSR_TP2_TP3_TIME_2500us;

	if (intel_dp_source_supports_hbr2(intel_dp) &&
	    drm_dp_tps3_supported(intel_dp->dpcd))
		val |= EDP_PSR_TP1_TP3_SEL;
	else
		val |= EDP_PSR_TP1_TP2_SEL;

	return val;
}