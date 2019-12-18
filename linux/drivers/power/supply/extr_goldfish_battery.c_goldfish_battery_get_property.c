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
 int /*<<< orphan*/  BATTERY_CAPACITY ; 
 int /*<<< orphan*/  BATTERY_CHARGE_COUNTER ; 
 int /*<<< orphan*/  BATTERY_CHARGE_FULL_UAH ; 
 int /*<<< orphan*/  BATTERY_CURRENT_AVG ; 
 int /*<<< orphan*/  BATTERY_CURRENT_NOW ; 
 int /*<<< orphan*/  BATTERY_CYCLE_COUNT ; 
 int /*<<< orphan*/  BATTERY_HEALTH ; 
 int /*<<< orphan*/  BATTERY_PRESENT ; 
 int /*<<< orphan*/  BATTERY_STATUS ; 
 int /*<<< orphan*/  BATTERY_TEMP ; 
 int /*<<< orphan*/  BATTERY_VOLTAGE ; 
 int EINVAL ; 
 void* GOLDFISH_BATTERY_READ (struct goldfish_battery_data*,int /*<<< orphan*/ ) ; 
#define  POWER_SUPPLY_PROP_CAPACITY 139 
#define  POWER_SUPPLY_PROP_CHARGE_COUNTER 138 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 137 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 136 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 135 
#define  POWER_SUPPLY_PROP_CYCLE_COUNT 134 
#define  POWER_SUPPLY_PROP_HEALTH 133 
#define  POWER_SUPPLY_PROP_PRESENT 132 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 130 
#define  POWER_SUPPLY_PROP_TEMP 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 void* POWER_SUPPLY_TECHNOLOGY_LION ; 
 struct goldfish_battery_data* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int goldfish_battery_get_property(struct power_supply *psy,
				 enum power_supply_property psp,
				 union power_supply_propval *val)
{
	struct goldfish_battery_data *data = power_supply_get_drvdata(psy);
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_STATUS);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_HEALTH);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_PRESENT);
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_CAPACITY);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_VOLTAGE);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_TEMP);
		break;
	case POWER_SUPPLY_PROP_CHARGE_COUNTER:
		val->intval = GOLDFISH_BATTERY_READ(data,
						    BATTERY_CHARGE_COUNTER);
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_CURRENT_NOW);
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_CURRENT_AVG);
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		val->intval = GOLDFISH_BATTERY_READ(data,
						    BATTERY_CHARGE_FULL_UAH);
		break;
	case POWER_SUPPLY_PROP_CYCLE_COUNT:
		val->intval = GOLDFISH_BATTERY_READ(data, BATTERY_CYCLE_COUNT);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}