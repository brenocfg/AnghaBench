#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct iwl_mvm_vif {TYPE_2__* phy_ctxt; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* channel; } ;
struct TYPE_3__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int IEEE80211_RC_BW_CHANGED ; 
 int IEEE80211_RC_NSS_CHANGED ; 
 int IEEE80211_RC_SUPP_RATES_CHANGED ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  iwl_mvm_rs_rate_init (struct iwl_mvm*,struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_mvm_sf_update (struct iwl_mvm*,struct ieee80211_vif*,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_sta_rc_update(struct ieee80211_hw *hw,
				  struct ieee80211_vif *vif,
				  struct ieee80211_sta *sta, u32 changed)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	if (changed & (IEEE80211_RC_BW_CHANGED |
		       IEEE80211_RC_SUPP_RATES_CHANGED |
		       IEEE80211_RC_NSS_CHANGED))
		iwl_mvm_rs_rate_init(mvm, sta, mvmvif->phy_ctxt->channel->band,
				     true);

	if (vif->type == NL80211_IFTYPE_STATION &&
	    changed & IEEE80211_RC_NSS_CHANGED)
		iwl_mvm_sf_update(mvm, vif, false);
}