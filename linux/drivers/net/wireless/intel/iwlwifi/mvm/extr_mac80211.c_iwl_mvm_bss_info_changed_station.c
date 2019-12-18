#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ bf_enabled; scalar_t__ last_cqm_event; scalar_t__ ave_beacon_signal; } ;
struct iwl_mvm_vif {TYPE_3__ bf_data; int /*<<< orphan*/  ap_sta_id; int /*<<< orphan*/  beacon_stats; scalar_t__ associated; int /*<<< orphan*/ * bssid; } ;
struct iwl_mvm {TYPE_2__* fw; int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int beacon_int; scalar_t__ he_support; } ;
struct ieee80211_vif {scalar_t__ mu_mimo_owner; int /*<<< orphan*/  addr; scalar_t__ p2p; TYPE_1__ bss_conf; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  txpower; scalar_t__ assoc; int /*<<< orphan*/  bssid; } ;
struct TYPE_8__ {int /*<<< orphan*/  disable_11ax; } ;
struct TYPE_6__ {int /*<<< orphan*/  ucode_capa; } ;

/* Variables and functions */
 int BSS_CHANGED_ARP_FILTER ; 
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON_INFO ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_CQM ; 
 int BSS_CHANGED_MU_GROUPS ; 
 int BSS_CHANGED_P2P_PS ; 
 int BSS_CHANGED_PS ; 
 int BSS_CHANGED_QOS ; 
 int BSS_CHANGED_TXPOWER ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_SMPS_AUTOMATIC ; 
 int /*<<< orphan*/  IEEE80211_SMPS_DYNAMIC ; 
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_mvm*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_MVM_INVALID_STA ; 
 int /*<<< orphan*/  IWL_MVM_SMPS_REQ_PROT ; 
 int /*<<< orphan*/  IWL_MVM_SMPS_REQ_TT ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_RESTART_REQUESTED ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int /*<<< orphan*/  IWL_UCODE_TLV_CAPA_UMAC_SCAN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ fw_has_capa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_bt_coex_vif_change (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_cfg_he_sta (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_config_scan (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_configure_bcast_filter (struct iwl_mvm*) ; 
 int iwl_mvm_enable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,struct ieee80211_vif*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_recalc_tsf_id (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_power_update_mac (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_power_vif_assoc (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwl_mvm_protect_session (struct iwl_mvm*,struct ieee80211_vif*,int,int,int,int) ; 
 int /*<<< orphan*/  iwl_mvm_recalc_multicast (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_request_statistics (struct iwl_mvm*,int) ; 
 int iwl_mvm_rm_sta_id (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_set_tx_power (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_sf_update (struct iwl_mvm*,struct ieee80211_vif*,int) ; 
 int /*<<< orphan*/  iwl_mvm_stop_session_protection (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_update_mu_groups (struct iwl_mvm*,struct ieee80211_vif*) ; 
 int iwl_mvm_update_quotas (struct iwl_mvm*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_update_smps (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 TYPE_4__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_bss_info_changed_station(struct iwl_mvm *mvm,
					     struct ieee80211_vif *vif,
					     struct ieee80211_bss_conf *bss_conf,
					     u32 changes)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	int ret;

	/*
	 * Re-calculate the tsf id, as the master-slave relations depend on the
	 * beacon interval, which was not known when the station interface was
	 * added.
	 */
	if (changes & BSS_CHANGED_ASSOC && bss_conf->assoc) {
		if (vif->bss_conf.he_support &&
		    !iwlwifi_mod_params.disable_11ax)
			iwl_mvm_cfg_he_sta(mvm, vif, mvmvif->ap_sta_id);

		iwl_mvm_mac_ctxt_recalc_tsf_id(mvm, vif);
	}

	/* Update MU EDCA params */
	if (changes & BSS_CHANGED_QOS && mvmvif->associated &&
	    bss_conf->assoc && vif->bss_conf.he_support &&
	    !iwlwifi_mod_params.disable_11ax)
		iwl_mvm_cfg_he_sta(mvm, vif, mvmvif->ap_sta_id);

	/*
	 * If we're not associated yet, take the (new) BSSID before associating
	 * so the firmware knows. If we're already associated, then use the old
	 * BSSID here, and we'll send a cleared one later in the CHANGED_ASSOC
	 * branch for disassociation below.
	 */
	if (changes & BSS_CHANGED_BSSID && !mvmvif->associated)
		memcpy(mvmvif->bssid, bss_conf->bssid, ETH_ALEN);

	ret = iwl_mvm_mac_ctxt_changed(mvm, vif, false, mvmvif->bssid);
	if (ret)
		IWL_ERR(mvm, "failed to update MAC %pM\n", vif->addr);

	/* after sending it once, adopt mac80211 data */
	memcpy(mvmvif->bssid, bss_conf->bssid, ETH_ALEN);
	mvmvif->associated = bss_conf->assoc;

	if (changes & BSS_CHANGED_ASSOC) {
		if (bss_conf->assoc) {
			/* clear statistics to get clean beacon counter */
			iwl_mvm_request_statistics(mvm, true);
			memset(&mvmvif->beacon_stats, 0,
			       sizeof(mvmvif->beacon_stats));

			/* add quota for this interface */
			ret = iwl_mvm_update_quotas(mvm, true, NULL);
			if (ret) {
				IWL_ERR(mvm, "failed to update quotas\n");
				return;
			}

			if (test_bit(IWL_MVM_STATUS_IN_HW_RESTART,
				     &mvm->status)) {
				/*
				 * If we're restarting then the firmware will
				 * obviously have lost synchronisation with
				 * the AP. It will attempt to synchronise by
				 * itself, but we can make it more reliable by
				 * scheduling a session protection time event.
				 *
				 * The firmware needs to receive a beacon to
				 * catch up with synchronisation, use 110% of
				 * the beacon interval.
				 *
				 * Set a large maximum delay to allow for more
				 * than a single interface.
				 */
				u32 dur = (11 * vif->bss_conf.beacon_int) / 10;
				iwl_mvm_protect_session(mvm, vif, dur, dur,
							5 * dur, false);
			}

			iwl_mvm_sf_update(mvm, vif, false);
			iwl_mvm_power_vif_assoc(mvm, vif);
			if (vif->p2p) {
				iwl_mvm_update_smps(mvm, vif,
						    IWL_MVM_SMPS_REQ_PROT,
						    IEEE80211_SMPS_DYNAMIC);
			}
		} else if (mvmvif->ap_sta_id != IWL_MVM_INVALID_STA) {
			/*
			 * If update fails - SF might be running in associated
			 * mode while disassociated - which is forbidden.
			 */
			ret = iwl_mvm_sf_update(mvm, vif, false);
			WARN_ONCE(ret &&
				  !test_bit(IWL_MVM_STATUS_HW_RESTART_REQUESTED,
					    &mvm->status),
				  "Failed to update SF upon disassociation\n");

			/*
			 * If we get an assert during the connection (after the
			 * station has been added, but before the vif is set
			 * to associated), mac80211 will re-add the station and
			 * then configure the vif. Since the vif is not
			 * associated, we would remove the station here and
			 * this would fail the recovery.
			 */
			if (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART,
				      &mvm->status)) {
				/*
				 * Remove AP station now that
				 * the MAC is unassoc
				 */
				ret = iwl_mvm_rm_sta_id(mvm, vif,
							mvmvif->ap_sta_id);
				if (ret)
					IWL_ERR(mvm,
						"failed to remove AP station\n");

				mvmvif->ap_sta_id = IWL_MVM_INVALID_STA;
			}

			/* remove quota for this interface */
			ret = iwl_mvm_update_quotas(mvm, false, NULL);
			if (ret)
				IWL_ERR(mvm, "failed to update quotas\n");

			/* this will take the cleared BSSID from bss_conf */
			ret = iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL);
			if (ret)
				IWL_ERR(mvm,
					"failed to update MAC %pM (clear after unassoc)\n",
					vif->addr);
		}

		/*
		 * The firmware tracks the MU-MIMO group on its own.
		 * However, on HW restart we should restore this data.
		 */
		if (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) &&
		    (changes & BSS_CHANGED_MU_GROUPS) && vif->mu_mimo_owner) {
			ret = iwl_mvm_update_mu_groups(mvm, vif);
			if (ret)
				IWL_ERR(mvm,
					"failed to update VHT MU_MIMO groups\n");
		}

		iwl_mvm_recalc_multicast(mvm);
		iwl_mvm_configure_bcast_filter(mvm);

		/* reset rssi values */
		mvmvif->bf_data.ave_beacon_signal = 0;

		iwl_mvm_bt_coex_vif_change(mvm);
		iwl_mvm_update_smps(mvm, vif, IWL_MVM_SMPS_REQ_TT,
				    IEEE80211_SMPS_AUTOMATIC);
		if (fw_has_capa(&mvm->fw->ucode_capa,
				IWL_UCODE_TLV_CAPA_UMAC_SCAN))
			iwl_mvm_config_scan(mvm);
	}

	if (changes & BSS_CHANGED_BEACON_INFO) {
		/*
		 * We received a beacon from the associated AP so
		 * remove the session protection.
		 */
		iwl_mvm_stop_session_protection(mvm, vif);

		iwl_mvm_sf_update(mvm, vif, false);
		WARN_ON(iwl_mvm_enable_beacon_filter(mvm, vif, 0));
	}

	if (changes & (BSS_CHANGED_PS | BSS_CHANGED_P2P_PS | BSS_CHANGED_QOS |
		       /*
			* Send power command on every beacon change,
			* because we may have not enabled beacon abort yet.
			*/
		       BSS_CHANGED_BEACON_INFO)) {
		ret = iwl_mvm_power_update_mac(mvm);
		if (ret)
			IWL_ERR(mvm, "failed to update power mode\n");
	}

	if (changes & BSS_CHANGED_TXPOWER) {
		IWL_DEBUG_CALIB(mvm, "Changing TX Power to %d\n",
				bss_conf->txpower);
		iwl_mvm_set_tx_power(mvm, vif, bss_conf->txpower);
	}

	if (changes & BSS_CHANGED_CQM) {
		IWL_DEBUG_MAC80211(mvm, "cqm info_changed\n");
		/* reset cqm events tracking */
		mvmvif->bf_data.last_cqm_event = 0;
		if (mvmvif->bf_data.bf_enabled) {
			ret = iwl_mvm_enable_beacon_filter(mvm, vif, 0);
			if (ret)
				IWL_ERR(mvm,
					"failed to update CQM thresholds\n");
		}
	}

	if (changes & BSS_CHANGED_ARP_FILTER) {
		IWL_DEBUG_MAC80211(mvm, "arp filter changed\n");
		iwl_mvm_configure_bcast_filter(mvm);
	}
}