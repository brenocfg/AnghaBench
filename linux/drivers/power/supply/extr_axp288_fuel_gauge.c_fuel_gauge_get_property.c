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
struct power_supply {int dummy; } ;
struct axp288_fg_info {int status; int max_volt; int /*<<< orphan*/  lock; TYPE_1__* pdev; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_FG_RES ; 
 int /*<<< orphan*/  AXP20X_PWR_OP_MODE ; 
 int /*<<< orphan*/  AXP288_FG_CC_MTR1_REG ; 
 int /*<<< orphan*/  AXP288_FG_DES_CAP1_REG ; 
 int /*<<< orphan*/  AXP288_FG_LOW_CAP_REG ; 
 int CHRG_STAT_BAT_PRESENT ; 
 int EINVAL ; 
 int FG_DES_CAP_RES_LSB ; 
 int FG_REP_CAP_VALID ; 
 int FG_REP_CAP_VAL_MASK ; 
#define  POWER_SUPPLY_PROP_CAPACITY 139 
#define  POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN 138 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 137 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 136 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 135 
#define  POWER_SUPPLY_PROP_HEALTH 134 
#define  POWER_SUPPLY_PROP_PRESENT 133 
#define  POWER_SUPPLY_PROP_STATUS 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_OCV 128 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 int PROP_CURR (int) ; 
 void* PROP_VOLT (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int fuel_gauge_battery_health (struct axp288_fg_info*) ; 
 int fuel_gauge_get_current (struct axp288_fg_info*,int*) ; 
 int /*<<< orphan*/  fuel_gauge_get_status (struct axp288_fg_info*) ; 
 int fuel_gauge_get_vbatt (struct axp288_fg_info*,int*) ; 
 int fuel_gauge_get_vocv (struct axp288_fg_info*,int*) ; 
 int fuel_gauge_read_15bit_word (struct axp288_fg_info*,int /*<<< orphan*/ ) ; 
 int fuel_gauge_reg_readb (struct axp288_fg_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct axp288_fg_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int fuel_gauge_get_property(struct power_supply *ps,
		enum power_supply_property prop,
		union power_supply_propval *val)
{
	struct axp288_fg_info *info = power_supply_get_drvdata(ps);
	int ret = 0, value;

	mutex_lock(&info->lock);
	switch (prop) {
	case POWER_SUPPLY_PROP_STATUS:
		fuel_gauge_get_status(info);
		val->intval = info->status;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = fuel_gauge_battery_health(info);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = fuel_gauge_get_vbatt(info, &value);
		if (ret < 0)
			goto fuel_gauge_read_err;
		val->intval = PROP_VOLT(value);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_OCV:
		ret = fuel_gauge_get_vocv(info, &value);
		if (ret < 0)
			goto fuel_gauge_read_err;
		val->intval = PROP_VOLT(value);
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = fuel_gauge_get_current(info, &value);
		if (ret < 0)
			goto fuel_gauge_read_err;
		val->intval = PROP_CURR(value);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		ret = fuel_gauge_reg_readb(info, AXP20X_PWR_OP_MODE);
		if (ret < 0)
			goto fuel_gauge_read_err;

		if (ret & CHRG_STAT_BAT_PRESENT)
			val->intval = 1;
		else
			val->intval = 0;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = fuel_gauge_reg_readb(info, AXP20X_FG_RES);
		if (ret < 0)
			goto fuel_gauge_read_err;

		if (!(ret & FG_REP_CAP_VALID))
			dev_err(&info->pdev->dev,
				"capacity measurement not valid\n");
		val->intval = (ret & FG_REP_CAP_VAL_MASK);
		break;
	case POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		ret = fuel_gauge_reg_readb(info, AXP288_FG_LOW_CAP_REG);
		if (ret < 0)
			goto fuel_gauge_read_err;
		val->intval = (ret & 0x0f);
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		ret = fuel_gauge_read_15bit_word(info, AXP288_FG_CC_MTR1_REG);
		if (ret < 0)
			goto fuel_gauge_read_err;

		val->intval = ret * FG_DES_CAP_RES_LSB;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = fuel_gauge_read_15bit_word(info, AXP288_FG_DES_CAP1_REG);
		if (ret < 0)
			goto fuel_gauge_read_err;

		val->intval = ret * FG_DES_CAP_RES_LSB;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = PROP_VOLT(info->max_volt);
		break;
	default:
		mutex_unlock(&info->lock);
		return -EINVAL;
	}

	mutex_unlock(&info->lock);
	return 0;

fuel_gauge_read_err:
	mutex_unlock(&info->lock);
	return ret;
}