#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct acpi_battery {scalar_t__ design_capacity_warning; scalar_t__ alarm; int /*<<< orphan*/  flags; TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_BATTERY_ALARM_PRESENT ; 
 int acpi_battery_set_alarm (struct acpi_battery*) ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_battery_init_alarm(struct acpi_battery *battery)
{
	/* See if alarms are supported, and if so, set default */
	if (!acpi_has_method(battery->device->handle, "_BTP")) {
		clear_bit(ACPI_BATTERY_ALARM_PRESENT, &battery->flags);
		return 0;
	}
	set_bit(ACPI_BATTERY_ALARM_PRESENT, &battery->flags);
	if (!battery->alarm)
		battery->alarm = battery->design_capacity_warning;
	return acpi_battery_set_alarm(battery);
}