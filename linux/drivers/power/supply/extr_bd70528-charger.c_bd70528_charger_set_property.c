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
union power_supply_propval {int intval; } ;
struct power_supply {int dummy; } ;
struct bd70528_psy {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 129 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 128 
 struct bd70528_psy* power_supply_get_drvdata (struct power_supply*) ; 
 int set_charge_current (struct bd70528_psy*,int) ; 
 int set_current_limit (struct bd70528_psy*,int) ; 

__attribute__((used)) static int bd70528_charger_set_property(struct power_supply *psy,
					enum power_supply_property psp,
					const union power_supply_propval *val)
{
	struct bd70528_psy *bdpsy = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		return set_current_limit(bdpsy, val->intval / 1000);
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		return set_charge_current(bdpsy, val->intval / 1000);
	default:
		break;
	}
	return -EINVAL;
}