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
 int /*<<< orphan*/  SHUTDOWN_poweroff ; 
 int /*<<< orphan*/  pm_power_off () ; 
 int /*<<< orphan*/  xen_reboot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_machine_power_off(void)
{
	if (pm_power_off)
		pm_power_off();
	xen_reboot(SHUTDOWN_poweroff);
}