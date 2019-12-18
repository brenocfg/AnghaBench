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
struct iwl_mvm {TYPE_1__* fw; } ;
struct ieee80211_vif {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_TDLS_CHANNEL_SWITCH ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_power_update_mac (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_tdls_config (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_tdls_sta_count (struct iwl_mvm*,struct ieee80211_vif*) ; 

void iwl_mvm_recalc_tdls_state(struct iwl_mvm *mvm, struct ieee80211_vif *vif,
			       bool sta_added)
{
	int tdls_sta_cnt = iwl_mvm_tdls_sta_count(mvm, vif);

	/* when the first peer joins, send a power update first */
	if (tdls_sta_cnt == 1 && sta_added)
		iwl_mvm_power_update_mac(mvm);

	/* Configure the FW with TDLS peer info only if TDLS channel switch
	 * capability is set.
	 * TDLS config data is used currently only in TDLS channel switch code.
	 * Supposed to serve also TDLS buffer station which is not implemneted
	 * yet in FW*/
	if (fw_has_capa(&mvm->fw->ucode_capa,
			IWL_UCODE_TLV_CAPA_TDLS_CHANNEL_SWITCH))
		iwl_mvm_tdls_config(mvm, vif);

	/* when the last peer leaves, send a power update last */
	if (tdls_sta_cnt == 0 && !sta_added)
		iwl_mvm_power_update_mac(mvm);
}