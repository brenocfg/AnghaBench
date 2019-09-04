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
 int /*<<< orphan*/  TB_SHUTDOWN_HALT ; 
 int /*<<< orphan*/  machine_shutdown () ; 
 int /*<<< orphan*/  pm_power_off () ; 
 int /*<<< orphan*/  reboot_force ; 
 int /*<<< orphan*/  tboot_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void native_machine_power_off(void)
{
	if (pm_power_off) {
		if (!reboot_force)
			machine_shutdown();
		pm_power_off();
	}
	/* A fallback in case there is no PM info available */
	tboot_shutdown(TB_SHUTDOWN_HALT);
}