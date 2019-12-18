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
struct axp288_chrg_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_PWR_INPUT_STATUS ; 
 int /*<<< orphan*/  AXP20X_PWR_OP_MODE ; 
 int CHRG_STAT_BAT_SAFE_MODE ; 
 int CHRG_STAT_PMIC_OTP ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE ; 
 int POWER_SUPPLY_HEALTH_UNKNOWN ; 
 unsigned int PS_STAT_VBUS_PRESENT ; 
 int PS_STAT_VBUS_VALID ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int axp288_get_charger_health(struct axp288_chrg_info *info)
{
	int ret, pwr_stat, chrg_stat;
	int health = POWER_SUPPLY_HEALTH_UNKNOWN;
	unsigned int val;

	ret = regmap_read(info->regmap, AXP20X_PWR_INPUT_STATUS, &val);
	if ((ret < 0) || !(val & PS_STAT_VBUS_PRESENT))
		goto health_read_fail;
	else
		pwr_stat = val;

	ret = regmap_read(info->regmap, AXP20X_PWR_OP_MODE, &val);
	if (ret < 0)
		goto health_read_fail;
	else
		chrg_stat = val;

	if (!(pwr_stat & PS_STAT_VBUS_VALID))
		health = POWER_SUPPLY_HEALTH_DEAD;
	else if (chrg_stat & CHRG_STAT_PMIC_OTP)
		health = POWER_SUPPLY_HEALTH_OVERHEAT;
	else if (chrg_stat & CHRG_STAT_BAT_SAFE_MODE)
		health = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
	else
		health = POWER_SUPPLY_HEALTH_GOOD;

health_read_fail:
	return health;
}