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
 unsigned int PS_STAT_VBUS_VALID ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int axp288_charger_is_online(struct axp288_chrg_info *info)
{
	int ret, online = 0;
	unsigned int val;

	ret = regmap_read(info->regmap, AXP20X_PWR_INPUT_STATUS, &val);
	if (ret < 0)
		return ret;

	if (val & PS_STAT_VBUS_VALID)
		online = 1;
	return online;
}