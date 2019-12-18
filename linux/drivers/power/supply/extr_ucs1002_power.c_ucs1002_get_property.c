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
union power_supply_propval {int /*<<< orphan*/  strval; int /*<<< orphan*/  intval; } ;
struct ucs1002_info {int /*<<< orphan*/  present; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 135 
#define  POWER_SUPPLY_PROP_CURRENT_MAX 134 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 133 
#define  POWER_SUPPLY_PROP_HEALTH 132 
#define  POWER_SUPPLY_PROP_MANUFACTURER 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_PRESENT 129 
#define  POWER_SUPPLY_PROP_USB_TYPE 128 
 int /*<<< orphan*/  UCS1002_MANUFACTURER ; 
 struct ucs1002_info* power_supply_get_drvdata (struct power_supply*) ; 
 int ucs1002_get_charge (struct ucs1002_info*,union power_supply_propval*) ; 
 int ucs1002_get_current (struct ucs1002_info*,union power_supply_propval*) ; 
 int ucs1002_get_health (struct ucs1002_info*,union power_supply_propval*) ; 
 int ucs1002_get_max_current (struct ucs1002_info*,union power_supply_propval*) ; 
 int ucs1002_get_online (struct ucs1002_info*,union power_supply_propval*) ; 
 int ucs1002_get_usb_type (struct ucs1002_info*,union power_supply_propval*) ; 

__attribute__((used)) static int ucs1002_get_property(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	struct ucs1002_info *info = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		return ucs1002_get_online(info, val);
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		return ucs1002_get_charge(info, val);
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		return ucs1002_get_current(info, val);
	case POWER_SUPPLY_PROP_CURRENT_MAX:
		return ucs1002_get_max_current(info, val);
	case POWER_SUPPLY_PROP_USB_TYPE:
		return ucs1002_get_usb_type(info, val);
	case POWER_SUPPLY_PROP_HEALTH:
		return ucs1002_get_health(info, val);
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = info->present;
		return 0;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = UCS1002_MANUFACTURER;
		return 0;
	default:
		return -EINVAL;
	}
}