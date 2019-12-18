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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct ds278x_info {TYPE_1__* ops; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int (* get_battery_capacity ) (struct ds278x_info*,int /*<<< orphan*/ *) ;int (* get_battery_voltage ) (struct ds278x_info*,int /*<<< orphan*/ *) ;int (* get_battery_current ) (struct ds278x_info*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 132 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 131 
#define  POWER_SUPPLY_PROP_STATUS 130 
#define  POWER_SUPPLY_PROP_TEMP 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int ds278x_get_status (struct ds278x_info*,int /*<<< orphan*/ *) ; 
 int ds278x_get_temp (struct ds278x_info*,int /*<<< orphan*/ *) ; 
 int stub1 (struct ds278x_info*,int /*<<< orphan*/ *) ; 
 int stub2 (struct ds278x_info*,int /*<<< orphan*/ *) ; 
 int stub3 (struct ds278x_info*,int /*<<< orphan*/ *) ; 
 struct ds278x_info* to_ds278x_info (struct power_supply*) ; 

__attribute__((used)) static int ds278x_battery_get_property(struct power_supply *psy,
				       enum power_supply_property prop,
				       union power_supply_propval *val)
{
	struct ds278x_info *info = to_ds278x_info(psy);
	int ret;

	switch (prop) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = ds278x_get_status(info, &val->intval);
		break;

	case POWER_SUPPLY_PROP_CAPACITY:
		ret = info->ops->get_battery_capacity(info, &val->intval);
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = info->ops->get_battery_voltage(info, &val->intval);
		break;

	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = info->ops->get_battery_current(info, &val->intval);
		break;

	case POWER_SUPPLY_PROP_TEMP:
		ret = ds278x_get_temp(info, &val->intval);
		break;

	default:
		ret = -EINVAL;
	}

	return ret;
}