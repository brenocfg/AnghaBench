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
struct wm97xx_batt_pdata {scalar_t__ charge_gpio; } ;
struct power_supply {TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_UNKNOWN ; 
 int bat_status ; 
 scalar_t__ gpio_get_value (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_changed (struct power_supply*) ; 
 struct wm97xx_batt_pdata* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  work_lock ; 

__attribute__((used)) static void wm97xx_bat_update(struct power_supply *bat_ps)
{
	int old_status = bat_status;
	struct wm97xx_batt_pdata *pdata = power_supply_get_drvdata(bat_ps);

	mutex_lock(&work_lock);

	bat_status = (pdata->charge_gpio >= 0) ?
			(gpio_get_value(pdata->charge_gpio) ?
			POWER_SUPPLY_STATUS_DISCHARGING :
			POWER_SUPPLY_STATUS_CHARGING) :
			POWER_SUPPLY_STATUS_UNKNOWN;

	if (old_status != bat_status) {
		pr_debug("%s: %i -> %i\n", bat_ps->desc->name, old_status,
					bat_status);
		power_supply_changed(bat_ps);
	}

	mutex_unlock(&work_lock);
}