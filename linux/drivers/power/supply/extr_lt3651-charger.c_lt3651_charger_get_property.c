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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct lt3651_charger {int /*<<< orphan*/  chrg_gpio; int /*<<< orphan*/  fault_gpio; int /*<<< orphan*/  acpr_gpio; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_DEAD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_GOOD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_UNKNOWN ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
#define  POWER_SUPPLY_PROP_HEALTH 130 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  gpiod_get_value (int /*<<< orphan*/ ) ; 
 struct lt3651_charger* psy_to_lt3651_charger (struct power_supply*) ; 

__attribute__((used)) static int lt3651_charger_get_property(struct power_supply *psy,
		enum power_supply_property psp, union power_supply_propval *val)
{
	struct lt3651_charger *lt3651_charger = psy_to_lt3651_charger(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (!lt3651_charger->chrg_gpio) {
			val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
			break;
		}
		if (gpiod_get_value(lt3651_charger->chrg_gpio))
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = gpiod_get_value(lt3651_charger->acpr_gpio);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		if (!lt3651_charger->fault_gpio) {
			val->intval = POWER_SUPPLY_HEALTH_UNKNOWN;
			break;
		}
		if (!gpiod_get_value(lt3651_charger->fault_gpio)) {
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
			break;
		}
		/*
		 * If the fault pin is active, the chrg pin explains the type
		 * of failure.
		 */
		if (!lt3651_charger->chrg_gpio) {
			val->intval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
			break;
		}
		val->intval = gpiod_get_value(lt3651_charger->chrg_gpio) ?
				POWER_SUPPLY_HEALTH_OVERHEAT :
				POWER_SUPPLY_HEALTH_DEAD;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}