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
struct iwl_mvm {int max_scans; scalar_t__* scan_uid_status; TYPE_1__* fw; int /*<<< orphan*/  hw; int /*<<< orphan*/  status; int /*<<< orphan*/  roc_done_wk; int /*<<< orphan*/  accu_radio_stats; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_RESTART_REQUESTED ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_UMAC_SCAN ; 
 scalar_t__ WARN_ONCE (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iterate_interfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_async_handlers_purge (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_cleanup_iterator ; 
 int /*<<< orphan*/  iwl_mvm_del_aux_sta (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_stop_device (struct iwl_mvm*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void __iwl_mvm_mac_stop(struct iwl_mvm *mvm)
{
	lockdep_assert_held(&mvm->mutex);

	/* firmware counters are obviously reset now, but we shouldn't
	 * partially track so also clear the fw_reset_accu counters.
	 */
	memset(&mvm->accu_radio_stats, 0, sizeof(mvm->accu_radio_stats));

	/* async_handlers_wk is now blocked */

	/*
	 * The work item could be running or queued if the
	 * ROC time event stops just as we get here.
	 */
	flush_work(&mvm->roc_done_wk);

	iwl_mvm_stop_device(mvm);

	iwl_mvm_async_handlers_purge(mvm);
	/* async_handlers_list is empty and will stay empty: HW is stopped */

	/* the fw is stopped, the aux sta is dead: clean up driver state */
	iwl_mvm_del_aux_sta(mvm);

	/*
	 * Clear IN_HW_RESTART and HW_RESTART_REQUESTED flag when stopping the
	 * hw (as restart_complete() won't be called in this case) and mac80211
	 * won't execute the restart.
	 * But make sure to cleanup interfaces that have gone down before/during
	 * HW restart was requested.
	 */
	if (test_and_clear_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) ||
	    test_and_clear_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED,
			       &mvm->status))
		ieee80211_iterate_interfaces(mvm->hw, 0,
					     iwl_mvm_cleanup_iterator, mvm);

	/* We shouldn't have any UIDs still set.  Loop over all the UIDs to
	 * make sure there's nothing left there and warn if any is found.
	 */
	if (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_UMAC_SCAN)) {
		int i;

		for (i = 0; i < mvm->max_scans; i++) {
			if (WARN_ONCE(mvm->scan_uid_status[i],
				      "UMAC scan UID %d status was not cleaned\n",
				      i))
				mvm->scan_uid_status[i] = 0;
		}
	}
}