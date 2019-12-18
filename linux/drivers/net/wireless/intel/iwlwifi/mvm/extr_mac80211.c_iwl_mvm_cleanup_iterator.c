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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm_vif {int uploaded; int /*<<< orphan*/  probe_resp_data; int /*<<< orphan*/  bf_data; int /*<<< orphan*/ * phy_ctxt; int /*<<< orphan*/  time_event_data; int /*<<< orphan*/  ap_sta_id; } ;
struct iwl_mvm {int /*<<< orphan*/  time_event_lock; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  iwl_mvm_te_clear_data (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_cleanup_iterator(void *data, u8 *mac,
				     struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	mvmvif->uploaded = false;
	mvmvif->ap_sta_id = IWL_MVM_INVALID_STA;

	spin_lock_bh(&mvm->time_event_lock);
	iwl_mvm_te_clear_data(mvm, &mvmvif->time_event_data);
	spin_unlock_bh(&mvm->time_event_lock);

	mvmvif->phy_ctxt = NULL;
	memset(&mvmvif->bf_data, 0, sizeof(mvmvif->bf_data));
	memset(&mvmvif->probe_resp_data, 0, sizeof(mvmvif->probe_resp_data));
}