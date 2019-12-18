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
typedef  int u32 ;
struct iwl_mvm_vif {int /*<<< orphan*/  ap_ibss_active; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  txpower; } ;

/* Variables and functions */
 int BSS_CHANGED_BANDWIDTH ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_ERP_CTS_PROT ; 
 int BSS_CHANGED_FTM_RESPONDER ; 
 int BSS_CHANGED_HT ; 
 int BSS_CHANGED_QOS ; 
 int BSS_CHANGED_TXPOWER ; 
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*,...) ; 
 int iwl_mvm_ftm_start_responder (struct iwl_mvm*,struct ieee80211_vif*) ; 
 scalar_t__ iwl_mvm_mac_ctxt_beacon_changed (struct iwl_mvm*,struct ieee80211_vif*) ; 
 scalar_t__ iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,struct ieee80211_vif*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_set_tx_power (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 

__attribute__((used)) static void
iwl_mvm_bss_info_changed_ap_ibss(struct iwl_mvm *mvm,
				 struct ieee80211_vif *vif,
				 struct ieee80211_bss_conf *bss_conf,
				 u32 changes)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);

	/* Changes will be applied when the AP/IBSS is started */
	if (!mvmvif->ap_ibss_active)
		return;

	if (changes & (BSS_CHANGED_ERP_CTS_PROT | BSS_CHANGED_HT |
		       BSS_CHANGED_BANDWIDTH | BSS_CHANGED_QOS) &&
	    iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL))
		IWL_ERR(mvm, "failed to update MAC %pM\n", vif->addr);

	/* Need to send a new beacon template to the FW */
	if (changes & BSS_CHANGED_BEACON &&
	    iwl_mvm_mac_ctxt_beacon_changed(mvm, vif))
		IWL_WARN(mvm, "Failed updating beacon data\n");

	if (changes & BSS_CHANGED_TXPOWER) {
		IWL_DEBUG_CALIB(mvm, "Changing TX Power to %d\n",
				bss_conf->txpower);
		iwl_mvm_set_tx_power(mvm, vif, bss_conf->txpower);
	}

	if (changes & BSS_CHANGED_FTM_RESPONDER) {
		int ret = iwl_mvm_ftm_start_responder(mvm, vif);

		if (ret)
			IWL_WARN(mvm, "Failed to enable FTM responder (%d)\n",
				 ret);
	}

}