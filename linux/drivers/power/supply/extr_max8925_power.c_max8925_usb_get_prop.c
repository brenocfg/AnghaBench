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
union power_supply_propval {int intval; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct max8925_power_info {int usb_online; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int ENODATA ; 
 int ENODEV ; 
 int /*<<< orphan*/  MEASURE_VCHG ; 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 struct max8925_power_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int start_measure (struct max8925_power_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8925_usb_get_prop(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	struct max8925_power_info *info = dev_get_drvdata(psy->dev.parent);
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = info->usb_online;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (info->usb_online) {
			ret = start_measure(info, MEASURE_VCHG);
			if (ret >= 0) {
				val->intval = ret * 2000;	/* unit is uV */
				goto out;
			}
		}
		ret = -ENODATA;
		break;
	default:
		ret = -ENODEV;
		break;
	}
out:
	return ret;
}