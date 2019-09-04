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
struct power_supply {int dummy; } ;

/* Variables and functions */
 struct power_supply* power_supply_get_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_put (struct power_supply*) ; 
 int /*<<< orphan*/  power_supply_set_battery_charged (struct power_supply*) ; 
 int /*<<< orphan*/ * raumfeld_power_supplicants ; 

__attribute__((used)) static void raumfeld_power_signal_charged(void)
{
	struct power_supply *psy =
		power_supply_get_by_name(raumfeld_power_supplicants[0]);

	if (psy) {
		power_supply_set_battery_charged(psy);
		power_supply_put(psy);
	}
}