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
struct ltc294x_info {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LTC294X_REG_ACC_CHARGE_MSB ; 
 int /*<<< orphan*/  LTC294X_REG_CHARGE_THR_HIGH_MSB ; 
 int /*<<< orphan*/  LTC294X_REG_CHARGE_THR_LOW_MSB ; 
#define  POWER_SUPPLY_PROP_CHARGE_COUNTER 134 
#define  POWER_SUPPLY_PROP_CHARGE_EMPTY 133 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 132 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 131 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 130 
#define  POWER_SUPPLY_PROP_TEMP 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int ltc294x_get_charge (struct ltc294x_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ltc294x_get_charge_counter (struct ltc294x_info*,int /*<<< orphan*/ *) ; 
 int ltc294x_get_current (struct ltc294x_info*,int /*<<< orphan*/ *) ; 
 int ltc294x_get_temperature (struct ltc294x_info*,int /*<<< orphan*/ *) ; 
 int ltc294x_get_voltage (struct ltc294x_info*,int /*<<< orphan*/ *) ; 
 struct ltc294x_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int ltc294x_get_property(struct power_supply *psy,
				enum power_supply_property prop,
				union power_supply_propval *val)
{
	struct ltc294x_info *info = power_supply_get_drvdata(psy);

	switch (prop) {
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		return ltc294x_get_charge(info, LTC294X_REG_CHARGE_THR_HIGH_MSB,
						&val->intval);
	case POWER_SUPPLY_PROP_CHARGE_EMPTY:
		return ltc294x_get_charge(info, LTC294X_REG_CHARGE_THR_LOW_MSB,
						&val->intval);
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		return ltc294x_get_charge(info, LTC294X_REG_ACC_CHARGE_MSB,
						&val->intval);
	case POWER_SUPPLY_PROP_CHARGE_COUNTER:
		return ltc294x_get_charge_counter(info, &val->intval);
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		return ltc294x_get_voltage(info, &val->intval);
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		return ltc294x_get_current(info, &val->intval);
	case POWER_SUPPLY_PROP_TEMP:
		return ltc294x_get_temperature(info, &val->intval);
	default:
		return -EINVAL;
	}
}