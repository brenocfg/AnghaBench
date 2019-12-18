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
struct iwl_mvm {int /*<<< orphan*/  status; int /*<<< orphan*/  fwrt; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_FW_INI_TIME_POINT_PERIODIC ; 
 int /*<<< orphan*/  IWL_FW_INI_TIME_POINT_POST_INIT ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_RESTART_REQUESTED ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_dbg_tlv_time_point (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_restart_cleanup (struct iwl_mvm*) ; 
 int iwl_mvm_up (struct iwl_mvm*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int __iwl_mvm_mac_start(struct iwl_mvm *mvm)
{
	int ret;

	lockdep_assert_held(&mvm->mutex);

	if (test_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status)) {
		/*
		 * Now convert the HW_RESTART_REQUESTED flag to IN_HW_RESTART
		 * so later code will - from now on - see that we're doing it.
		 */
		set_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);
		clear_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED, &mvm->status);
		/* Clean up some internal and mac80211 state on restart */
		iwl_mvm_restart_cleanup(mvm);
	}
	ret = iwl_mvm_up(mvm);

	iwl_dbg_tlv_time_point(&mvm->fwrt, IWL_FW_INI_TIME_POINT_POST_INIT,
			       NULL);
	iwl_dbg_tlv_time_point(&mvm->fwrt, IWL_FW_INI_TIME_POINT_PERIODIC,
			       NULL);

	if (ret && test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) {
		/* Something went wrong - we need to finish some cleanup
		 * that normally iwl_mvm_mac_restart_complete() below
		 * would do.
		 */
		clear_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);
	}

	return ret;
}