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
struct iwl_mvm {TYPE_1__* hw; int /*<<< orphan*/  rx_sync_waitq; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int iwl_mvm_is_radio_killed (struct iwl_mvm*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_mvm_set_rfkill_state(struct iwl_mvm *mvm)
{
	bool state = iwl_mvm_is_radio_killed(mvm);

	if (state)
		wake_up(&mvm->rx_sync_waitq);

	wiphy_rfkill_set_hw_state(mvm->hw->wiphy, state);
}