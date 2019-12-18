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
union power_supply_propval {int /*<<< orphan*/  intval; int /*<<< orphan*/  strval; } ;
struct power_supply {int dummy; } ;
struct ds2780_device_info {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_AVG ; 
 int /*<<< orphan*/  CURRENT_NOW ; 
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 137 
#define  POWER_SUPPLY_PROP_CHARGE_COUNTER 136 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 135 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 134 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 133 
#define  POWER_SUPPLY_PROP_MANUFACTURER 132 
#define  POWER_SUPPLY_PROP_MODEL_NAME 131 
#define  POWER_SUPPLY_PROP_STATUS 130 
#define  POWER_SUPPLY_PROP_TEMP 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int ds2780_get_accumulated_current (struct ds2780_device_info*,int /*<<< orphan*/ *) ; 
 int ds2780_get_capacity (struct ds2780_device_info*,int /*<<< orphan*/ *) ; 
 int ds2780_get_charge_now (struct ds2780_device_info*,int /*<<< orphan*/ *) ; 
 int ds2780_get_current (struct ds2780_device_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ds2780_get_status (struct ds2780_device_info*,int /*<<< orphan*/ *) ; 
 int ds2780_get_temperature (struct ds2780_device_info*,int /*<<< orphan*/ *) ; 
 int ds2780_get_voltage (struct ds2780_device_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manufacturer ; 
 int /*<<< orphan*/  model ; 
 struct ds2780_device_info* to_ds2780_device_info (struct power_supply*) ; 

__attribute__((used)) static int ds2780_battery_get_property(struct power_supply *psy,
	enum power_supply_property psp,
	union power_supply_propval *val)
{
	int ret = 0;
	struct ds2780_device_info *dev_info = to_ds2780_device_info(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = ds2780_get_voltage(dev_info, &val->intval);
		break;

	case POWER_SUPPLY_PROP_TEMP:
		ret = ds2780_get_temperature(dev_info, &val->intval);
		break;

	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = model;
		break;

	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = manufacturer;
		break;

	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = ds2780_get_current(dev_info, CURRENT_NOW, &val->intval);
		break;

	case POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = ds2780_get_current(dev_info, CURRENT_AVG, &val->intval);
		break;

	case POWER_SUPPLY_PROP_STATUS:
		ret = ds2780_get_status(dev_info, &val->intval);
		break;

	case POWER_SUPPLY_PROP_CAPACITY:
		ret = ds2780_get_capacity(dev_info, &val->intval);
		break;

	case POWER_SUPPLY_PROP_CHARGE_COUNTER:
		ret = ds2780_get_accumulated_current(dev_info, &val->intval);
		break;

	case POWER_SUPPLY_PROP_CHARGE_NOW:
		ret = ds2780_get_charge_now(dev_info, &val->intval);
		break;

	default:
		ret = -EINVAL;
	}

	return ret;
}