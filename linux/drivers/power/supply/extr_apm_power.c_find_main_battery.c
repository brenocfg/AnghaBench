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
struct TYPE_2__ {int intval; } ;
struct find_bat_param {int max_energy; int max_charge; int /*<<< orphan*/ * bat; int /*<<< orphan*/ * max_energy_bat; int /*<<< orphan*/ * max_charge_bat; TYPE_1__ full; int /*<<< orphan*/ * main; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSY_PROP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VOLTAGE_MAX_DESIGN ; 
 int /*<<< orphan*/  __find_main_battery ; 
 int class_for_each_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct find_bat_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * main_battery ; 
 int /*<<< orphan*/  memset (struct find_bat_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  power_supply_class ; 

__attribute__((used)) static void find_main_battery(void)
{
	struct find_bat_param bp;
	int error;

	memset(&bp, 0, sizeof(struct find_bat_param));
	main_battery = NULL;
	bp.main = main_battery;

	error = class_for_each_device(power_supply_class, NULL, &bp,
				      __find_main_battery);
	if (error) {
		main_battery = bp.main;
		return;
	}

	if ((bp.max_energy_bat && bp.max_charge_bat) &&
			(bp.max_energy_bat != bp.max_charge_bat)) {
		/* try guess battery with more capacity */
		if (!PSY_PROP(bp.max_charge_bat, VOLTAGE_MAX_DESIGN,
			      &bp.full)) {
			if (bp.max_energy > bp.max_charge * bp.full.intval)
				main_battery = bp.max_energy_bat;
			else
				main_battery = bp.max_charge_bat;
		} else if (!PSY_PROP(bp.max_energy_bat, VOLTAGE_MAX_DESIGN,
								  &bp.full)) {
			if (bp.max_charge > bp.max_energy / bp.full.intval)
				main_battery = bp.max_charge_bat;
			else
				main_battery = bp.max_energy_bat;
		} else {
			/* give up, choice any */
			main_battery = bp.max_energy_bat;
		}
	} else if (bp.max_charge_bat) {
		main_battery = bp.max_charge_bat;
	} else if (bp.max_energy_bat) {
		main_battery = bp.max_energy_bat;
	} else {
		/* give up, try the last if any */
		main_battery = bp.bat;
	}
}