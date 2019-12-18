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
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_RECOVERY_END_OF_RECOVERY ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_send_recovery_cmd (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_teardown_tdls_peers (struct iwl_mvm*) ; 
 int iwl_mvm_update_quotas (struct iwl_mvm*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_restart_complete(struct iwl_mvm *mvm)
{
	int ret;

	mutex_lock(&mvm->mutex);

	clear_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status);

	ret = iwl_mvm_update_quotas(mvm, true, NULL);
	if (ret)
		IWL_ERR(mvm, "Failed to update quotas after restart (%d)\n",
			ret);

	iwl_mvm_send_recovery_cmd(mvm, ERROR_RECOVERY_END_OF_RECOVERY);

	/*
	 * If we have TDLS peers, remove them. We don't know the last seqno/PN
	 * of packets the FW sent out, so we must reconnect.
	 */
	iwl_mvm_teardown_tdls_peers(mvm);

	mutex_unlock(&mvm->mutex);
}