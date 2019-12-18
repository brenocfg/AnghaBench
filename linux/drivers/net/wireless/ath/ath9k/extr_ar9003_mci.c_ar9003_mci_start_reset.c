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
typedef  int /*<<< orphan*/  u32 ;
struct ath9k_hw_mci {scalar_t__ bt_state; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;
struct ath_common {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 int /*<<< orphan*/  MCI ; 
 scalar_t__ MCI_BT_AWAKE ; 
 scalar_t__ MCI_BT_CAL ; 
 scalar_t__ MCI_BT_CAL_START ; 
 int /*<<< orphan*/  MCI_GPM ; 
 int /*<<< orphan*/  MCI_GPM_BT_CAL_DONE ; 
 int /*<<< orphan*/  MCI_GPM_SET_CAL_TYPE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCI_GPM_WLAN_CAL_GRANT ; 
 int /*<<< orphan*/  ar9003_mci_2g5g_changed (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_mci_disable_interrupt (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_enable_interrupt (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_send_message (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ ar9003_mci_wait_for_gpm (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

bool ar9003_mci_start_reset(struct ath_hw *ah, struct ath9k_channel *chan)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_hw_mci *mci_hw = &ah->btcoex_hw.mci;
	u32 payload[4] = {0, 0, 0, 0};

	ar9003_mci_2g5g_changed(ah, IS_CHAN_2GHZ(chan));

	if (mci_hw->bt_state != MCI_BT_CAL_START)
		return false;

	mci_hw->bt_state = MCI_BT_CAL;

	/*
	 * MCI FIX: disable mci interrupt here. This is to avoid
	 * SW_MSG_DONE or RX_MSG bits to trigger MCI_INT and
	 * lead to mci_intr reentry.
	 */
	ar9003_mci_disable_interrupt(ah);

	MCI_GPM_SET_CAL_TYPE(payload, MCI_GPM_WLAN_CAL_GRANT);
	ar9003_mci_send_message(ah, MCI_GPM, 0, payload,
				16, true, false);

	/* Wait BT calibration to be completed for 25ms */

	if (ar9003_mci_wait_for_gpm(ah, MCI_GPM_BT_CAL_DONE,
				    0, 25000))
		ath_dbg(common, MCI, "MCI BT_CAL_DONE received\n");
	else
		ath_dbg(common, MCI,
			"MCI BT_CAL_DONE not received\n");

	mci_hw->bt_state = MCI_BT_AWAKE;
	/* MCI FIX: enable mci interrupt here */
	ar9003_mci_enable_interrupt(ah);

	return true;
}