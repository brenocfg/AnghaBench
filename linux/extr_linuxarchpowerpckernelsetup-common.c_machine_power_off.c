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
 int /*<<< orphan*/  machine_hang () ; 
 int /*<<< orphan*/  machine_shutdown () ; 
 int /*<<< orphan*/  pm_power_off () ; 
 int /*<<< orphan*/  smp_send_stop () ; 

void machine_power_off(void)
{
	machine_shutdown();
	if (pm_power_off)
		pm_power_off();

	smp_send_stop();
	machine_hang();
}