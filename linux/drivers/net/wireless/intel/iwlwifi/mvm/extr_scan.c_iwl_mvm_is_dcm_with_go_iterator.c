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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm_vif {TYPE_1__* phy_ctxt; } ;
struct iwl_is_dcm_with_go_iterator_data {int is_dcm_with_p2p_go; struct ieee80211_vif* current_vif; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ p2p; } ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_is_dcm_with_go_iterator(void *_data, u8 *mac,
					    struct ieee80211_vif *vif)
{
	struct iwl_is_dcm_with_go_iterator_data *data = _data;
	struct iwl_mvm_vif *other_mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_vif *curr_mvmvif =
		iwl_mvm_vif_from_mac80211(data->current_vif);

	/* exclude the given vif */
	if (vif == data->current_vif)
		return;

	if (vif->type == NL80211_IFTYPE_AP && vif->p2p &&
	    other_mvmvif->phy_ctxt && curr_mvmvif->phy_ctxt &&
	    other_mvmvif->phy_ctxt->id != curr_mvmvif->phy_ctxt->id)
		data->is_dcm_with_p2p_go = true;
}