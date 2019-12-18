#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  unicast_rsc; int /*<<< orphan*/  tsc; } ;
struct TYPE_10__ {int /*<<< orphan*/  pn; } ;
struct TYPE_11__ {TYPE_3__ tsc; int /*<<< orphan*/  unicast_rsc; } ;
union iwl_all_tsc_rsc {TYPE_5__ tkip; TYPE_4__ aes; } ;
typedef  int u64 ;
struct iwl_mvm_d3_gtk_iter_data {int unhandled_cipher; int cipher; TYPE_7__* status; int /*<<< orphan*/  mvm; struct ieee80211_key_conf* last_gtk; scalar_t__ find_phase; int /*<<< orphan*/  num_keys; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  iv32; int /*<<< orphan*/  iv16; } ;
struct ieee80211_key_seq {TYPE_6__ tkip; } ;
struct ieee80211_key_conf {int cipher; int /*<<< orphan*/  tx_pn; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_14__ {scalar_t__ num_of_gtk_rekeys; TYPE_2__* gtk; } ;
struct TYPE_8__ {union iwl_all_tsc_rsc all_tsc_rsc; } ;
struct TYPE_9__ {TYPE_1__ rsc; } ;

/* Variables and functions */
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ieee80211_remove_key (struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  iwl_mvm_set_aes_rx_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  iwl_mvm_set_key_rx_seq (int /*<<< orphan*/ ,struct ieee80211_key_conf*,TYPE_7__*) ; 
 int /*<<< orphan*/  iwl_mvm_set_tkip_rx_seq (int /*<<< orphan*/ ,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  iwl_mvm_tkip_sc_to_seq (int /*<<< orphan*/ *,struct ieee80211_key_seq*) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_d3_update_keys(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif,
				   struct ieee80211_sta *sta,
				   struct ieee80211_key_conf *key,
				   void *_data)
{
	struct iwl_mvm_d3_gtk_iter_data *data = _data;

	if (data->unhandled_cipher)
		return;

	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		/* ignore WEP completely, nothing to do */
		return;
	case WLAN_CIPHER_SUITE_CCMP:
	case WLAN_CIPHER_SUITE_TKIP:
		/* we support these */
		break;
	default:
		/* everything else (even CMAC for MFP) - disconnect from AP */
		data->unhandled_cipher = true;
		return;
	}

	data->num_keys++;

	/*
	 * pairwise key - update sequence counters only;
	 * note that this assumes no TDLS sessions are active
	 */
	if (sta) {
		struct ieee80211_key_seq seq = {};
		union iwl_all_tsc_rsc *sc =
			&data->status->gtk[0].rsc.all_tsc_rsc;

		if (data->find_phase)
			return;

		switch (key->cipher) {
		case WLAN_CIPHER_SUITE_CCMP:
			iwl_mvm_set_aes_rx_seq(data->mvm, sc->aes.unicast_rsc,
					       sta, key);
			atomic64_set(&key->tx_pn, le64_to_cpu(sc->aes.tsc.pn));
			break;
		case WLAN_CIPHER_SUITE_TKIP:
			iwl_mvm_tkip_sc_to_seq(&sc->tkip.tsc, &seq);
			iwl_mvm_set_tkip_rx_seq(sc->tkip.unicast_rsc, key);
			atomic64_set(&key->tx_pn,
				     (u64)seq.tkip.iv16 |
				     ((u64)seq.tkip.iv32 << 16));
			break;
		}

		/* that's it for this key */
		return;
	}

	if (data->find_phase) {
		data->last_gtk = key;
		data->cipher = key->cipher;
		return;
	}

	if (data->status->num_of_gtk_rekeys)
		ieee80211_remove_key(key);
	else if (data->last_gtk == key)
		iwl_mvm_set_key_rx_seq(data->mvm, key, data->status);
}