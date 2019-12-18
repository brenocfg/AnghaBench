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
struct ath_btcoex_hw {int /*<<< orphan*/  btactive_gpio; } ;
struct ath_hw {struct ath_btcoex_hw btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GPIO_INPUT_EN_VAL ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_EN_VAL_BT_ACTIVE_BB ; 
 int AR_GPIO_INPUT_EN_VAL_BT_FREQUENCY_DEF ; 
 int AR_GPIO_INPUT_EN_VAL_BT_PRIORITY_DEF ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_MUX1 ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_MUX1_BT_ACTIVE ; 
 int /*<<< orphan*/  AR_SREV_SOC (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_gpio_request_in (struct ath_hw*,int /*<<< orphan*/ ,char*) ; 

void ath9k_hw_btcoex_init_2wire(struct ath_hw *ah)
{
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	/* connect bt_active to baseband */
	REG_CLR_BIT(ah, AR_GPIO_INPUT_EN_VAL,
		    (AR_GPIO_INPUT_EN_VAL_BT_PRIORITY_DEF |
		     AR_GPIO_INPUT_EN_VAL_BT_FREQUENCY_DEF));

	REG_SET_BIT(ah, AR_GPIO_INPUT_EN_VAL,
		    AR_GPIO_INPUT_EN_VAL_BT_ACTIVE_BB);

	/* Set input mux for bt_active to gpio pin */
	if (!AR_SREV_SOC(ah))
		REG_RMW_FIELD(ah, AR_GPIO_INPUT_MUX1,
			      AR_GPIO_INPUT_MUX1_BT_ACTIVE,
			      btcoex_hw->btactive_gpio);

	/* Configure the desired gpio port for input */
	ath9k_hw_gpio_request_in(ah, btcoex_hw->btactive_gpio,
				 "ath9k-btactive");
}