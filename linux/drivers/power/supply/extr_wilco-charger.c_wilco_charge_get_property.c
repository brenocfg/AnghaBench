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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct wilco_ec_device {int dummy; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 scalar_t__ PID_CHARGE_LOWER_LIMIT ; 
 scalar_t__ PID_CHARGE_MODE ; 
 scalar_t__ PID_CHARGE_UPPER_LIMIT ; 
#define  POWER_SUPPLY_PROP_CHARGE_CONTROL_END_THRESHOLD 130 
#define  POWER_SUPPLY_PROP_CHARGE_CONTROL_START_THRESHOLD 129 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 128 
 int charge_mode_to_psp_val (int) ; 
 struct wilco_ec_device* power_supply_get_drvdata (struct power_supply*) ; 
 int wilco_ec_get_byte_property (struct wilco_ec_device*,scalar_t__,int*) ; 

__attribute__((used)) static int wilco_charge_get_property(struct power_supply *psy,
				     enum power_supply_property psp,
				     union power_supply_propval *val)
{
	struct wilco_ec_device *ec = power_supply_get_drvdata(psy);
	u32 property_id;
	int ret;
	u8 raw;

	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		property_id = PID_CHARGE_MODE;
		break;
	case POWER_SUPPLY_PROP_CHARGE_CONTROL_START_THRESHOLD:
		property_id = PID_CHARGE_LOWER_LIMIT;
		break;
	case POWER_SUPPLY_PROP_CHARGE_CONTROL_END_THRESHOLD:
		property_id = PID_CHARGE_UPPER_LIMIT;
		break;
	default:
		return -EINVAL;
	}

	ret = wilco_ec_get_byte_property(ec, property_id, &raw);
	if (ret < 0)
		return ret;
	if (property_id == PID_CHARGE_MODE) {
		ret = charge_mode_to_psp_val(raw);
		if (ret < 0)
			return -EBADMSG;
		raw = ret;
	}
	val->intval = raw;

	return 0;
}