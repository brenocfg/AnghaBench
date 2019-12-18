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
typedef  int u32 ;
struct sc2731_charger_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int SC2731_CHARGE_FULL ; 
 int /*<<< orphan*/  SC2731_CHARGE_STATUS ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int sc2731_charger_get_status(struct sc2731_charger_info *info)
{
	u32 val;
	int ret;

	ret = regmap_read(info->regmap, SC2731_CHARGE_STATUS, &val);
	if (ret)
		return ret;

	if (val & SC2731_CHARGE_FULL)
		return POWER_SUPPLY_STATUS_FULL;

	return POWER_SUPPLY_STATUS_CHARGING;
}