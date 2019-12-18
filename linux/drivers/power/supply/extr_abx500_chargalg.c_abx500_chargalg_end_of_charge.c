#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ volt; scalar_t__ avg_curr; } ;
struct TYPE_5__ {scalar_t__ ac_cv_active; scalar_t__ usb_cv_active; } ;
struct abx500_chargalg {scalar_t__ charge_status; scalar_t__ charge_state; int maintenance_chg; scalar_t__ eoc_cnt; int /*<<< orphan*/  dev; int /*<<< orphan*/  chargalg_psy; TYPE_4__ batt_data; TYPE_3__* bm; TYPE_1__ events; } ;
struct TYPE_7__ {size_t batt_id; TYPE_2__* bat_type; } ;
struct TYPE_6__ {scalar_t__ termination_vol; scalar_t__ termination_curr; } ;

/* Variables and functions */
 scalar_t__ EOC_COND_CNT ; 
 scalar_t__ POWER_SUPPLY_STATUS_CHARGING ; 
 scalar_t__ POWER_SUPPLY_STATUS_FULL ; 
 scalar_t__ STATE_NORMAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void abx500_chargalg_end_of_charge(struct abx500_chargalg *di)
{
	if (di->charge_status == POWER_SUPPLY_STATUS_CHARGING &&
		di->charge_state == STATE_NORMAL &&
		!di->maintenance_chg && (di->batt_data.volt >=
		di->bm->bat_type[di->bm->batt_id].termination_vol ||
		di->events.usb_cv_active || di->events.ac_cv_active) &&
		di->batt_data.avg_curr <
		di->bm->bat_type[di->bm->batt_id].termination_curr &&
		di->batt_data.avg_curr > 0) {
		if (++di->eoc_cnt >= EOC_COND_CNT) {
			di->eoc_cnt = 0;
			di->charge_status = POWER_SUPPLY_STATUS_FULL;
			di->maintenance_chg = true;
			dev_dbg(di->dev, "EOC reached!\n");
			power_supply_changed(di->chargalg_psy);
		} else {
			dev_dbg(di->dev,
				" EOC limit reached for the %d"
				" time, out of %d before EOC\n",
				di->eoc_cnt,
				EOC_COND_CNT);
		}
	} else {
		di->eoc_cnt = 0;
	}
}