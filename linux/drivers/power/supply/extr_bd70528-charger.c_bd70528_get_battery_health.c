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
struct bd70528_psy {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int BD70528_MASK_CHG_BAT_DETECT ; 
 unsigned int BD70528_MASK_CHG_BAT_OVERVOLT ; 
 unsigned int BD70528_MASK_CHG_BAT_TIMER ; 
 int /*<<< orphan*/  BD70528_REG_CHG_BAT_STAT ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int bd70528_get_battery_health(struct bd70528_psy *bdpsy, int *val)
{
	int ret;
	unsigned int v;

	ret = regmap_read(bdpsy->regmap, BD70528_REG_CHG_BAT_STAT, &v);
	if (ret) {
		dev_err(bdpsy->dev, "Battery state read failure %d\n",
			ret);
		return ret;
	}
	/* No battery? */
	if (!(v & BD70528_MASK_CHG_BAT_DETECT))
		*val = POWER_SUPPLY_HEALTH_DEAD;
	else if (v & BD70528_MASK_CHG_BAT_OVERVOLT)
		*val = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	else if (v & BD70528_MASK_CHG_BAT_TIMER)
		*val = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
	else
		*val = POWER_SUPPLY_HEALTH_GOOD;

	return 0;
}