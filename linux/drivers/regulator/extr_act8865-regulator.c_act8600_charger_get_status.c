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
typedef  unsigned int u8 ;
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int ACT8600_APCH_CSTATE0 ; 
 unsigned int ACT8600_APCH_CSTATE1 ; 
 int /*<<< orphan*/  ACT8600_APCH_STAT ; 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int POWER_SUPPLY_STATUS_UNKNOWN ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int act8600_charger_get_status(struct regmap *map)
{
	unsigned int val;
	int ret;
	u8 state0, state1;

	ret = regmap_read(map, ACT8600_APCH_STAT, &val);
	if (ret < 0)
		return ret;

	state0 = val & ACT8600_APCH_CSTATE0;
	state1 = val & ACT8600_APCH_CSTATE1;

	if (state0 && !state1)
		return POWER_SUPPLY_STATUS_CHARGING;
	if (!state0 && state1)
		return POWER_SUPPLY_STATUS_NOT_CHARGING;
	if (!state0 && !state1)
		return POWER_SUPPLY_STATUS_DISCHARGING;

	return POWER_SUPPLY_STATUS_UNKNOWN;
}