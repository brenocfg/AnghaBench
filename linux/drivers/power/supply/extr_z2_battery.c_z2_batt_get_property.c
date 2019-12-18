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
struct z2_charger {int bat_status; struct z2_battery_info* info; } ;
struct z2_battery_info {int batt_tech; int max_voltage; int min_voltage; int /*<<< orphan*/  batt_I2C_reg; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_PRESENT 133 
#define  POWER_SUPPLY_PROP_STATUS 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 struct z2_charger* power_supply_get_drvdata (struct power_supply*) ; 
 int z2_read_bat (struct z2_charger*) ; 

__attribute__((used)) static int z2_batt_get_property(struct power_supply *batt_ps,
			    enum power_supply_property psp,
			    union power_supply_propval *val)
{
	struct z2_charger *charger = power_supply_get_drvdata(batt_ps);
	struct z2_battery_info *info = charger->info;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = charger->bat_status;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = info->batt_tech;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (info->batt_I2C_reg >= 0)
			val->intval = z2_read_bat(charger);
		else
			return -EINVAL;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX:
		if (info->max_voltage >= 0)
			val->intval = info->max_voltage;
		else
			return -EINVAL;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN:
		if (info->min_voltage >= 0)
			val->intval = info->min_voltage;
		else
			return -EINVAL;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = 1;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}