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
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int port; TYPE_1__ base; } ;
struct intel_digital_port {int tc_mode; TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MG_DP_MODE (int,int) ; 
 int MG_DP_MODE_CFG_DP_X1_MODE ; 
 int MG_DP_MODE_CFG_DP_X2_MODE ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  TC_PORT_DP_ALT 129 
#define  TC_PORT_LEGACY 128 
 int TC_PORT_TBT_ALT ; 
 int intel_tc_port_get_lane_mask (struct intel_digital_port*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_program_mg_dp_mode(struct intel_digital_port *intel_dig_port)
{
	struct drm_i915_private *dev_priv = to_i915(intel_dig_port->base.base.dev);
	enum port port = intel_dig_port->base.port;
	u32 ln0, ln1, lane_mask;

	if (intel_dig_port->tc_mode == TC_PORT_TBT_ALT)
		return;

	ln0 = I915_READ(MG_DP_MODE(0, port));
	ln1 = I915_READ(MG_DP_MODE(1, port));

	switch (intel_dig_port->tc_mode) {
	case TC_PORT_DP_ALT:
		ln0 &= ~(MG_DP_MODE_CFG_DP_X1_MODE | MG_DP_MODE_CFG_DP_X2_MODE);
		ln1 &= ~(MG_DP_MODE_CFG_DP_X1_MODE | MG_DP_MODE_CFG_DP_X2_MODE);

		lane_mask = intel_tc_port_get_lane_mask(intel_dig_port);

		switch (lane_mask) {
		case 0x1:
		case 0x4:
			break;
		case 0x2:
			ln0 |= MG_DP_MODE_CFG_DP_X1_MODE;
			break;
		case 0x3:
			ln0 |= MG_DP_MODE_CFG_DP_X1_MODE |
			       MG_DP_MODE_CFG_DP_X2_MODE;
			break;
		case 0x8:
			ln1 |= MG_DP_MODE_CFG_DP_X1_MODE;
			break;
		case 0xC:
			ln1 |= MG_DP_MODE_CFG_DP_X1_MODE |
			       MG_DP_MODE_CFG_DP_X2_MODE;
			break;
		case 0xF:
			ln0 |= MG_DP_MODE_CFG_DP_X1_MODE |
			       MG_DP_MODE_CFG_DP_X2_MODE;
			ln1 |= MG_DP_MODE_CFG_DP_X1_MODE |
			       MG_DP_MODE_CFG_DP_X2_MODE;
			break;
		default:
			MISSING_CASE(lane_mask);
		}
		break;

	case TC_PORT_LEGACY:
		ln0 |= MG_DP_MODE_CFG_DP_X1_MODE | MG_DP_MODE_CFG_DP_X2_MODE;
		ln1 |= MG_DP_MODE_CFG_DP_X1_MODE | MG_DP_MODE_CFG_DP_X2_MODE;
		break;

	default:
		MISSING_CASE(intel_dig_port->tc_mode);
		return;
	}

	I915_WRITE(MG_DP_MODE(0, port), ln0);
	I915_WRITE(MG_DP_MODE(1, port), ln1);
}