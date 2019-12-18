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
struct ath_btcoex_hw {int btactive_gpio; int enabled; } ;
struct ath_hw {struct ath_btcoex_hw btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GPIO_PDPU ; 
 int /*<<< orphan*/  AR_SREV_SOC (struct ath_hw*) ; 
#define  ATH_BTCOEX_CFG_2WIRE 131 
#define  ATH_BTCOEX_CFG_3WIRE 130 
#define  ATH_BTCOEX_CFG_MCI 129 
#define  ATH_BTCOEX_CFG_NONE 128 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ath9k_hw_btcoex_enable_2wire (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_btcoex_enable_3wire (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_btcoex_enable_mci (struct ath_hw*) ; 
 int const ath9k_hw_get_btcoex_scheme (struct ath_hw*) ; 

void ath9k_hw_btcoex_enable(struct ath_hw *ah)
{
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	switch (ath9k_hw_get_btcoex_scheme(ah)) {
	case ATH_BTCOEX_CFG_NONE:
		return;
	case ATH_BTCOEX_CFG_2WIRE:
		ath9k_hw_btcoex_enable_2wire(ah);
		break;
	case ATH_BTCOEX_CFG_3WIRE:
		ath9k_hw_btcoex_enable_3wire(ah);
		break;
	case ATH_BTCOEX_CFG_MCI:
		ath9k_hw_btcoex_enable_mci(ah);
		break;
	}

	if (ath9k_hw_get_btcoex_scheme(ah) != ATH_BTCOEX_CFG_MCI &&
	    !AR_SREV_SOC(ah)) {
		REG_RMW(ah, AR_GPIO_PDPU,
			(0x2 << (btcoex_hw->btactive_gpio * 2)),
			(0x3 << (btcoex_hw->btactive_gpio * 2)));
	}

	ah->btcoex_hw.enabled = true;
}