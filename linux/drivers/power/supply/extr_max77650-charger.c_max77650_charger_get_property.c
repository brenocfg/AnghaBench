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
struct max77650_charger_data {int /*<<< orphan*/  map; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 void* MAX77650_CHARGER_CHG_CHARGING (int) ; 
 int /*<<< orphan*/  MAX77650_CHG_DETAILS_BITS (int) ; 
#define  MAX77650_CHG_DONE 142 
#define  MAX77650_CHG_OFF 141 
#define  MAX77650_CHG_ON_CURR 140 
#define  MAX77650_CHG_ON_CURR_JEITA 139 
#define  MAX77650_CHG_ON_TOPOFF 138 
#define  MAX77650_CHG_ON_TOPOFF_JEITA 137 
#define  MAX77650_CHG_ON_VOLT 136 
#define  MAX77650_CHG_ON_VOLT_JEITA 135 
#define  MAX77650_CHG_PREQ 134 
#define  MAX77650_CHG_SUSP_BATT_TEMP_FAULT 133 
#define  MAX77650_CHG_SUSP_FAST_CHG_TIM_FAULT 132 
#define  MAX77650_CHG_SUSP_PREQ_TIM_FAULT 131 
 int /*<<< orphan*/  MAX77650_REG_STAT_CHG_B ; 
 void* POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 void* POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 void* POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 
 void* POWER_SUPPLY_CHARGE_TYPE_UNKNOWN ; 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 130 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 void* POWER_SUPPLY_STATUS_CHARGING ; 
 void* POWER_SUPPLY_STATUS_FULL ; 
 void* POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 void* POWER_SUPPLY_STATUS_UNKNOWN ; 
 struct max77650_charger_data* power_supply_get_drvdata (struct power_supply*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int max77650_charger_get_property(struct power_supply *psy,
					 enum power_supply_property psp,
					 union power_supply_propval *val)
{
	struct max77650_charger_data *chg = power_supply_get_drvdata(psy);
	int rv, reg;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		rv = regmap_read(chg->map, MAX77650_REG_STAT_CHG_B, &reg);
		if (rv)
			return rv;

		if (MAX77650_CHARGER_CHG_CHARGING(reg)) {
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
			break;
		}

		switch (MAX77650_CHG_DETAILS_BITS(reg)) {
		case MAX77650_CHG_OFF:
		case MAX77650_CHG_SUSP_PREQ_TIM_FAULT:
		case MAX77650_CHG_SUSP_FAST_CHG_TIM_FAULT:
		case MAX77650_CHG_SUSP_BATT_TEMP_FAULT:
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			break;
		case MAX77650_CHG_PREQ:
		case MAX77650_CHG_ON_CURR:
		case MAX77650_CHG_ON_CURR_JEITA:
		case MAX77650_CHG_ON_VOLT:
		case MAX77650_CHG_ON_VOLT_JEITA:
		case MAX77650_CHG_ON_TOPOFF:
		case MAX77650_CHG_ON_TOPOFF_JEITA:
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
			break;
		case MAX77650_CHG_DONE:
			val->intval = POWER_SUPPLY_STATUS_FULL;
			break;
		default:
			val->intval = POWER_SUPPLY_STATUS_UNKNOWN;
		}
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		rv = regmap_read(chg->map, MAX77650_REG_STAT_CHG_B, &reg);
		if (rv)
			return rv;

		val->intval = MAX77650_CHARGER_CHG_CHARGING(reg);
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		rv = regmap_read(chg->map, MAX77650_REG_STAT_CHG_B, &reg);
		if (rv)
			return rv;

		if (!MAX77650_CHARGER_CHG_CHARGING(reg)) {
			val->intval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			break;
		}

		switch (MAX77650_CHG_DETAILS_BITS(reg)) {
		case MAX77650_CHG_PREQ:
		case MAX77650_CHG_ON_CURR:
		case MAX77650_CHG_ON_CURR_JEITA:
		case MAX77650_CHG_ON_VOLT:
		case MAX77650_CHG_ON_VOLT_JEITA:
			val->intval = POWER_SUPPLY_CHARGE_TYPE_FAST;
			break;
		case MAX77650_CHG_ON_TOPOFF:
		case MAX77650_CHG_ON_TOPOFF_JEITA:
			val->intval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
			break;
		default:
			val->intval = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}