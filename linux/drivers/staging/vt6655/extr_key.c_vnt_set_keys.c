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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vnt_private {int dummy; } ;
struct ieee80211_bss_conf {scalar_t__ bssid; } ;
struct ieee80211_vif {struct ieee80211_bss_conf bss_conf; } ;
struct ieee80211_sta {int /*<<< orphan*/ * addr; } ;
struct ieee80211_key_conf {int cipher; int flags; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;

/* Variables and functions */
 int IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int /*<<< orphan*/  KEY_CTL_CCMP ; 
 int /*<<< orphan*/  KEY_CTL_TKIP ; 
 int /*<<< orphan*/  KEY_CTL_WEP ; 
 int /*<<< orphan*/  MACvDisableKeyEntry (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_KEY_TABLE ; 
 int /*<<< orphan*/  VNT_KEY_DEFAULTKEY ; 
 int /*<<< orphan*/  VNT_KEY_GROUP_ADDRESS ; 
 int /*<<< orphan*/  VNT_KEY_PAIRWISE ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  vnt_set_keymode (struct ieee80211_hw*,int /*<<< orphan*/ *,struct ieee80211_key_conf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int vnt_set_keys(struct ieee80211_hw *hw, struct ieee80211_sta *sta,
		 struct ieee80211_vif *vif, struct ieee80211_key_conf *key)
{
	struct ieee80211_bss_conf *conf = &vif->bss_conf;
	struct vnt_private *priv = hw->priv;
	u8 *mac_addr = NULL;
	u8 key_dec_mode = 0;
	int ret = 0;
	u32 u;

	if (sta)
		mac_addr = &sta->addr[0];

	switch (key->cipher) {
	case 0:
		for (u = 0 ; u < MAX_KEY_TABLE; u++)
			MACvDisableKeyEntry(priv, u);
		return ret;

	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
		for (u = 0; u < MAX_KEY_TABLE; u++)
			MACvDisableKeyEntry(priv, u);

		vnt_set_keymode(hw, mac_addr,
				key, VNT_KEY_DEFAULTKEY, KEY_CTL_WEP, true);

		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;

		return ret;
	case WLAN_CIPHER_SUITE_TKIP:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;

		key_dec_mode = KEY_CTL_TKIP;

		break;
	case WLAN_CIPHER_SUITE_CCMP:
		key_dec_mode = KEY_CTL_CCMP;

		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
	}

	if (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) {
		vnt_set_keymode(hw, mac_addr,
				key, VNT_KEY_PAIRWISE, key_dec_mode, true);
	} else {
		vnt_set_keymode(hw, mac_addr,
				key, VNT_KEY_DEFAULTKEY, key_dec_mode, true);

		vnt_set_keymode(hw, (u8 *)conf->bssid,
				key, VNT_KEY_GROUP_ADDRESS, key_dec_mode, true);
	}

	return 0;
}