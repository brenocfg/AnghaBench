#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct iwl_mvm_vif {struct ieee80211_key_conf** ap_early_keys; int /*<<< orphan*/  ap_ibss_active; } ;
struct iwl_mvm_sta {int /*<<< orphan*/ * ptk_pn; } ;
struct iwl_mvm_key_pn {TYPE_4__* q; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  status; TYPE_3__* trans; } ;
struct ieee80211_vif {int /*<<< orphan*/  type; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  pn; } ;
struct ieee80211_key_seq {TYPE_5__ ccmp; } ;
struct ieee80211_key_conf {int keyidx; int cipher; int flags; void* hw_key_idx; } ;
struct ieee80211_hw {TYPE_2__* cipher_schemes; int /*<<< orphan*/  n_cipher_schemes; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;
struct TYPE_12__ {scalar_t__ swcrypto; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pn; } ;
struct TYPE_9__ {int num_rx_queues; TYPE_1__* trans_cfg; } ;
struct TYPE_8__ {int cipher; } ;
struct TYPE_7__ {int /*<<< orphan*/  gen2; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ieee80211_key_conf**) ; 
#define  DISABLE_KEY 138 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_CCMP_PN_LEN ; 
 int IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int IEEE80211_KEY_FLAG_PUT_IV_SPACE ; 
 int IEEE80211_KEY_FLAG_PUT_MIC_SPACE ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int IWL_MAX_TID_COUNT ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  MFP_CAPABLE ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  SET_KEY 137 
 void* STA_KEY_IDX_INVALID ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 136 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_128 135 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_256 134 
#define  WLAN_CIPHER_SUITE_CCMP 133 
#define  WLAN_CIPHER_SUITE_GCMP 132 
#define  WLAN_CIPHER_SUITE_GCMP_256 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  ieee80211_get_key_rx_seq (struct ieee80211_key_conf*,int,struct ieee80211_key_seq*) ; 
 int /*<<< orphan*/  ieee80211_hw_check (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_rx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int iwl_mvm_remove_sta_key (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*) ; 
 int iwl_mvm_set_sta_key (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*,struct ieee80211_key_conf*,void*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 TYPE_6__ iwlwifi_mod_params ; 
 int /*<<< orphan*/  kfree_rcu (struct iwl_mvm_key_pn*,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_key_pn* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct iwl_mvm_key_pn*) ; 
 struct iwl_mvm_key_pn* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  struct_size (struct iwl_mvm_key_pn*,int,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __iwl_mvm_mac_set_key(struct ieee80211_hw *hw,
				 enum set_key_cmd cmd,
				 struct ieee80211_vif *vif,
				 struct ieee80211_sta *sta,
				 struct ieee80211_key_conf *key)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_sta *mvmsta;
	struct iwl_mvm_key_pn *ptk_pn;
	int keyidx = key->keyidx;
	int ret, i;
	u8 key_offset;

	if (iwlwifi_mod_params.swcrypto) {
		IWL_DEBUG_MAC80211(mvm, "leave - hwcrypto disabled\n");
		return -EOPNOTSUPP;
	}

	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_TKIP:
		if (!mvm->trans->trans_cfg->gen2) {
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
			key->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE;
		} else if (vif->type == NL80211_IFTYPE_STATION) {
			key->flags |= IEEE80211_KEY_FLAG_PUT_MIC_SPACE;
		} else {
			IWL_DEBUG_MAC80211(mvm, "Use SW encryption for TKIP\n");
			return -EOPNOTSUPP;
		}
		break;
	case WLAN_CIPHER_SUITE_CCMP:
	case WLAN_CIPHER_SUITE_GCMP:
	case WLAN_CIPHER_SUITE_GCMP_256:
		if (!iwl_mvm_has_new_tx_api(mvm))
			key->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE;
		break;
	case WLAN_CIPHER_SUITE_AES_CMAC:
	case WLAN_CIPHER_SUITE_BIP_GMAC_128:
	case WLAN_CIPHER_SUITE_BIP_GMAC_256:
		WARN_ON_ONCE(!ieee80211_hw_check(hw, MFP_CAPABLE));
		break;
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		if (vif->type == NL80211_IFTYPE_STATION)
			break;
		if (iwl_mvm_has_new_tx_api(mvm))
			return -EOPNOTSUPP;
		/* support HW crypto on TX */
		return 0;
	default:
		/* currently FW supports only one optional cipher scheme */
		if (hw->n_cipher_schemes &&
		    hw->cipher_schemes->cipher == key->cipher)
			key->flags |= IEEE80211_KEY_FLAG_PUT_IV_SPACE;
		else
			return -EOPNOTSUPP;
	}

	switch (cmd) {
	case SET_KEY:
		if ((vif->type == NL80211_IFTYPE_ADHOC ||
		     vif->type == NL80211_IFTYPE_AP) && !sta) {
			/*
			 * GTK on AP interface is a TX-only key, return 0;
			 * on IBSS they're per-station and because we're lazy
			 * we don't support them for RX, so do the same.
			 * CMAC/GMAC in AP/IBSS modes must be done in software.
			 */
			if (key->cipher == WLAN_CIPHER_SUITE_AES_CMAC ||
			    key->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_128 ||
			    key->cipher == WLAN_CIPHER_SUITE_BIP_GMAC_256)
				ret = -EOPNOTSUPP;
			else
				ret = 0;

			if (key->cipher != WLAN_CIPHER_SUITE_GCMP &&
			    key->cipher != WLAN_CIPHER_SUITE_GCMP_256 &&
			    !iwl_mvm_has_new_tx_api(mvm)) {
				key->hw_key_idx = STA_KEY_IDX_INVALID;
				break;
			}

			if (!mvmvif->ap_ibss_active) {
				for (i = 0;
				     i < ARRAY_SIZE(mvmvif->ap_early_keys);
				     i++) {
					if (!mvmvif->ap_early_keys[i]) {
						mvmvif->ap_early_keys[i] = key;
						break;
					}
				}

				if (i >= ARRAY_SIZE(mvmvif->ap_early_keys))
					ret = -ENOSPC;

				break;
			}
		}

		/* During FW restart, in order to restore the state as it was,
		 * don't try to reprogram keys we previously failed for.
		 */
		if (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) &&
		    key->hw_key_idx == STA_KEY_IDX_INVALID) {
			IWL_DEBUG_MAC80211(mvm,
					   "skip invalid idx key programming during restart\n");
			ret = 0;
			break;
		}

		if (!test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status) &&
		    sta && iwl_mvm_has_new_rx_api(mvm) &&
		    key->flags & IEEE80211_KEY_FLAG_PAIRWISE &&
		    (key->cipher == WLAN_CIPHER_SUITE_CCMP ||
		     key->cipher == WLAN_CIPHER_SUITE_GCMP ||
		     key->cipher == WLAN_CIPHER_SUITE_GCMP_256)) {
			struct ieee80211_key_seq seq;
			int tid, q;

			mvmsta = iwl_mvm_sta_from_mac80211(sta);
			WARN_ON(rcu_access_pointer(mvmsta->ptk_pn[keyidx]));
			ptk_pn = kzalloc(struct_size(ptk_pn, q,
						     mvm->trans->num_rx_queues),
					 GFP_KERNEL);
			if (!ptk_pn) {
				ret = -ENOMEM;
				break;
			}

			for (tid = 0; tid < IWL_MAX_TID_COUNT; tid++) {
				ieee80211_get_key_rx_seq(key, tid, &seq);
				for (q = 0; q < mvm->trans->num_rx_queues; q++)
					memcpy(ptk_pn->q[q].pn[tid],
					       seq.ccmp.pn,
					       IEEE80211_CCMP_PN_LEN);
			}

			rcu_assign_pointer(mvmsta->ptk_pn[keyidx], ptk_pn);
		}

		/* in HW restart reuse the index, otherwise request a new one */
		if (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status))
			key_offset = key->hw_key_idx;
		else
			key_offset = STA_KEY_IDX_INVALID;

