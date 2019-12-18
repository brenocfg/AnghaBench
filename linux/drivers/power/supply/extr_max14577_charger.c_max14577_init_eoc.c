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
typedef  unsigned int u8 ;
struct max14577_charger {TYPE_1__* max14577; } ;
struct TYPE_2__ {int dev_type; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHGCTRL5_EOCS_MASK ; 
 unsigned int CHGCTRL5_EOCS_SHIFT ; 
 int EINVAL ; 
 unsigned int MAX14577_CHARGER_EOC_CURRENT_LIMIT_MAX ; 
 unsigned int MAX14577_CHARGER_EOC_CURRENT_LIMIT_MIN ; 
 unsigned int MAX14577_CHARGER_EOC_CURRENT_LIMIT_STEP ; 
 int /*<<< orphan*/  MAX14577_CHG_REG_CHG_CTRL5 ; 
#define  MAXIM_DEVICE_TYPE_MAX14577 129 
#define  MAXIM_DEVICE_TYPE_MAX77836 128 
 int max14577_update_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static int max14577_init_eoc(struct max14577_charger *chg,
		unsigned int uamp)
{
	unsigned int current_bits = 0xf;
	u8 reg_data;

	switch (chg->max14577->dev_type) {
	case MAXIM_DEVICE_TYPE_MAX77836:
		if (uamp < 5000)
			return -EINVAL; /* Requested current is too low */

		if (uamp >= 7500 && uamp < 10000)
			current_bits = 0x0;
		else if (uamp <= 50000) {
			/* <5000, 7499> and <10000, 50000> */
			current_bits = uamp / 5000;
		} else {
			uamp = min(uamp, 100000U) - 50000U;
			current_bits = 0xa + uamp / 10000;
		}
		break;

	case MAXIM_DEVICE_TYPE_MAX14577:
	default:
		if (uamp < MAX14577_CHARGER_EOC_CURRENT_LIMIT_MIN)
			return -EINVAL; /* Requested current is too low */

		uamp = min(uamp, MAX14577_CHARGER_EOC_CURRENT_LIMIT_MAX);
		uamp -= MAX14577_CHARGER_EOC_CURRENT_LIMIT_MIN;
		current_bits = uamp / MAX14577_CHARGER_EOC_CURRENT_LIMIT_STEP;
		break;
	}

	reg_data = current_bits << CHGCTRL5_EOCS_SHIFT;

	return max14577_update_reg(chg->max14577->regmap,
			MAX14577_CHG_REG_CHG_CTRL5, CHGCTRL5_EOCS_MASK,
			reg_data);
}