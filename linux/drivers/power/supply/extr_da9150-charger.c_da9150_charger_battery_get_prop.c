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
typedef  union power_supply_propval {int dummy; } power_supply_propval ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct da9150_charger {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 136 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX 135 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX 134 
#define  POWER_SUPPLY_PROP_HEALTH 133 
#define  POWER_SUPPLY_PROP_ONLINE 132 
#define  POWER_SUPPLY_PROP_PRESENT 131 
#define  POWER_SUPPLY_PROP_STATUS 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int da9150_charger_battery_charge_type (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_battery_current_max (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_battery_health (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_battery_present (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_battery_status (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_battery_voltage_max (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_battery_voltage_min (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_battery_voltage_now (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_supply_online (struct da9150_charger*,struct power_supply*,union power_supply_propval*) ; 
 struct da9150_charger* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_charger_battery_get_prop(struct power_supply *psy,
					   enum power_supply_property psp,
					   union power_supply_propval *val)
{
	struct da9150_charger *charger = dev_get_drvdata(psy->dev.parent);
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = da9150_charger_battery_status(charger, val);
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		ret = da9150_charger_supply_online(charger, psy, val);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		ret = da9150_charger_battery_health(charger, val);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		ret = da9150_charger_battery_present(charger, val);
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = da9150_charger_battery_charge_type(charger, val);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		ret = da9150_charger_battery_voltage_min(charger, val);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = da9150_charger_battery_voltage_now(charger, val);
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		ret = da9150_charger_battery_current_max(charger, val);
		break;
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		ret = da9150_charger_battery_voltage_max(charger, val);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}