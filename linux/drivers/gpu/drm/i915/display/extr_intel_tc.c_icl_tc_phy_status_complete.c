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
struct intel_uncore {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; TYPE_1__ base; } ;
struct intel_digital_port {int /*<<< orphan*/  tc_port_name; int /*<<< orphan*/  tc_phy_fia; TYPE_2__ base; } ;
struct drm_i915_private {struct intel_uncore uncore; } ;
typedef  enum tc_port { ____Placeholder_tc_port } tc_port ;

/* Variables and functions */
 int DP_PHY_MODE_STATUS_COMPLETED (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_TX_DFLEXDPPMS (int /*<<< orphan*/ ) ; 
 int intel_port_to_tc (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int intel_uncore_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool icl_tc_phy_status_complete(struct intel_digital_port *dig_port)
{
	struct drm_i915_private *i915 = to_i915(dig_port->base.base.dev);
	enum tc_port tc_port = intel_port_to_tc(i915, dig_port->base.port);
	struct intel_uncore *uncore = &i915->uncore;
	u32 val;

	val = intel_uncore_read(uncore,
				PORT_TX_DFLEXDPPMS(dig_port->tc_phy_fia));
	if (val == 0xffffffff) {
		DRM_DEBUG_KMS("Port %s: PHY in TCCOLD, assuming not complete\n",
			      dig_port->tc_port_name);
		return false;
	}

	return val & DP_PHY_MODE_STATUS_COMPLETED(tc_port);
}