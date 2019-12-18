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
typedef  scalar_t__ u32 ;
struct ath9k_hw_mci {scalar_t__ bt_state; int unhalt_bt_gpm; } ;
struct TYPE_2__ {struct ath9k_hw_mci mci; } ;
struct ath_hw {TYPE_1__ btcoex_hw; } ;

/* Variables and functions */
 scalar_t__ MCI_BT_SLEEP ; 
 int /*<<< orphan*/  MCI_STATE_REMOTE_SLEEP ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_halt_bt_gpm (struct ath_hw*,int,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_version_query (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_mci_send_coex_wlan_channels (struct ath_hw*,int) ; 
 scalar_t__ ar9003_mci_state (struct ath_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_mci_sync_bt_state(struct ath_hw *ah)
{
	struct ath9k_hw_mci *mci = &ah->btcoex_hw.mci;
	u32 cur_bt_state;

	cur_bt_state = ar9003_mci_state(ah, MCI_STATE_REMOTE_SLEEP);

	if (mci->bt_state != cur_bt_state)
		mci->bt_state = cur_bt_state;

	if (mci->bt_state != MCI_BT_SLEEP) {

		ar9003_mci_send_coex_version_query(ah, true);
		ar9003_mci_send_coex_wlan_channels(ah, true);

		if (mci->unhalt_bt_gpm == true)
			ar9003_mci_send_coex_halt_bt_gpm(ah, false, true);
	}
}