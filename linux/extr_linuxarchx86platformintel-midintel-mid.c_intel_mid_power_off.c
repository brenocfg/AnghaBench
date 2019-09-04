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

/* Variables and functions */
 int /*<<< orphan*/  IPCMSG_COLD_OFF ; 
 int /*<<< orphan*/  intel_mid_pwr_power_off () ; 
 int /*<<< orphan*/  intel_scu_ipc_simple_command (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void intel_mid_power_off(void)
{
	/* Shut down South Complex via PWRMU */
	intel_mid_pwr_power_off();

	/* Only for Tangier, the rest will ignore this command */
	intel_scu_ipc_simple_command(IPCMSG_COLD_OFF, 1);
}