		IWL_DEBUG_MAC80211(mvm, "set hwcrypto key\n");
		ret = iwl_mvm_set_sta_key(mvm, vif, sta, key, key_offset);
		if (ret) {
			IWL_WARN(mvm, "set key failed\n");
			key->hw_key_idx = STA_KEY_IDX_INVALID;
			/*
			 * can't add key for RX, but we don't need it
			 * in the device for TX so still return 0,
			 * unless we have new TX API where we cannot
			 * put key material into the TX_CMD
			 */
			if (iwl_mvm_has_new_tx_api(mvm))
				ret = -EOPNOTSUPP;
			else
				ret = 0;
		}

		break;
	case DISABLE_KEY:
		ret = -ENOENT;
		for (i = 0; i < ARRAY_SIZE(mvmvif->ap_early_keys); i++) {
			if (mvmvif->ap_early_keys[i] == key) {
				mvmvif->ap_early_keys[i] = NULL;
				ret = 0;
			}
		}

		/* found in pending list - don't do anything else */
		if (ret == 0)
			break;

		if (key->hw_key_idx == STA_KEY_IDX_INVALID) {
			ret = 0;
			break;
		}

		if (sta && iwl_mvm_has_new_rx_api(mvm) &&
		    key->flags & IEEE80211_KEY_FLAG_PAIRWISE &&
		    (key->cipher == WLAN_CIPHER_SUITE_CCMP ||
		     key->cipher == WLAN_CIPHER_SUITE_GCMP ||
		     key->cipher == WLAN_CIPHER_SUITE_GCMP_256)) {
			mvmsta = iwl_mvm_sta_from_mac80211(sta);
			ptk_pn = rcu_dereference_protected(
						mvmsta->ptk_pn[keyidx],
						lockdep_is_held(&mvm->mutex));
			RCU_INIT_POINTER(mvmsta->ptk_pn[keyidx], NULL);
			if (ptk_pn)
				kfree_rcu(ptk_pn, rcu_head);
		}

		IWL_DEBUG_MAC80211(mvm, "disable hwcrypto key\n");
		ret = iwl_mvm_remove_sta_key(mvm, vif, sta, key);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}