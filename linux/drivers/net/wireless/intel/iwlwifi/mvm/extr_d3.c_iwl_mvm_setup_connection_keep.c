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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct iwl_wowlan_status {int /*<<< orphan*/  non_qos_seq_ctr; int /*<<< orphan*/  replay_ctr; TYPE_2__* gtk; scalar_t__ num_of_gtk_rekeys; int /*<<< orphan*/  wakeup_reasons; } ;
struct iwl_mvm_vif {int seqno_valid; scalar_t__ seqno; } ;
struct iwl_mvm_d3_gtk_iter_data {int find_phase; int cipher; int /*<<< orphan*/  last_gtk; int /*<<< orphan*/  num_keys; scalar_t__ unhandled_cipher; struct iwl_wowlan_status* status; struct iwl_mvm* mvm; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  bssid; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct ieee80211_key_conf {int cipher; int keylen; int /*<<< orphan*/  key; int /*<<< orphan*/  keyidx; } ;
typedef  int /*<<< orphan*/  __be64 ;
struct TYPE_4__ {int /*<<< orphan*/  tkip_mic_key; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_DEAUTH ; 
 int IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_MISSED_BEACON ; 
 int /*<<< orphan*/  NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY ; 
#define  WLAN_CIPHER_SUITE_CCMP 129 
#define  WLAN_CIPHER_SUITE_TKIP 128 
 int WLAN_KEY_LEN_CCMP ; 
 int WLAN_KEY_LEN_TKIP ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ieee80211_gtk_rekey_add (struct ieee80211_vif*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  ieee80211_gtk_rekey_notify (struct ieee80211_vif*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_iter_keys (int /*<<< orphan*/ ,struct ieee80211_vif*,int /*<<< orphan*/ ,struct iwl_mvm_d3_gtk_iter_data*) ; 
 int /*<<< orphan*/  iwl_mvm_d3_update_keys ; 
 int /*<<< orphan*/  iwl_mvm_set_key_rx_seq (struct iwl_mvm*,int /*<<< orphan*/ *,struct iwl_wowlan_status*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  iwlmvm_wowlan_gtk_idx (TYPE_2__*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool iwl_mvm_setup_connection_keep(struct iwl_mvm *mvm,
					  struct ieee80211_vif *vif,
					  struct iwl_wowlan_status *status)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_d3_gtk_iter_data gtkdata = {
		.mvm = mvm,
		.status = status,
	};
	u32 disconnection_reasons =
		IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_MISSED_BEACON |
		IWL_WOWLAN_WAKEUP_BY_DISCONNECTION_ON_DEAUTH;

	if (!status || !vif->bss_conf.bssid)
		return false;

	if (le32_to_cpu(status->wakeup_reasons) & disconnection_reasons)
		return false;

	/* find last GTK that we used initially, if any */
	gtkdata.find_phase = true;
	ieee80211_iter_keys(mvm->hw, vif,
			    iwl_mvm_d3_update_keys, &gtkdata);
	/* not trying to keep connections with MFP/unhandled ciphers */
	if (gtkdata.unhandled_cipher)
		return false;
	if (!gtkdata.num_keys)
		goto out;
	if (!gtkdata.last_gtk)
		return false;

	/*
	 * invalidate all other GTKs that might still exist and update
	 * the one that we used
	 */
	gtkdata.find_phase = false;
	ieee80211_iter_keys(mvm->hw, vif,
			    iwl_mvm_d3_update_keys, &gtkdata);

	if (status->num_of_gtk_rekeys) {
		struct ieee80211_key_conf *key;
		struct {
			struct ieee80211_key_conf conf;
			u8 key[32];
		} conf = {
			.conf.cipher = gtkdata.cipher,
			.conf.keyidx =
				iwlmvm_wowlan_gtk_idx(&status->gtk[0]),
		};
		__be64 replay_ctr;

		switch (gtkdata.cipher) {
		case WLAN_CIPHER_SUITE_CCMP:
			conf.conf.keylen = WLAN_KEY_LEN_CCMP;
			memcpy(conf.conf.key, status->gtk[0].key,
			       WLAN_KEY_LEN_CCMP);
			break;
		case WLAN_CIPHER_SUITE_TKIP:
			conf.conf.keylen = WLAN_KEY_LEN_TKIP;
			memcpy(conf.conf.key, status->gtk[0].key, 16);
			/* leave TX MIC key zeroed, we don't use it anyway */
			memcpy(conf.conf.key +
			       NL80211_TKIP_DATA_OFFSET_RX_MIC_KEY,
			       status->gtk[0].tkip_mic_key, 8);
			break;
		}

		key = ieee80211_gtk_rekey_add(vif, &conf.conf);
		if (IS_ERR(key))
			return false;
		iwl_mvm_set_key_rx_seq(mvm, key, status);

		replay_ctr =
			cpu_to_be64(le64_to_cpu(status->replay_ctr));

		ieee80211_gtk_rekey_notify(vif, vif->bss_conf.bssid,
					   (void *)&replay_ctr, GFP_KERNEL);
	}

out:
	mvmvif->seqno_valid = true;
	/* +0x10 because the set API expects next-to-use, not last-used */
	mvmvif->seqno = le16_to_cpu(status->non_qos_seq_ctr) + 0x10;

	return true;
}