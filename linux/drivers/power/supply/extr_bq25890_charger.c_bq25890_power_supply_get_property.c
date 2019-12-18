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
union power_supply_propval {int intval; char* strval; } ;
struct power_supply {int dummy; } ;
struct bq25890_state {int online; int /*<<< orphan*/  chrg_fault; int /*<<< orphan*/  bat_fault; int /*<<< orphan*/  boost_fault; int /*<<< orphan*/  chrg_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  iterm; int /*<<< orphan*/  vreg; int /*<<< orphan*/  ichg; } ;
struct bq25890_device {TYPE_1__ init_data; int /*<<< orphan*/  chip_id; int /*<<< orphan*/  lock; struct bq25890_state state; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  BQ25890_ID ; 
 char* BQ25890_MANUFACTURER ; 
 int /*<<< orphan*/  BQ25895_ID ; 
 int /*<<< orphan*/  BQ25896_ID ; 
 int /*<<< orphan*/  CHRG_FAULT_THERMAL_SHUTDOWN ; 
 int /*<<< orphan*/  CHRG_FAULT_TIMER_EXPIRED ; 
 int EINVAL ; 
 int /*<<< orphan*/  F_BATV ; 
 int /*<<< orphan*/  F_ICHGR ; 
 int /*<<< orphan*/  F_SYSV ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE ; 
 int POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
#define  POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT 138 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT 137 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX 136 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE 135 
#define  POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX 134 
#define  POWER_SUPPLY_PROP_HEALTH 133 
#define  POWER_SUPPLY_PROP_MANUFACTURER 132 
#define  POWER_SUPPLY_PROP_MODEL_NAME 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_STATUS 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int POWER_SUPPLY_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  STATUS_FAST_CHARGING ; 
 int /*<<< orphan*/  STATUS_NOT_CHARGING ; 
 int /*<<< orphan*/  STATUS_PRE_CHARGING ; 
 int /*<<< orphan*/  STATUS_TERMINATION_DONE ; 
 int /*<<< orphan*/  TBL_ICHG ; 
 int /*<<< orphan*/  TBL_ITERM ; 
 int /*<<< orphan*/  TBL_VREG ; 
 int bq25890_field_read (struct bq25890_device*,int /*<<< orphan*/ ) ; 
 void* bq25890_find_val (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bq25890_device* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int bq25890_power_supply_get_property(struct power_supply *psy,
					     enum power_supply_property psp,
					     union power_supply_propval *val)
{
	int ret;
	struct bq25890_device *bq = power_supply_get_drvdata(psy);
	struct bq25890_state state;

	mutex_lock(&bq->lock);
	state = bq->state;
	mutex_unlock(&bq->lock);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (!state.online)
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		else if (state.chrg_status == STATUS_NOT_CHARGING)
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		else if (state.chrg_status == STATUS_PRE_CHARGING ||
			 state.chrg_status == STATUS_FAST_CHARGING)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else if (state.chrg_status == STATUS_TERMINATION_DONE)
			val->intval = POWER_SUPPLY_STATUS_FULL;
		else
			val->intval = POWER_SUPPLY_STATUS_UNKNOWN;

		break;

	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ25890_MANUFACTURER;
		break;

	case POWER_SUPPLY_PROP_MODEL_NAME:
		if (bq->chip_id == BQ25890_ID)
			val->strval = "BQ25890";
		else if (bq->chip_id == BQ25895_ID)
			val->strval = "BQ25895";
		else if (bq->chip_id == BQ25896_ID)
			val->strval = "BQ25896";
		else
			val->strval = "UNKNOWN";

		break;

	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = state.online;
		break;

	case POWER_SUPPLY_PROP_HEALTH:
		if (!state.chrg_fault && !state.bat_fault && !state.boost_fault)
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
		else if (state.bat_fault)
			val->intval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		else if (state.chrg_fault == CHRG_FAULT_TIMER_EXPIRED)
			val->intval = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
		else if (state.chrg_fault == CHRG_FAULT_THERMAL_SHUTDOWN)
			val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		else
			val->intval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq25890_field_read(bq, F_ICHGR); /* read measured value */
		if (ret < 0)
			return ret;

		/* converted_val = ADC_val * 50mA (table 10.3.19) */
		val->intval = ret * 50000;
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->intval = bq25890_find_val(bq->init_data.ichg, TBL_ICHG);
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		if (!state.online) {
			val->intval = 0;
			break;
		}

		ret = bq25890_field_read(bq, F_BATV); /* read measured value */
		if (ret < 0)
			return ret;

		/* converted_val = 2.304V + ADC_val * 20mV (table 10.3.15) */
		val->intval = 2304000 + ret * 20000;
		break;

	case POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->intval = bq25890_find_val(bq->init_data.vreg, TBL_VREG);
		break;

	case POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		val->intval = bq25890_find_val(bq->init_data.iterm, TBL_ITERM);
		break;

	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = bq25890_field_read(bq, F_SYSV); /* read measured value */
		if (ret < 0)
			return ret;

		/* converted_val = 2.304V + ADC_val * 20mV (table 10.3.15) */
		val->intval = 2304000 + ret * 20000;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}