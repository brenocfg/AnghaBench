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
struct ath9k_hw_mci {int config; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 int ATH_MCI_CONFIG_DISABLE_AIC ; 

__attribute__((used)) static bool ar9003_hw_is_aic_enabled(struct ath_hw *ah)
{
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;

	/*
	 * Disable AIC for now, until we have all the
	 * HW code and the driver-layer support ready.
	 */
	return false;

	if (mci_hw->config & ATH_MCI_CONFIG_DISABLE_AIC)
		return false;

	return true;
}