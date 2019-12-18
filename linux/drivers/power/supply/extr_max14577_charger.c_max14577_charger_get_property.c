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
union power_supply_propval {int /*<<< orphan*/  strval; int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct max14577_charger {TYPE_1__* max14577; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {size_t dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAXIM_DEVICE_TYPE_NUM ; 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 134 
#define  POWER_SUPPLY_PROP_HEALTH 133 
#define  POWER_SUPPLY_PROP_MANUFACTURER 132 
#define  POWER_SUPPLY_PROP_MODEL_NAME 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_PRESENT 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 int /*<<< orphan*/  manufacturer ; 
 int max14577_get_battery_health (struct max14577_charger*,int /*<<< orphan*/ *) ; 
 int max14577_get_charge_type (struct max14577_charger*,int /*<<< orphan*/ *) ; 
 int max14577_get_charger_state (struct max14577_charger*,int /*<<< orphan*/ *) ; 
 int max14577_get_online (struct max14577_charger*,int /*<<< orphan*/ *) ; 
 int max14577_get_present (struct max14577_charger*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * model_names ; 
 struct max14577_charger* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int max14577_charger_get_property(struct power_supply *psy,
			    enum power_supply_property psp,
			    union power_supply_propval *val)
{
	struct max14577_charger *chg = power_supply_get_drvdata(psy);
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = max14577_get_charger_state(chg, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = max14577_get_charge_type(chg, &val->intval);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		ret = max14577_get_battery_health(chg, &val->intval);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		ret = max14577_get_present(chg, &val->intval);
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		ret = max14577_get_online(chg, &val->intval);
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		BUILD_BUG_ON(ARRAY_SIZE(model_names) != MAXIM_DEVICE_TYPE_NUM);
		val->strval = model_names[chg->max14577->dev_type];
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = manufacturer;
		break;
	default:
		return -EINVAL;
	}

	return ret;
}