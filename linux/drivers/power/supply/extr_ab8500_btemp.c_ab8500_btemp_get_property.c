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
union power_supply_propval {int intval; } ;
struct power_supply {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  batt_rem; } ;
struct ab8500_btemp {TYPE_1__* bm; TYPE_2__ events; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_6__ {int name; } ;
struct TYPE_4__ {size_t batt_id; TYPE_3__* bat_type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_ONLINE 131 
#define  POWER_SUPPLY_PROP_PRESENT 130 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 129 
#define  POWER_SUPPLY_PROP_TEMP 128 
 int ab8500_btemp_get_temp (struct ab8500_btemp*) ; 
 struct ab8500_btemp* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int ab8500_btemp_get_property(struct power_supply *psy,
	enum power_supply_property psp,
	union power_supply_propval *val)
{
	struct ab8500_btemp *di = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
	case POWER_SUPPLY_PROP_ONLINE:
		if (di->events.batt_rem)
			val->intval = 0;
		else
			val->intval = 1;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = di->bm->bat_type[di->bm->batt_id].name;
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = ab8500_btemp_get_temp(di);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}