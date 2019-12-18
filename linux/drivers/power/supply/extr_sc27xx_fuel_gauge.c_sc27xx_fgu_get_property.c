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
struct sc27xx_fgu_data {int bat_present; int total_cap; int /*<<< orphan*/  lock; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 139 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE 138 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 137 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 136 
#define  POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN 135 
#define  POWER_SUPPLY_PROP_HEALTH 134 
#define  POWER_SUPPLY_PROP_PRESENT 133 
#define  POWER_SUPPLY_PROP_STATUS 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_TEMP 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_OCV 128 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sc27xx_fgu_data* power_supply_get_drvdata (struct power_supply*) ; 
 int sc27xx_fgu_get_capacity (struct sc27xx_fgu_data*,int*) ; 
 int sc27xx_fgu_get_charge_vol (struct sc27xx_fgu_data*,int*) ; 
 int sc27xx_fgu_get_current (struct sc27xx_fgu_data*,int*) ; 
 int sc27xx_fgu_get_health (struct sc27xx_fgu_data*,int*) ; 
 int sc27xx_fgu_get_status (struct sc27xx_fgu_data*,int*) ; 
 int sc27xx_fgu_get_temp (struct sc27xx_fgu_data*,int*) ; 
 int sc27xx_fgu_get_vbat_ocv (struct sc27xx_fgu_data*,int*) ; 
 int sc27xx_fgu_get_vbat_vol (struct sc27xx_fgu_data*,int*) ; 

__attribute__((used)) static int sc27xx_fgu_get_property(struct power_supply *psy,
				   enum power_supply_property psp,
				   union power_supply_propval *val)
{
	struct sc27xx_fgu_data *data = power_supply_get_drvdata(psy);
	int ret = 0;
	int value;

	mutex_lock(&data->lock);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = sc27xx_fgu_get_status(data, &value);
		if (ret)
			goto error;

		val->intval = value;
		break;

	case POWER_SUPPLY_PROP_HEALTH:
		ret = sc27xx_fgu_get_health(data, &value);
		if (ret)
			goto error;

		val->intval = value;
		break;

	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = data->bat_present;
		break;

	case POWER_SUPPLY_PROP_TEMP:
		ret = sc27xx_fgu_get_temp(data, &value);
		if (ret)
			goto error;

		val->intval = value;
		break;

	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;

	case POWER_SUPPLY_PROP_CAPACITY:
		ret = sc27xx_fgu_get_capacity(data, &value);
		if (ret)
			goto error;

		val->intval = value;
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = sc27xx_fgu_get_vbat_vol(data, &value);
		if (ret)
			goto error;

		val->intval = value * 1000;
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_OCV:
		ret = sc27xx_fgu_get_vbat_ocv(data, &value);
		if (ret)
			goto error;

		val->intval = value;
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = sc27xx_fgu_get_charge_vol(data, &value);
		if (ret)
			goto error;

		val->intval = value;
		break;

	case POWER_SUPPLY_PROP_CURRENT_NOW:
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = sc27xx_fgu_get_current(data, &value);
		if (ret)
			goto error;

		val->intval = value * 1000;
		break;

	case POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		val->intval = data->total_cap * 1000;
		break;

	default:
		ret = -EINVAL;
		break;
	}

error:
	mutex_unlock(&data->lock);
	return ret;
}