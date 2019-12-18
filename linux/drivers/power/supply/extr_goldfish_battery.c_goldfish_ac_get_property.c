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
union power_supply_propval {void* intval; } ;
struct power_supply {int dummy; } ;
struct goldfish_battery_data {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  BATTERY_AC_ONLINE ; 
 int /*<<< orphan*/  BATTERY_CURRENT_MAX ; 
 int /*<<< orphan*/  BATTERY_VOLTAGE_MAX ; 
 int EINVAL ; 
 void* GOLDFISH_BATTERY_READ (struct goldfish_battery_data*,int /*<<< orphan*/ ) ; 
#define  POWER_SUPPLY_PROP_CURRENT_MAX 130 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX 128 
 struct goldfish_battery_data* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int goldfish_ac_get_property(struct power_supply *psy,
			enum power_supply_property psp,
			union power_supply_propval *val)
{
	struct goldfish_battery_data *data = power_supply_get_drvdata(psy);
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_AC_ONLINE);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_VOLTAGE_MAX);
		break;
	case POWER_SUPPLY_PROP_CURRENT_MAX:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_CURRENT_MAX);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}