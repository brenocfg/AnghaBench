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
struct intel_digital_port {TYPE_2__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum tc_port { ____Placeholder_tc_port } tc_port ;
typedef  enum port { ____Placeholder_port } port ;

/* Variables and functions */
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MG_DP_MODE (int,int) ; 
 int MG_DP_MODE_CFG_CLNPWR_GATING ; 
 int MG_DP_MODE_CFG_DIGPWR_GATING ; 
 int MG_DP_MODE_CFG_GAONPWR_GATING ; 
 int MG_DP_MODE_CFG_TR2PWR_GATING ; 
 int MG_DP_MODE_CFG_TRPWR_GATING ; 
 int /*<<< orphan*/  MG_MISC_SUS0 (int) ; 
 int MG_MISC_SUS0_CFG_CL1PWR_GATING ; 
 int MG_MISC_SUS0_CFG_CL2PWR_GATING ; 
 int MG_MISC_SUS0_CFG_DGPWR_GATING ; 
 int MG_MISC_SUS0_CFG_GAONPWR_GATING ; 
 int MG_MISC_SUS0_CFG_TR2PWR_GATING ; 
 int MG_MISC_SUS0_CFG_TRPWR_GATING ; 
 int MG_MISC_SUS0_SUSCLK_DYNCLKGATE_MODE_MASK ; 
 int PORT_TC_NONE ; 
 int intel_port_to_tc (struct drm_i915_private*,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icl_disable_phy_clock_gating(struct intel_digital_port *dig_port)
{
	struct drm_i915_private *dev_priv = to_i915(dig_port->base.base.dev);
	enum port port = dig_port->base.port;
	enum tc_port tc_port = intel_port_to_tc(dev_priv, port);
	u32 val;
	int ln;

	if (tc_port == PORT_TC_NONE)
		return;

	for (ln = 0; ln < 2; ln++) {
		val = I915_READ(MG_DP_MODE(ln, port));
		val &= ~(MG_DP_MODE_CFG_TR2PWR_GATING |
			 MG_DP_MODE_CFG_TRPWR_GATING |
			 MG_DP_MODE_CFG_CLNPWR_GATING |
			 MG_DP_MODE_CFG_DIGPWR_GATING |
			 MG_DP_MODE_CFG_GAONPWR_GATING);
		I915_WRITE(MG_DP_MODE(ln, port), val);
	}

	val = I915_READ(MG_MISC_SUS0(tc_port));
	val &= ~(MG_MISC_SUS0_SUSCLK_DYNCLKGATE_MODE_MASK |
		 MG_MISC_SUS0_CFG_TR2PWR_GATING |
		 MG_MISC_SUS0_CFG_CL2PWR_GATING |
		 MG_MISC_SUS0_CFG_GAONPWR_GATING |
		 MG_MISC_SUS0_CFG_TRPWR_GATING |
		 MG_MISC_SUS0_CFG_CL1PWR_GATING |
		 MG_MISC_SUS0_CFG_DGPWR_GATING);
	I915_WRITE(MG_MISC_SUS0(tc_port), val);
}