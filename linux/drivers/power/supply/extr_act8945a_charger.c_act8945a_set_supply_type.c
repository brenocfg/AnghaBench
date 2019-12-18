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
struct act8945a_charger {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACT8945A_APCH_STATE ; 
 int /*<<< orphan*/  ACT8945A_APCH_STATUS ; 
 unsigned int APCH_STATE_ACINSTAT ; 
 unsigned int APCH_STATUS_INDAT ; 
 unsigned int POWER_SUPPLY_TYPE_BATTERY ; 
 unsigned int POWER_SUPPLY_TYPE_MAINS ; 
 unsigned int POWER_SUPPLY_TYPE_USB ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int act8945a_set_supply_type(struct act8945a_charger *charger,
					     unsigned int *type)
{
	unsigned int status, state;
	int ret;

	ret = regmap_read(charger->regmap, ACT8945A_APCH_STATUS, &status);
	if (ret < 0)
		return ret;

	ret = regmap_read(charger->regmap, ACT8945A_APCH_STATE, &state);
	if (ret < 0)
		return ret;

	if (status & APCH_STATUS_INDAT) {
		if (state & APCH_STATE_ACINSTAT)
			*type = POWER_SUPPLY_TYPE_MAINS;
		else
			*type = POWER_SUPPLY_TYPE_USB;
	} else {
		*type = POWER_SUPPLY_TYPE_BATTERY;
	}

	return 0;
}