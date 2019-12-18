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
typedef  int u32 ;
struct intel_digital_port {int tc_legacy_port; int /*<<< orphan*/  tc_port_name; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TC_PORT_DP_ALT ; 
 int /*<<< orphan*/  TC_PORT_LEGACY ; 
 int /*<<< orphan*/  TC_PORT_TBT_ALT ; 

__attribute__((used)) static void tc_port_fixup_legacy_flag(struct intel_digital_port *dig_port,
				      u32 live_status_mask)
{
	u32 valid_hpd_mask;

	if (dig_port->tc_legacy_port)
		valid_hpd_mask = BIT(TC_PORT_LEGACY);
	else
		valid_hpd_mask = BIT(TC_PORT_DP_ALT) |
				 BIT(TC_PORT_TBT_ALT);

	if (!(live_status_mask & ~valid_hpd_mask))
		return;

	/* If live status mismatches the VBT flag, trust the live status. */
	DRM_ERROR("Port %s: live status %08x mismatches the legacy port flag, fix flag\n",
		  dig_port->tc_port_name, live_status_mask);

	dig_port->tc_legacy_port = !dig_port->tc_legacy_port;
}