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
struct ieee80211_vif_chanctx_switch {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum ieee80211_chanctx_switch_mode { ____Placeholder_ieee80211_chanctx_switch_mode } ieee80211_chanctx_switch_mode ;

/* Variables and functions */
#define  CHANCTX_SWMODE_REASSIGN_VIF 129 
#define  CHANCTX_SWMODE_SWAP_CONTEXTS 128 
 int EOPNOTSUPP ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int iwl_mvm_switch_vif_chanctx_reassign (struct iwl_mvm*,struct ieee80211_vif_chanctx_switch*) ; 
 int iwl_mvm_switch_vif_chanctx_swap (struct iwl_mvm*,struct ieee80211_vif_chanctx_switch*) ; 

__attribute__((used)) static int iwl_mvm_switch_vif_chanctx(struct ieee80211_hw *hw,
				      struct ieee80211_vif_chanctx_switch *vifs,
				      int n_vifs,
				      enum ieee80211_chanctx_switch_mode mode)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	int ret;

	/* we only support a single-vif right now */
	if (n_vifs > 1)
		return -EOPNOTSUPP;

	switch (mode) {
	case CHANCTX_SWMODE_SWAP_CONTEXTS:
		ret = iwl_mvm_switch_vif_chanctx_swap(mvm, vifs);
		break;
	case CHANCTX_SWMODE_REASSIGN_VIF:
		ret = iwl_mvm_switch_vif_chanctx_reassign(mvm, vifs);
		break;
	default:
		ret = -EOPNOTSUPP;
		break;
	}

	return ret;
}