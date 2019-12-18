#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int intval; } ;
typedef  scalar_t__ u32 ;
struct power_supply {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; scalar_t__ accumulator; scalar_t__ sample; } ;
struct cpcap_battery_state_data {int temperature; int current_ua; int counter_uah; int voltage; TYPE_1__ cc; } ;
struct TYPE_5__ {int technology; int voltage_max_design; int voltage_min_design; int charge_full_design; } ;
struct TYPE_6__ {TYPE_2__ info; } ;
struct cpcap_battery_ddata {TYPE_3__ config; } ;
typedef  int s64 ;
typedef  scalar_t__ s32 ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int CPCAP_NO_BATTERY ; 
 int EINVAL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_FULL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_HIGH ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_LOW ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_NORMAL ; 
 int POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN ; 
#define  POWER_SUPPLY_PROP_CAPACITY_LEVEL 142 
#define  POWER_SUPPLY_PROP_CHARGE_COUNTER 141 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 140 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 139 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 138 
#define  POWER_SUPPLY_PROP_POWER_AVG 137 
#define  POWER_SUPPLY_PROP_POWER_NOW 136 
#define  POWER_SUPPLY_PROP_PRESENT 135 
#define  POWER_SUPPLY_PROP_SCOPE 134 
#define  POWER_SUPPLY_PROP_STATUS 133 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 132 
#define  POWER_SUPPLY_PROP_TEMP 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_SCOPE_SYSTEM ; 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 void* cpcap_battery_cc_get_avg_current (struct cpcap_battery_ddata*) ; 
 void* cpcap_battery_cc_to_ua (struct cpcap_battery_ddata*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpcap_battery_full (struct cpcap_battery_ddata*) ; 
 int cpcap_battery_get_voltage (struct cpcap_battery_ddata*) ; 
 struct cpcap_battery_state_data* cpcap_battery_latest (struct cpcap_battery_ddata*) ; 
 struct cpcap_battery_state_data* cpcap_battery_previous (struct cpcap_battery_ddata*) ; 
 int cpcap_battery_update_status (struct cpcap_battery_ddata*) ; 
 void* div64_s64 (int,int) ; 
 struct cpcap_battery_ddata* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int cpcap_battery_get_property(struct power_supply *psy,
				      enum power_supply_property psp,
				      union power_supply_propval *val)
{
	struct cpcap_battery_ddata *ddata = power_supply_get_drvdata(psy);
	struct cpcap_battery_state_data *latest, *previous;
	u32 sample;
	s32 accumulator;
	int cached;
	s64 tmp;

	cached = cpcap_battery_update_status(ddata);
	if (cached < 0)
		return cached;

	latest = cpcap_battery_latest(ddata);
	previous = cpcap_battery_previous(ddata);

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		if (latest->temperature > CPCAP_NO_BATTERY)
			val->intval = 1;
		else
			val->intval = 0;
		break;
	case POWER_SUPPLY_PROP_STATUS:
		if (cpcap_battery_full(ddata)) {
			val->intval = POWER_SUPPLY_STATUS_FULL;
			break;
		}
		if (cpcap_battery_cc_get_avg_current(ddata) < 0)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = ddata->config.info.technology;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = cpcap_battery_get_voltage(ddata);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = ddata->config.info.voltage_max_design;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->intval = ddata->config.info.voltage_min_design;
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		sample = latest->cc.sample - previous->cc.sample;
		if (!sample) {
			val->intval = cpcap_battery_cc_get_avg_current(ddata);
			break;
		}
		accumulator = latest->cc.accumulator - previous->cc.accumulator;
		val->intval = cpcap_battery_cc_to_ua(ddata, sample,
						     accumulator,
						     latest->cc.offset);
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		val->intval = latest->current_ua;
		break;
	case POWER_SUPPLY_PROP_CHARGE_COUNTER:
		val->intval = latest->counter_uah;
		break;
	case POWER_SUPPLY_PROP_POWER_NOW:
		tmp = (latest->voltage / 10000) * latest->current_ua;
		val->intval = div64_s64(tmp, 100);
		break;
	case POWER_SUPPLY_PROP_POWER_AVG:
		sample = latest->cc.sample - previous->cc.sample;
		if (!sample) {
			tmp = cpcap_battery_cc_get_avg_current(ddata);
			tmp *= (latest->voltage / 10000);
			val->intval = div64_s64(tmp, 100);
			break;
		}
		accumulator = latest->cc.accumulator - previous->cc.accumulator;
		tmp = cpcap_battery_cc_to_ua(ddata, sample, accumulator,
					     latest->cc.offset);
		tmp *= ((latest->voltage + previous->voltage) / 20000);
		val->intval = div64_s64(tmp, 100);
		break;
	case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		if (cpcap_battery_full(ddata))
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_FULL;
		else if (latest->voltage >= 3750000)
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_HIGH;
		else if (latest->voltage >= 3300000)
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
		else if (latest->voltage > 3100000)
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_LOW;
		else if (latest->voltage <= 3100000)
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
		else
			val->intval = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->intval = ddata->config.info.charge_full_design;
		break;
	case POWER_SUPPLY_PROP_SCOPE:
		val->intval = POWER_SUPPLY_SCOPE_SYSTEM;
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = latest->temperature;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}