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
struct intel_digital_port {int tc_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MISSING_CASE (int) ; 
#define  TC_PORT_DP_ALT 130 
#define  TC_PORT_LEGACY 129 
#define  TC_PORT_TBT_ALT 128 
 int /*<<< orphan*/  icl_tc_phy_set_safe_mode (struct intel_digital_port*,int) ; 

__attribute__((used)) static void icl_tc_phy_disconnect(struct intel_digital_port *dig_port)
{
	switch (dig_port->tc_mode) {
	case TC_PORT_LEGACY:
		/* Nothing to do, we never disconnect from legacy mode */
		break;
	case TC_PORT_DP_ALT:
		icl_tc_phy_set_safe_mode(dig_port, true);
		dig_port->tc_mode = TC_PORT_TBT_ALT;
		break;
	case TC_PORT_TBT_ALT:
		/* Nothing to do, we stay in TBT-alt mode */
		break;
	default:
		MISSING_CASE(dig_port->tc_mode);
	}
}