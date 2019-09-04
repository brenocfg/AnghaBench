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
 int /*<<< orphan*/  _machine_halt ; 
 int /*<<< orphan*/  _machine_restart ; 
 int /*<<< orphan*/  ip27_machine_halt ; 
 int /*<<< orphan*/  ip27_machine_power_off ; 
 int /*<<< orphan*/  ip27_machine_restart ; 
 int /*<<< orphan*/  pm_power_off ; 

void ip27_reboot_setup(void)
{
	_machine_restart = ip27_machine_restart;
	_machine_halt = ip27_machine_halt;
	pm_power_off = ip27_machine_power_off;
}