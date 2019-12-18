#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int intval; int /*<<< orphan*/  strval; } ;
struct power_supply {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  ichaverage_res; int /*<<< orphan*/  vbat_res; } ;
struct da9030_charger {TYPE_2__* battery_info; TYPE_1__ adc; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_4__ {int technology; int voltage_max_design; int voltage_min_design; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  POWER_SUPPLY_PROP_CURRENT_AVG 135 
#define  POWER_SUPPLY_PROP_HEALTH 134 
#define  POWER_SUPPLY_PROP_MODEL_NAME 133 
#define  POWER_SUPPLY_PROP_STATUS 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int /*<<< orphan*/  da9030_battery_check_health (struct da9030_charger*,union power_supply_propval*) ; 
 int /*<<< orphan*/  da9030_battery_check_status (struct da9030_charger*,union power_supply_propval*) ; 
 int da9030_reg_to_mA (int /*<<< orphan*/ ) ; 
 int da9030_reg_to_mV (int /*<<< orphan*/ ) ; 
 struct da9030_charger* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int da9030_battery_get_property(struct power_supply *psy,
				   enum power_supply_property psp,
				   union power_supply_propval *val)
{
	struct da9030_charger *charger = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		da9030_battery_check_status(charger, val);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		da9030_battery_check_health(charger, val);
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = charger->battery_info->technology;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = charger->battery_info->voltage_max_design;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->intval = charger->battery_info->voltage_min_design;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = da9030_reg_to_mV(charger->adc.vbat_res) * 1000;
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		val->intval =
			da9030_reg_to_mA(charger->adc.ichaverage_res) * 1000;
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = charger->battery_info->name;
		break;
	default:
		break;
	}

	return 0;
}