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
struct iwl_mvm {int scan_status; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int IWL_MVM_SCAN_REGULAR ; 
 int /*<<< orphan*/  iwl_mvm_scan_stop (struct iwl_mvm*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mac_cancel_hw_scan(struct ieee80211_hw *hw,
				       struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	mutex_lock(&mvm->mutex);

	/* Due to a race condition, it's possible that mac80211 asks
	 * us to stop a hw_scan when it's already stopped.  This can
	 * happen, for instance, if we stopped the scan ourselves,
	 * called ieee80211_scan_completed() and the userspace called
	 * cancel scan scan before ieee80211_scan_work() could run.
	 * To handle that, simply return if the scan is not running.
	*/
	if (mvm->scan_status & IWL_MVM_SCAN_REGULAR)
		iwl_mvm_scan_stop(mvm, IWL_MVM_SCAN_REGULAR, true);

	mutex_unlock(&mvm->mutex);
}