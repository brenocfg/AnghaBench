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
struct iwl_mvm {int /*<<< orphan*/  async_handlers_wk; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fwrt; int /*<<< orphan*/  scan_timeout_dwork; int /*<<< orphan*/  cs_tx_unblock_dwork; int /*<<< orphan*/  status; int /*<<< orphan*/  add_stream_wk; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_FIRMWARE_RUNNING ; 
 int /*<<< orphan*/  __iwl_mvm_mac_stop (struct iwl_mvm*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_fw_free_dump_desc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mac_stop(struct ieee80211_hw *hw)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	flush_work(&mvm->async_handlers_wk);
	flush_work(&mvm->add_stream_wk);

	/*
	 * Lock and clear the firmware running bit here already, so that
	 * new commands coming in elsewhere, e.g. from debugfs, will not
	 * be able to proceed. This is important here because one of those
	 * debugfs files causes the firmware dump to be triggered, and if we
	 * don't stop debugfs accesses before canceling that it could be
	 * retriggered after we flush it but before we've cleared the bit.
	 */
	clear_bit(IWL_MVM_STATUS_FIRMWARE_RUNNING, &mvm->status);

	cancel_delayed_work_sync(&mvm->cs_tx_unblock_dwork);
	cancel_delayed_work_sync(&mvm->scan_timeout_dwork);
	iwl_fw_free_dump_desc(&mvm->fwrt);

	mutex_lock(&mvm->mutex);
	__iwl_mvm_mac_stop(mvm);
	mutex_unlock(&mvm->mutex);

	/*
	 * The worker might have been waiting for the mutex, let it run and
	 * discover that its list is now empty.
	 */
	cancel_work_sync(&mvm->async_handlers_wk);
}