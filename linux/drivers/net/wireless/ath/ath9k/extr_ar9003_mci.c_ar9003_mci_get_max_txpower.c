#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  concur_tx; } ;
struct TYPE_4__ {TYPE_1__ mci; } ;
struct ath_hw {TYPE_2__ btcoex_hw; } ;

/* Variables and functions */
 int ATH_BTCOEX_HT20_MAX_TXPOWER ; 
 int ATH_BTCOEX_HT40_MAX_TXPOWER ; 
 scalar_t__ CTL_2GHT20 ; 
 scalar_t__ CTL_2GHT40 ; 

u16 ar9003_mci_get_max_txpower(struct ath_hw *ah, u8 ctlmode)
{
	if (!ah->btcoex_hw.mci.concur_tx)
		goto out;

	if (ctlmode == CTL_2GHT20)
		return ATH_BTCOEX_HT20_MAX_TXPOWER;
	else if (ctlmode == CTL_2GHT40)
		return ATH_BTCOEX_HT40_MAX_TXPOWER;

out:
	return -1;
}