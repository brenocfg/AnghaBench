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
union power_supply_propval {char* strval; int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  online; int /*<<< orphan*/  level; int /*<<< orphan*/  capacity; int /*<<< orphan*/  status; } ;
struct hidpp_device {char* name; TYPE_2__* hid_dev; TYPE_1__ battery; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_4__ {char* uniq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 135 
#define  POWER_SUPPLY_PROP_CAPACITY_LEVEL 134 
#define  POWER_SUPPLY_PROP_MANUFACTURER 133 
#define  POWER_SUPPLY_PROP_MODEL_NAME 132 
#define  POWER_SUPPLY_PROP_ONLINE 131 
#define  POWER_SUPPLY_PROP_SCOPE 130 
#define  POWER_SUPPLY_PROP_SERIAL_NUMBER 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 int /*<<< orphan*/  POWER_SUPPLY_SCOPE_DEVICE ; 
 struct hidpp_device* power_supply_get_drvdata (struct power_supply*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int hidpp_battery_get_property(struct power_supply *psy,
				      enum power_supply_property psp,
				      union power_supply_propval *val)
{
	struct hidpp_device *hidpp = power_supply_get_drvdata(psy);
	int ret = 0;

	switch(psp) {
		case POWER_SUPPLY_PROP_STATUS:
			val->intval = hidpp->battery.status;
			break;
		case POWER_SUPPLY_PROP_CAPACITY:
			val->intval = hidpp->battery.capacity;
			break;
		case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
			val->intval = hidpp->battery.level;
			break;
		case POWER_SUPPLY_PROP_SCOPE:
			val->intval = POWER_SUPPLY_SCOPE_DEVICE;
			break;
		case POWER_SUPPLY_PROP_ONLINE:
			val->intval = hidpp->battery.online;
			break;
		case POWER_SUPPLY_PROP_MODEL_NAME:
			if (!strncmp(hidpp->name, "Logitech ", 9))
				val->strval = hidpp->name + 9;
			else
				val->strval = hidpp->name;
			break;
		case POWER_SUPPLY_PROP_MANUFACTURER:
			val->strval = "Logitech";
			break;
		case POWER_SUPPLY_PROP_SERIAL_NUMBER:
			val->strval = hidpp->hid_dev->uniq;
			break;
		default:
			ret = -EINVAL;
			break;
	}

	return ret;
}