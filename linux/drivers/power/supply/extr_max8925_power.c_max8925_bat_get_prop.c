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
struct max8925_power_info {int bat_online; int /*<<< orphan*/  ac_online; int /*<<< orphan*/  usb_online; int /*<<< orphan*/  gpm; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int ENODATA ; 
 int ENODEV ; 
 int /*<<< orphan*/  MAX8925_CHG_STATUS ; 
 int MAX8925_CHG_STAT_EN_MASK ; 
 int MAX8925_CHG_STAT_MODE_MASK ; 
 int /*<<< orphan*/  MEASURE_ISNS ; 
 int /*<<< orphan*/  MEASURE_VMBATT ; 
 int POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 int POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 132 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_STATUS 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 struct max8925_power_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int max8925_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int start_measure (struct max8925_power_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8925_bat_get_prop(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	struct max8925_power_info *info = dev_get_drvdata(psy->dev.parent);
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = info->bat_online;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		if (info->bat_online) {
			ret = start_measure(info, MEASURE_VMBATT);
			if (ret >= 0) {
				val->intval = ret * 2000;	/* unit is uV */
				ret = 0;
				break;
			}
		}
		ret = -ENODATA;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		if (info->bat_online) {
			ret = start_measure(info, MEASURE_ISNS);
			if (ret >= 0) {
				/* assume r_sns is 0.02 */
				ret = ((ret * 6250) - 3125) /* uA */;
				val->intval = 0;
				if (ret > 0)
					val->intval = ret; /* unit is mA */
				ret = 0;
				break;
			}
		}
		ret = -ENODATA;
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		if (!info->bat_online) {
			ret = -ENODATA;
			break;
		}
		ret = max8925_reg_read(info->gpm, MAX8925_CHG_STATUS);
		ret = (ret & MAX8925_CHG_STAT_MODE_MASK) >> 2;
		switch (ret) {
		case 1:
			val->intval = POWER_SUPPLY_CHARGE_TYPE_FAST;
			break;
		case 0:
		case 2:
			val->intval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
			break;
		case 3:
			val->intval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			break;
		}
		ret = 0;
		break;
	case POWER_SUPPLY_PROP_STATUS:
		if (!info->bat_online) {
			ret = -ENODATA;
			break;
		}
		ret = max8925_reg_read(info->gpm, MAX8925_CHG_STATUS);
		if (info->usb_online || info->ac_online) {
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			if (ret & MAX8925_CHG_STAT_EN_MASK)
				val->intval = POWER_SUPPLY_STATUS_CHARGING;
		} else
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		ret = 0;
		break;
	default:
		ret = -ENODEV;
		break;
	}
	return ret;
}