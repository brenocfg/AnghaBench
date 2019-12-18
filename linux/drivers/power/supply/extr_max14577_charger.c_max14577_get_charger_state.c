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
typedef  int u8 ;
struct regmap {int dummy; } ;
struct max14577_charger {TYPE_1__* max14577; } ;
struct TYPE_2__ {struct regmap* regmap; } ;

/* Variables and functions */
 int CHGCTRL2_MBCHOSTEN_MASK ; 
 int /*<<< orphan*/  MAX14577_CHG_REG_CHG_CTRL2 ; 
 int /*<<< orphan*/  MAX14577_CHG_REG_STATUS3 ; 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int STATUS3_CGMBC_MASK ; 
 int STATUS3_EOC_MASK ; 
 int max14577_read_reg (struct regmap*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int max14577_get_charger_state(struct max14577_charger *chg, int *val)
{
	struct regmap *rmap = chg->max14577->regmap;
	int ret;
	u8 reg_data;

	/*
	 * Charging occurs only if:
	 *  - CHGCTRL2/MBCHOSTEN == 1
	 *  - STATUS2/CGMBC == 1
	 *
	 * TODO:
	 *  - handle FULL after Top-off timer (EOC register may be off
	 *    and the charger won't be charging although MBCHOSTEN is on)
	 *  - handle properly dead-battery charging (respect timer)
	 *  - handle timers (fast-charge and prequal) /MBCCHGERR/
	 */
	ret = max14577_read_reg(rmap, MAX14577_CHG_REG_CHG_CTRL2, &reg_data);
	if (ret < 0)
		goto out;

	if ((reg_data & CHGCTRL2_MBCHOSTEN_MASK) == 0) {
		*val = POWER_SUPPLY_STATUS_DISCHARGING;
		goto out;
	}

	ret = max14577_read_reg(rmap, MAX14577_CHG_REG_STATUS3, &reg_data);
	if (ret < 0)
		goto out;

	if (reg_data & STATUS3_CGMBC_MASK) {
		/* Charger or USB-cable is connected */
		if (reg_data & STATUS3_EOC_MASK)
			*val = POWER_SUPPLY_STATUS_FULL;
		else
			*val = POWER_SUPPLY_STATUS_CHARGING;
		goto out;
	}

	*val = POWER_SUPPLY_STATUS_DISCHARGING;

out:
	return ret;
}