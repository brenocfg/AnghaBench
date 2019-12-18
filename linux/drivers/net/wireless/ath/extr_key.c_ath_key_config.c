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
typedef  int u8 ;
struct ieee80211_vif {int type; int* addr; } ;
struct ieee80211_sta {int* addr; } ;
struct ieee80211_key_conf {int cipher; int keylen; int* key; int flags; int keyidx; } ;
struct ath_keyval {int kv_len; int* kv_val; int /*<<< orphan*/  kv_type; } ;
struct ath_common {int crypt_caps; int /*<<< orphan*/  tkip_keymap; int /*<<< orphan*/  keymap; int /*<<< orphan*/  ccmp_keymap; } ;
typedef  int /*<<< orphan*/  hk ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_CIPHER_AES_CCM ; 
 int /*<<< orphan*/  ATH_CIPHER_CLR ; 
 int /*<<< orphan*/  ATH_CIPHER_TKIP ; 
 int /*<<< orphan*/  ATH_CIPHER_WEP ; 
 int ATH_CRYPT_CAP_MIC_COMBINED ; 
 int EIO ; 
 int ENOSPC ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
#define  NL80211_IFTYPE_ADHOC 133 
#define  NL80211_IFTYPE_AP 132 
 scalar_t__ WARN_ON (int) ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int ath_hw_set_keycache_entry (struct ath_common*,int,struct ath_keyval*,int const*) ; 
 int ath_reserve_key_cache_slot (struct ath_common*,int) ; 
 int ath_setkey_tkip (struct ath_common*,int,int*,struct ath_keyval*,int const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (struct ath_keyval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

int ath_key_config(struct ath_common *common,
			  struct ieee80211_vif *vif,
			  struct ieee80211_sta *sta,
			  struct ieee80211_key_conf *key)
{
	struct ath_keyval hk;
	const u8 *mac = NULL;
	u8 gmac[ETH_ALEN];
	int ret = 0;
	int idx;

	memset(&hk, 0, sizeof(hk));

	switch (key->cipher) {
	case 0:
		hk.kv_type = ATH_CIPHER_CLR;
		break;
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		hk.kv_type = ATH_CIPHER_WEP;
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		hk.kv_type = ATH_CIPHER_TKIP;
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		hk.kv_type = ATH_CIPHER_AES_CCM;
		break;
	default:
		return -EOPNOTSUPP;
	}

	hk.kv_len = key->keylen;
	if (key->keylen)
		memcpy(hk.kv_val, key->key, key->keylen);

	if (!(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) {
		switch (vif->type) {
		case NL80211_IFTYPE_AP:
			memcpy(gmac, vif->addr, ETH_ALEN);
			gmac[0] |= 0x01;
			mac = gmac;
			idx = ath_reserve_key_cache_slot(common, key->cipher);
			break;
		case NL80211_IFTYPE_ADHOC:
			if (!sta) {
				idx = key->keyidx;
				break;
			}
			memcpy(gmac, sta->addr, ETH_ALEN);
			gmac[0] |= 0x01;
			mac = gmac;
			idx = ath_reserve_key_cache_slot(common, key->cipher);
			break;
		default:
			idx = key->keyidx;
			break;
		}
	} else if (key->keyidx) {
		if (WARN_ON(!sta))
			return -EOPNOTSUPP;
		mac = sta->addr;

		if (vif->type != NL80211_IFTYPE_AP) {
			/* Only keyidx 0 should be used with unicast key, but
			 * allow this for client mode for now. */
			idx = key->keyidx;
		} else
			return -EIO;
	} else {
		if (WARN_ON(!sta))
			return -EOPNOTSUPP;
		mac = sta->addr;

		idx = ath_reserve_key_cache_slot(common, key->cipher);
	}

	if (idx < 0)
		return -ENOSPC; /* no free key cache entries */

	if (key->cipher == WLAN_CIPHER_SUITE_TKIP)
		ret = ath_setkey_tkip(common, idx, key->key, &hk, mac,
				      vif->type == NL80211_IFTYPE_AP);
	else
		ret = ath_hw_set_keycache_entry(common, idx, &hk, mac);

	if (!ret)
		return -EIO;

	set_bit(idx, common->keymap);
	if (key->cipher == WLAN_CIPHER_SUITE_CCMP)
		set_bit(idx, common->ccmp_keymap);

	if (key->cipher == WLAN_CIPHER_SUITE_TKIP) {
		set_bit(idx + 64, common->keymap);
		set_bit(idx, common->tkip_keymap);
		set_bit(idx + 64, common->tkip_keymap);
		if (!(common->crypt_caps & ATH_CRYPT_CAP_MIC_COMBINED)) {
			set_bit(idx + 32, common->keymap);
			set_bit(idx + 64 + 32, common->keymap);
			set_bit(idx + 32, common->tkip_keymap);
			set_bit(idx + 64 + 32, common->tkip_keymap);
		}
	}

	return idx;
}