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
struct acpi_battery {scalar_t__ rate_now; } ;

/* Variables and functions */
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 scalar_t__ battery_ac_is_broken ; 
 scalar_t__ power_supply_is_system_supplied () ; 

__attribute__((used)) static int acpi_battery_handle_discharging(struct acpi_battery *battery)
{
	/*
	 * Some devices wrongly report discharging if the battery's charge level
	 * was above the device's start charging threshold atm the AC adapter
	 * was plugged in and the device thus did not start a new charge cycle.
	 */
	if ((battery_ac_is_broken || power_supply_is_system_supplied()) &&
	    battery->rate_now == 0)
		return POWER_SUPPLY_STATUS_NOT_CHARGING;

	return POWER_SUPPLY_STATUS_DISCHARGING;
}