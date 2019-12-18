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
struct wacom_battery {int bat_status; int battery_capacity; int bat_charging; int bat_connected; int ps_connected; scalar_t__ battery; } ;

/* Variables and functions */
 int /*<<< orphan*/  power_supply_changed (scalar_t__) ; 

__attribute__((used)) static void __wacom_notify_battery(struct wacom_battery *battery,
				   int bat_status, int bat_capacity,
				   bool bat_charging, bool bat_connected,
				   bool ps_connected)
{
	bool changed = battery->bat_status       != bat_status    ||
		       battery->battery_capacity != bat_capacity  ||
		       battery->bat_charging     != bat_charging  ||
		       battery->bat_connected    != bat_connected ||
		       battery->ps_connected     != ps_connected;

	if (changed) {
		battery->bat_status = bat_status;
		battery->battery_capacity = bat_capacity;
		battery->bat_charging = bat_charging;
		battery->bat_connected = bat_connected;
		battery->ps_connected = ps_connected;

		if (battery->battery)
			power_supply_changed(battery->battery);
	}
}