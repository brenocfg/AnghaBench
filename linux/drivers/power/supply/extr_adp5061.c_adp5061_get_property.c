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
typedef  int /*<<< orphan*/  u8 ;
struct power_supply {int dummy; } ;
struct adp5061_state {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int ADP5061_CHG_STATUS_2_BAT_STATUS (int /*<<< orphan*/ ) ; 
 int ADP5061_NO_BATTERY ; 
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY_LEVEL 139 
#define  POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT 138 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 137 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 136 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX 135 
#define  POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT 134 
#define  POWER_SUPPLY_PROP_PRECHARGE_CURRENT 133 
#define  POWER_SUPPLY_PROP_PRESENT 132 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN 128 
 int adp5061_get_battery_status (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_charger_status (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_chg_type (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_chg_volt_lim (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_const_chg_current (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_input_current_limit (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_max_voltage (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_min_voltage (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_prechg_current (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_status (struct adp5061_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int adp5061_get_termination_current (struct adp5061_state*,union power_supply_propval*) ; 
 int adp5061_get_vweak_th (struct adp5061_state*,union power_supply_propval*) ; 
 struct adp5061_state* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int adp5061_get_property(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	struct adp5061_state *st = power_supply_get_drvdata(psy);
	u8 status1, status2;
	int mode, ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		ret = adp5061_get_status(st, &status1, &status2);
		if (ret < 0)
			return ret;

		mode = ADP5061_CHG_STATUS_2_BAT_STATUS(status2);
		if (mode == ADP5061_NO_BATTERY)
			val->intval = 0;
		else
			val->intval = 1;
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		return adp5061_get_chg_type(st, val);
	case POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		/* This property is used to indicate the input current
		 * limit into VINx (ILIM)
		 */
		return adp5061_get_input_current_limit(st, val);
	case POWER_SUPPLY_PROP_VOLTAGE_MAX:
		/* This property is used to indicate the termination
		 * voltage (VTRM)
		 */
		return adp5061_get_max_voltage(st, val);
	case POWER_SUPPLY_PROP_VOLTAGE_MIN:
		/*
		 * This property is used to indicate the trickle to fast
		 * charge threshold (VTRK_DEAD)
		 */
		return adp5061_get_min_voltage(st, val);
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		/* This property is used to indicate the charging
		 * voltage limit (CHG_VLIM)
		 */
		return adp5061_get_chg_volt_lim(st, val);
	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		/*
		 * This property is used to indicate the value of the constant
		 * current charge (ICHG)
		 */
		return adp5061_get_const_chg_current(st, val);
	case POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		/*
		 * This property is used to indicate the value of the trickle
		 * and weak charge currents (ITRK_DEAD)
		 */
		return adp5061_get_prechg_current(st, val);
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		/*
		 * This property is used to set the VWEAK threshold
		 * bellow this value, weak charge mode is entered
		 * above this value, fast chargerge mode is entered
		 */
		return adp5061_get_vweak_th(st, val);
	case POWER_SUPPLY_PROP_STATUS:
		/*
		 * Indicate the charger status in relation to power
		 * supply status property
		 */
		return adp5061_get_charger_status(st, val);
	case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		/*
		 * Indicate the battery status in relation to power
		 * supply capacity level property
		 */
		return adp5061_get_battery_status(st, val);
	case POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		/* Indicate the values of the termination current */
		return adp5061_get_termination_current(st, val);
	default:
		return -EINVAL;
	}

	return 0;
}