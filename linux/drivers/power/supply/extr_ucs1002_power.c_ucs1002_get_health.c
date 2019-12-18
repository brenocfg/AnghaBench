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
union power_supply_propval {int intval; } ;
struct ucs1002_info {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int F_BACK_VOLT ; 
 unsigned int F_DISCHARGE_ERR ; 
 unsigned int F_MIN_KEEP_OUT ; 
 unsigned int F_OVER_ILIM ; 
 unsigned int F_OVER_VOLT ; 
 unsigned int F_TSD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERCURRENT ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
 int /*<<< orphan*/  UCS1002_REG_INTERRUPT_STATUS ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ucs1002_get_health(struct ucs1002_info *info,
			      union power_supply_propval *val)
{
	unsigned int reg;
	int ret, health;

	ret = regmap_read(info->regmap, UCS1002_REG_INTERRUPT_STATUS, &reg);
	if (ret)
		return ret;

	if (reg & F_TSD)
		health = POWER_SUPPLY_HEALTH_OVERHEAT;
	else if (reg & (F_OVER_VOLT | F_BACK_VOLT))
		health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	else if (reg & F_OVER_ILIM)
		health = POWER_SUPPLY_HEALTH_OVERCURRENT;
	else if (reg & (F_DISCHARGE_ERR | F_MIN_KEEP_OUT))
		health = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
	else
		health = POWER_SUPPLY_HEALTH_GOOD;

	val->intval = health;

	return 0;
}