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
union power_supply_propval {long intval; } ;
struct power_supply {int dummy; } ;
struct ds2760_device_info {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EPERM ; 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 129 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 128 
 int /*<<< orphan*/  ds2760_battery_set_current_accum (struct ds2760_device_info*,long) ; 
 int /*<<< orphan*/  ds2760_battery_write_active_full (struct ds2760_device_info*,long) ; 
 struct ds2760_device_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int ds2760_battery_set_property(struct power_supply *psy,
				       enum power_supply_property psp,
				       const union power_supply_propval *val)
{
	struct ds2760_device_info *di = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		/* the interface counts in uAh, convert the value */
		ds2760_battery_write_active_full(di, val->intval / 1000L);
		break;

	case POWER_SUPPLY_PROP_CHARGE_NOW:
		/* ds2760_battery_set_current_accum() does the conversion */
		ds2760_battery_set_current_accum(di, val->intval);
		break;

	default:
		return -EPERM;
	}

	return 0;
}