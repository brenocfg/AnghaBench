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
struct TYPE_2__ {void* vcharge_max; void* vcharge_min; void* vbat_charge_restart; void* vbat_charge_stop; void* vbat_charge_start; void* vbat_crit; void* vbat_low; int /*<<< orphan*/  tbat_restart; int /*<<< orphan*/  tbat_high; int /*<<< orphan*/  tbat_low; } ;
struct da9030_charger {TYPE_1__ thresholds; } ;
struct da9030_battery_info {int /*<<< orphan*/  vcharge_max; int /*<<< orphan*/  vcharge_min; int /*<<< orphan*/  vbat_charge_restart; int /*<<< orphan*/  vbat_charge_stop; int /*<<< orphan*/  vbat_charge_start; int /*<<< orphan*/  vbat_crit; int /*<<< orphan*/  vbat_low; int /*<<< orphan*/  tbat_restart; int /*<<< orphan*/  tbat_high; int /*<<< orphan*/  tbat_low; } ;

/* Variables and functions */
 void* da9030_millivolt_to_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void da9030_battery_convert_thresholds(struct da9030_charger *charger,
					      struct da9030_battery_info *pdata)
{
	charger->thresholds.tbat_low = pdata->tbat_low;
	charger->thresholds.tbat_high = pdata->tbat_high;
	charger->thresholds.tbat_restart  = pdata->tbat_restart;

	charger->thresholds.vbat_low =
		da9030_millivolt_to_reg(pdata->vbat_low);
	charger->thresholds.vbat_crit =
		da9030_millivolt_to_reg(pdata->vbat_crit);
	charger->thresholds.vbat_charge_start =
		da9030_millivolt_to_reg(pdata->vbat_charge_start);
	charger->thresholds.vbat_charge_stop =
		da9030_millivolt_to_reg(pdata->vbat_charge_stop);
	charger->thresholds.vbat_charge_restart =
		da9030_millivolt_to_reg(pdata->vbat_charge_restart);

	charger->thresholds.vcharge_min =
		da9030_millivolt_to_reg(pdata->vcharge_min);
	charger->thresholds.vcharge_max =
		da9030_millivolt_to_reg(pdata->vcharge_max);
}