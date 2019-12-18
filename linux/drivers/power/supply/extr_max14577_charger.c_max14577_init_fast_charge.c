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
typedef  int /*<<< orphan*/  u8 ;
struct maxim_charger_current {int dummy; } ;
struct max14577_charger {TYPE_1__* max14577; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {size_t dev_type; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int CHGCTRL4_MBCICHWRCH_MASK ; 
 int CHGCTRL4_MBCICHWRCL_MASK ; 
 int /*<<< orphan*/  MAX14577_CHG_REG_CHG_CTRL4 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int max14577_update_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int maxim_charger_calc_reg_current (struct maxim_charger_current const*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 struct maxim_charger_current* maxim_charger_currents ; 

__attribute__((used)) static int max14577_init_fast_charge(struct max14577_charger *chg,
		unsigned int uamp)
{
	u8 reg_data;
	int ret;
	const struct maxim_charger_current *limits =
		&maxim_charger_currents[chg->max14577->dev_type];

	ret = maxim_charger_calc_reg_current(limits, uamp, uamp, &reg_data);
	if (ret) {
		dev_err(chg->dev, "Wrong value for fast charge: %u\n", uamp);
		return ret;
	}

	return max14577_update_reg(chg->max14577->regmap,
			MAX14577_CHG_REG_CHG_CTRL4,
			CHGCTRL4_MBCICHWRCL_MASK | CHGCTRL4_MBCICHWRCH_MASK,
			reg_data);
}