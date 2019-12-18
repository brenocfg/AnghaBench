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
struct power_supply_battery_info {int voltage_min_design_uv; int voltage_max_design_uv; } ;
struct power_supply {int dummy; } ;
struct ingenic_battery {int /*<<< orphan*/  channel; struct power_supply_battery_info info; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
#define  POWER_SUPPLY_PROP_HEALTH 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 
 struct ingenic_battery* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int ingenic_battery_get_property(struct power_supply *psy,
					enum power_supply_property psp,
					union power_supply_propval *val)
{
	struct ingenic_battery *bat = power_supply_get_drvdata(psy);
	struct power_supply_battery_info *info = &bat->info;
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_HEALTH:
		ret = iio_read_channel_processed(bat->channel, &val->intval);
		val->intval *= 1000;
		if (val->intval < info->voltage_min_design_uv)
			val->intval = POWER_SUPPLY_HEALTH_DEAD;
		else if (val->intval > info->voltage_max_design_uv)
			val->intval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		else
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
		return ret;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = iio_read_channel_processed(bat->channel, &val->intval);
		val->intval *= 1000;
		return ret;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->intval = info->voltage_min_design_uv;
		return 0;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = info->voltage_max_design_uv;
		return 0;
	default:
		return -EINVAL;
	};
}