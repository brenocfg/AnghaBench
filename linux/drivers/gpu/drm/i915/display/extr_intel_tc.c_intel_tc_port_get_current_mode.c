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
typedef  scalar_t__ u32 ;
struct intel_digital_port {scalar_t__ tc_legacy_port; } ;
typedef  enum tc_port_mode { ____Placeholder_tc_port_mode } tc_port_mode ;

/* Variables and functions */
 int TC_PORT_DP_ALT ; 
 int TC_PORT_LEGACY ; 
 int TC_PORT_TBT_ALT ; 
 scalar_t__ WARN_ON (int) ; 
 int fls (scalar_t__) ; 
 int icl_tc_phy_is_in_safe_mode (struct intel_digital_port*) ; 
 int /*<<< orphan*/  icl_tc_phy_status_complete (struct intel_digital_port*) ; 
 scalar_t__ tc_port_live_status_mask (struct intel_digital_port*) ; 

__attribute__((used)) static enum tc_port_mode
intel_tc_port_get_current_mode(struct intel_digital_port *dig_port)
{
	u32 live_status_mask = tc_port_live_status_mask(dig_port);
	bool in_safe_mode = icl_tc_phy_is_in_safe_mode(dig_port);
	enum tc_port_mode mode;

	if (in_safe_mode || WARN_ON(!icl_tc_phy_status_complete(dig_port)))
		return TC_PORT_TBT_ALT;

	mode = dig_port->tc_legacy_port ? TC_PORT_LEGACY : TC_PORT_DP_ALT;
	if (live_status_mask) {
		enum tc_port_mode live_mode = fls(live_status_mask) - 1;

		if (!WARN_ON(live_mode == TC_PORT_TBT_ALT))
			mode = live_mode;
	}

	return mode;
}