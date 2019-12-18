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
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_dealloc_bcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_send_rm_bcast_sta (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_rm_p2p_bcast_sta(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	int ret;

	lockdep_assert_held(&mvm->mutex);

	ret = iwl_mvm_send_rm_bcast_sta(mvm, vif);

	iwl_mvm_dealloc_bcast_sta(mvm, vif);

	return ret;
}