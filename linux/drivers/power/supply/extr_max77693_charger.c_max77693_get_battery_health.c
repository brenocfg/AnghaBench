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
struct regmap {int dummy; } ;

/* Variables and functions */
 unsigned int CHG_DETAILS_01_BAT_MASK ; 
 unsigned int CHG_DETAILS_01_BAT_SHIFT ; 
#define  MAX77693_BATTERY_GOOD 135 
#define  MAX77693_BATTERY_LOWVOLTAGE 134 
#define  MAX77693_BATTERY_NOBAT 133 
#define  MAX77693_BATTERY_OVERCURRENT 132 
#define  MAX77693_BATTERY_OVERVOLTAGE 131 
#define  MAX77693_BATTERY_PREQUALIFICATION 130 
#define  MAX77693_BATTERY_RESERVED 129 
#define  MAX77693_BATTERY_TIMER_EXPIRED 128 
 int /*<<< orphan*/  MAX77693_CHG_REG_CHG_DETAILS_01 ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE ; 
 int POWER_SUPPLY_HEALTH_UNKNOWN ; 
 int POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max77693_get_battery_health(struct regmap *regmap, int *val)
{
	int ret;
	unsigned int data;

	ret = regmap_read(regmap, MAX77693_CHG_REG_CHG_DETAILS_01, &data);
	if (ret < 0)
		return ret;

	data &= CHG_DETAILS_01_BAT_MASK;
	data >>= CHG_DETAILS_01_BAT_SHIFT;

	switch (data) {
	case MAX77693_BATTERY_NOBAT:
		*val = POWER_SUPPLY_HEALTH_DEAD;
		break;
	case MAX77693_BATTERY_PREQUALIFICATION:
	case MAX77693_BATTERY_GOOD:
	case MAX77693_BATTERY_LOWVOLTAGE:
		*val = POWER_SUPPLY_HEALTH_GOOD;
		break;
	case MAX77693_BATTERY_TIMER_EXPIRED:
		/*
		 * Took longer to charge than expected, charging suspended.
		 * Damaged battery?
		 */
		*val = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
		break;
	case MAX77693_BATTERY_OVERVOLTAGE:
		*val = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		break;
	case MAX77693_BATTERY_OVERCURRENT:
		*val = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		break;
	case MAX77693_BATTERY_RESERVED:
	default:
		*val = POWER_SUPPLY_HEALTH_UNKNOWN;
		break;
	}

	return 0;
}