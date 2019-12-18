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
struct TYPE_2__ {int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm_vif {TYPE_1__ mcast_sta; int /*<<< orphan*/  cab_queue; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  iwl_mvm_disable_txq (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_flush_sta (struct iwl_mvm*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int iwl_mvm_rm_sta_common (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_rm_mcast_sta(struct iwl_mvm *mvm, struct ieee80211_vif *vif)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	lockdep_assert_held(&mvm->mutex);

	iwl_mvm_flush_sta(mvm, &mvmvif->mcast_sta, true, 0);

	iwl_mvm_disable_txq(mvm, NULL, mvmvif->cab_queue, 0, 0);

	ret = iwl_mvm_rm_sta_common(mvm, mvmvif->mcast_sta.sta_id);
	if (ret)
		IWL_WARN(mvm, "Failed sending remove station\n");

	return ret;
}