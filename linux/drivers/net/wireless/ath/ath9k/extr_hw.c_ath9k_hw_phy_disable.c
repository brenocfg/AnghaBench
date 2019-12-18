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
struct ath_hw {int htc_reset_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_RESET_WARM ; 
 int /*<<< orphan*/  ar9003_mci_bt_gain_ctrl (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_init_pll (struct ath_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_reset_reg (struct ath_hw*,int /*<<< orphan*/ ) ; 

bool ath9k_hw_phy_disable(struct ath_hw *ah)
{
	if (ath9k_hw_mci_is_enabled(ah))
		ar9003_mci_bt_gain_ctrl(ah);

	if (!ath9k_hw_set_reset_reg(ah, ATH9K_RESET_WARM))
		return false;

	ath9k_hw_init_pll(ah, NULL);
	ah->htc_reset_init = true;
	return true;
}