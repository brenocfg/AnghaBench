#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  temp; } ;
struct TYPE_4__ {int /*<<< orphan*/  btemp_underover; int /*<<< orphan*/  batt_ovv; } ;
struct abx500_chargalg {int /*<<< orphan*/  charge_state; TYPE_3__* bm; TYPE_2__ batt_data; TYPE_1__ events; int /*<<< orphan*/  charge_status; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_6__ {int /*<<< orphan*/  temp_under; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_COLD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_GOOD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
#define  POWER_SUPPLY_PROP_HEALTH 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 int /*<<< orphan*/  STATE_SAFETY_TIMER_EXPIRED ; 
 int /*<<< orphan*/  STATE_SAFETY_TIMER_EXPIRED_INIT ; 
 struct abx500_chargalg* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int abx500_chargalg_get_property(struct power_supply *psy,
	enum power_supply_property psp,
	union power_supply_propval *val)
{
	struct abx500_chargalg *di = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = di->charge_status;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		if (di->events.batt_ovv) {
			val->intval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		} else if (di->events.btemp_underover) {
			if (di->batt_data.temp <= di->bm->temp_under)
				val->intval = POWER_SUPPLY_HEALTH_COLD;
			else
				val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		} else if (di->charge_state == STATE_SAFETY_TIMER_EXPIRED ||
			   di->charge_state == STATE_SAFETY_TIMER_EXPIRED_INIT) {
			val->intval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		} else {
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
		}
		break;
	default:
		return -EINVAL;
	}
	return 0;
}