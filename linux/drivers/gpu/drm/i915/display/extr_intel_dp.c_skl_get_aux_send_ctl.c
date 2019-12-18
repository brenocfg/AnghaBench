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
struct TYPE_4__ {int /*<<< orphan*/  port; TYPE_1__ base; } ;
struct intel_digital_port {scalar_t__ tc_mode; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum phy { ____Placeholder_phy } phy ;

/* Variables and functions */
 int DP_AUX_CH_CTL_DONE ; 
 int DP_AUX_CH_CTL_FW_SYNC_PULSE_SKL (int) ; 
 int DP_AUX_CH_CTL_INTERRUPT ; 
 int DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT ; 
 int DP_AUX_CH_CTL_RECEIVE_ERROR ; 
 int DP_AUX_CH_CTL_SEND_BUSY ; 
 int DP_AUX_CH_CTL_SYNC_PULSE_SKL (int) ; 
 int DP_AUX_CH_CTL_TBT_IO ; 
 int DP_AUX_CH_CTL_TIME_OUT_ERROR ; 
 int DP_AUX_CH_CTL_TIME_OUT_MAX ; 
 scalar_t__ TC_PORT_TBT_ALT ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 scalar_t__ intel_phy_is_tc (struct drm_i915_private*,int) ; 
 int intel_port_to_phy (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 skl_get_aux_send_ctl(struct intel_dp *intel_dp,
				int send_bytes,
				u32 unused)
{
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	struct drm_i915_private *i915 =
			to_i915(intel_dig_port->base.base.dev);
	enum phy phy = intel_port_to_phy(i915, intel_dig_port->base.port);
	u32 ret;

	ret = DP_AUX_CH_CTL_SEND_BUSY |
	      DP_AUX_CH_CTL_DONE |
	      DP_AUX_CH_CTL_INTERRUPT |
	      DP_AUX_CH_CTL_TIME_OUT_ERROR |
	      DP_AUX_CH_CTL_TIME_OUT_MAX |
	      DP_AUX_CH_CTL_RECEIVE_ERROR |
	      (send_bytes << DP_AUX_CH_CTL_MESSAGE_SIZE_SHIFT) |
	      DP_AUX_CH_CTL_FW_SYNC_PULSE_SKL(32) |
	      DP_AUX_CH_CTL_SYNC_PULSE_SKL(32);

	if (intel_phy_is_tc(i915, phy) &&
	    intel_dig_port->tc_mode == TC_PORT_TBT_ALT)
		ret |= DP_AUX_CH_CTL_TBT_IO;

	return ret;
}