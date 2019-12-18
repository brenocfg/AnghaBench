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
typedef  int u32 ;
struct intel_dp {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT ; 
 int DP_AUX_CH_CTL_DONE ; 
 int DP_AUX_CH_CTL_INTERRUPT ; 
 int DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT ; 
 int DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT ; 
 int DP_AUX_CH_CTL_RECEIVE_ERROR ; 
 int DP_AUX_CH_CTL_SEND_BUSY ; 
 int DP_AUX_CH_CTL_TIME_OUT_400us ; 
 int DP_AUX_CH_CTL_TIME_OUT_600us ; 
 int DP_AUX_CH_CTL_TIME_OUT_ERROR ; 
 scalar_t__ IS_BROADWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 g4x_get_aux_send_ctl(struct intel_dp *intel_dp,
				int send_bytes,
				u32 aux_clock_divider)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *dev_priv =
			to_i915(intel_dig_port->base.base.dev);
	u32 precharge, timeout;

	if (IS_GEN(dev_priv, 6))
		precharge = 3;
	else
		precharge = 5;

	if (IS_BROADWELL(dev_priv))
		timeout = DP_AUX_CH_CTL_TIME_OUT_600us;
	else
		timeout = DP_AUX_CH_CTL_TIME_OUT_400us;

	return DP_AUX_CH_CTL_SEND_BUSY |
	       DP_AUX_CH_CTL_DONE |
	       DP_AUX_CH_CTL_INTERRUPT |
	       DP_AUX_CH_CTL_TIME_OUT_ERROR |
	       timeout |
	       DP_AUX_CH_CTL_RECEIVE_ERROR |
	       (send_bytes << DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT) |
	       (precharge << DP_AUX_CH_CTL_PRECHARGE_2US_SHIFT) |
	       (aux_clock_divider << DP_AUX_CH_CTL_BIT_CLOCK_2X_SHIFT);
}