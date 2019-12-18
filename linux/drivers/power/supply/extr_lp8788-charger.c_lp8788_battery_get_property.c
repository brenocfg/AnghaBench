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
struct lp8788_charger {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 135 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 134 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX 133 
#define  POWER_SUPPLY_PROP_HEALTH 132 
#define  POWER_SUPPLY_PROP_PRESENT 131 
#define  POWER_SUPPLY_PROP_STATUS 130 
#define  POWER_SUPPLY_PROP_TEMP 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 struct lp8788_charger* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int lp8788_get_battery_capacity (struct lp8788_charger*,union power_supply_propval*) ; 
 int lp8788_get_battery_charging_current (struct lp8788_charger*,union power_supply_propval*) ; 
 int lp8788_get_battery_health (struct lp8788_charger*,union power_supply_propval*) ; 
 int lp8788_get_battery_present (struct lp8788_charger*,union power_supply_propval*) ; 
 int lp8788_get_battery_status (struct lp8788_charger*,union power_supply_propval*) ; 
 int lp8788_get_battery_temperature (struct lp8788_charger*,union power_supply_propval*) ; 
 int lp8788_get_battery_voltage (struct lp8788_charger*,union power_supply_propval*) ; 
 int lp8788_get_charging_termination_voltage (struct lp8788_charger*,union power_supply_propval*) ; 

__attribute__((used)) static int lp8788_battery_get_property(struct power_supply *psy,
					enum power_supply_property psp,
					union power_supply_propval *val)
{
	struct lp8788_charger *pchg = dev_get_drvdata(psy->dev.parent);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		return lp8788_get_battery_status(pchg, val);
	case POWER_SUPPLY_PROP_HEALTH:
		return lp8788_get_battery_health(pchg, val);
	case POWER_SUPPLY_PROP_PRESENT:
		return lp8788_get_battery_present(pchg, val);
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		return lp8788_get_battery_voltage(pchg, val);
	case POWER_SUPPLY_PROP_CAPACITY:
		return lp8788_get_battery_capacity(pchg, val);
	case POWER_SUPPLY_PROP_TEMP:
		return lp8788_get_battery_temperature(pchg, val);
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		return lp8788_get_battery_charging_current(pchg, val);
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		return lp8788_get_charging_termination_voltage(pchg, val);
	default:
		return -EINVAL;
	}
}