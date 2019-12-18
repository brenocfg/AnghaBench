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
union power_supply_propval {int intval; int /*<<< orphan*/  strval; } ;
struct power_supply {int dummy; } ;
struct compal_data {int /*<<< orphan*/  bat_serial_number; int /*<<< orphan*/  bat_manufacturer_name; int /*<<< orphan*/  bat_model_name; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  BAT_CAPACITY ; 
 int /*<<< orphan*/  BAT_CHARGE_DESIGN ; 
 int /*<<< orphan*/  BAT_CHARGE_LIMIT ; 
 int BAT_CHARGE_LIMIT_MAX ; 
 int /*<<< orphan*/  BAT_CHARGE_NOW ; 
 int /*<<< orphan*/  BAT_CURRENT_AVG ; 
 int /*<<< orphan*/  BAT_CURRENT_NOW ; 
 int /*<<< orphan*/  BAT_POWER ; 
 int /*<<< orphan*/  BAT_TEMP ; 
 int /*<<< orphan*/  BAT_TEMP_AVG ; 
 int /*<<< orphan*/  BAT_VOLTAGE_DESIGN ; 
 int /*<<< orphan*/  BAT_VOLTAGE_NOW ; 
#define  POWER_SUPPLY_PROP_CAPACITY 147 
#define  POWER_SUPPLY_PROP_CAPACITY_LEVEL 146 
#define  POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT 145 
#define  POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX 144 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 143 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 142 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 141 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 140 
#define  POWER_SUPPLY_PROP_HEALTH 139 
#define  POWER_SUPPLY_PROP_MANUFACTURER 138 
#define  POWER_SUPPLY_PROP_MODEL_NAME 137 
#define  POWER_SUPPLY_PROP_POWER_NOW 136 
#define  POWER_SUPPLY_PROP_PRESENT 135 
#define  POWER_SUPPLY_PROP_SERIAL_NUMBER 134 
#define  POWER_SUPPLY_PROP_STATUS 133 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 132 
#define  POWER_SUPPLY_PROP_TEMP 131 
#define  POWER_SUPPLY_PROP_TEMP_AMBIENT 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int bat_capacity_level () ; 
 int bat_health () ; 
 int bat_is_present () ; 
 int bat_status () ; 
 int bat_technology () ; 
 int ec_read_s16 (int /*<<< orphan*/ ) ; 
 int ec_read_s8 (int /*<<< orphan*/ ) ; 
 int ec_read_u16 (int /*<<< orphan*/ ) ; 
 int ec_read_u8 (int /*<<< orphan*/ ) ; 
 struct compal_data* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int bat_get_property(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	struct compal_data *data = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = bat_status();
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = bat_health();
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = bat_is_present();
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = bat_technology();
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN: /* THE design voltage... */
		val->intval = ec_read_u16(BAT_VOLTAGE_DESIGN) * 1000;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = ec_read_u16(BAT_VOLTAGE_NOW) * 1000;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		val->intval = ec_read_s16(BAT_CURRENT_NOW) * 1000;
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		val->intval = ec_read_s16(BAT_CURRENT_AVG) * 1000;
		break;
	case POWER_SUPPLY_PROP_POWER_NOW:
		val->intval = ec_read_u8(BAT_POWER) * 1000000;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->intval = ec_read_u16(BAT_CHARGE_DESIGN) * 1000;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		val->intval = ec_read_u16(BAT_CHARGE_NOW) * 1000;
		break;
	case POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		val->intval = ec_read_u8(BAT_CHARGE_LIMIT);
		break;
	case POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT_MAX:
		val->intval = BAT_CHARGE_LIMIT_MAX;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = ec_read_u8(BAT_CAPACITY);
		break;
	case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		val->intval = bat_capacity_level();
		break;
	/* It smees that BAT_TEMP_AVG is a (2's complement?) value showing
	 * the number of degrees, whereas BAT_TEMP is somewhat more
	 * complicated. It looks like this is a negative nember with a
	 * 100/256 divider and an offset of 222. Both were determined
	 * experimentally by comparing BAT_TEMP and BAT_TEMP_AVG. */
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = ((222 - (int)ec_read_u8(BAT_TEMP)) * 1000) >> 8;
		break;
	case POWER_SUPPLY_PROP_TEMP_AMBIENT: /* Ambient, Avg, ... same thing */
		val->intval = ec_read_s8(BAT_TEMP_AVG) * 10;
		break;
	/* Neither the model name nor manufacturer name work for me. */
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = data->bat_model_name;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = data->bat_manufacturer_name;
		break;
	case POWER_SUPPLY_PROP_SERIAL_NUMBER:
		val->strval = data->bat_serial_number;
		break;
	default:
		break;
	}
	return 0;
}