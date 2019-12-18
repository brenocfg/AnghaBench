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
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  MVM_DEBUGFS_ADD_STA_FILE (int /*<<< orphan*/ ,struct dentry*,int) ; 
 int /*<<< orphan*/  amsdu_len ; 
 scalar_t__ iwl_mvm_has_tlc_offload (struct iwl_mvm*) ; 
 int /*<<< orphan*/  rs_data ; 

void iwl_mvm_sta_add_debugfs(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif,
			     struct ieee80211_sta *sta,
			     struct dentry *dir)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);

	if (iwl_mvm_has_tlc_offload(mvm)) {
		MVM_DEBUGFS_ADD_STA_FILE(rs_data, dir, 0400);
	}
	MVM_DEBUGFS_ADD_STA_FILE(amsdu_len, dir, 0600);
}