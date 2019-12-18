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
struct iwl_mvm_vif {int /*<<< orphan*/  id; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;
typedef  enum iwl_mvm_low_latency_cause { ____Placeholder_iwl_mvm_low_latency_cause } iwl_mvm_low_latency_cause ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_bt_coex_vif_change (struct iwl_mvm*) ; 
 int iwl_mvm_power_update_mac (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_send_low_latency_cmd (struct iwl_mvm*,int,int /*<<< orphan*/ ) ; 
 int iwl_mvm_update_quotas (struct iwl_mvm*,int,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int iwl_mvm_vif_low_latency (struct iwl_mvm_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_vif_set_low_latency (struct iwl_mvm_vif*,int,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_update_low_latency(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			       bool low_latency,
			       enum iwl_mvm_low_latency_cause cause)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int res;
	bool prev;

	lockdep_assert_held(&mvm->mutex);

	prev = iwl_mvm_vif_low_latency(mvmvif);
	iwl_mvm_vif_set_low_latency(mvmvif, low_latency, cause);

	low_latency = iwl_mvm_vif_low_latency(mvmvif);

	if (low_latency == prev)
		return 0;

	iwl_mvm_send_low_latency_cmd(mvm, low_latency, mvmvif->id);

	res = iwl_mvm_update_quotas(mvm, false, NULL);
	if (res)
		return res;

	iwl_mvm_bt_coex_vif_change(mvm);

	return iwl_mvm_power_update_mac(mvm);
}