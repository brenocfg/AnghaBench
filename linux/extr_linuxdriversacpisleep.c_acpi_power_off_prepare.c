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
 int /*<<< orphan*/  ACPI_STATE_S5 ; 
 int /*<<< orphan*/  acpi_disable_all_gpes () ; 
 int /*<<< orphan*/  acpi_os_wait_events_complete () ; 
 int /*<<< orphan*/  acpi_sleep_prepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acpi_power_off_prepare(void)
{
	/* Prepare to power off the system */
	acpi_sleep_prepare(ACPI_STATE_S5);
	acpi_disable_all_gpes();
	acpi_os_wait_events_complete();
}