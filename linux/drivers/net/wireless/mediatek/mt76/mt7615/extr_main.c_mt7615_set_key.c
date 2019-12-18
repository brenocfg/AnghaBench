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
struct mt76_wcid {int hw_key_idx; int /*<<< orphan*/  idx; } ;
struct mt7615_sta {struct mt76_wcid wcid; } ;
struct mt7615_vif {struct mt7615_sta sta; } ;
struct mt7615_dev {int /*<<< orphan*/  mt76; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {int keyidx; int cipher; int flags; int /*<<< orphan*/  hw_key_idx; } ;
struct ieee80211_hw {struct mt7615_dev* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_GENERATE_MMIE ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int SET_KEY ; 
#define  WLAN_CIPHER_SUITE_AES_CMAC 136 
#define  WLAN_CIPHER_SUITE_CCMP 135 
#define  WLAN_CIPHER_SUITE_CCMP_256 134 
#define  WLAN_CIPHER_SUITE_GCMP 133 
#define  WLAN_CIPHER_SUITE_GCMP_256 132 
#define  WLAN_CIPHER_SUITE_SMS4 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int mt7615_mac_wtbl_set_key (struct mt7615_dev*,struct mt76_wcid*,struct ieee80211_key_conf*,int) ; 
 int /*<<< orphan*/  mt76_wcid_key_setup (int /*<<< orphan*/ *,struct mt76_wcid*,struct ieee80211_key_conf*) ; 

__attribute__((used)) static int mt7615_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
			  struct ieee80211_vif *vif, struct ieee80211_sta *sta,
			  struct ieee80211_key_conf *key)
{
	struct mt7615_dev *dev = hw->priv;
	struct mt7615_vif *mvif = (struct mt7615_vif *)vif->drv_priv;
	struct mt7615_sta *msta = sta ? (struct mt7615_sta *)sta->drv_priv :
				  &mvif->sta;
	struct mt76_wcid *wcid = &msta->wcid;
	int idx = key->keyidx;

	/* The hardware does not support per-STA RX GTK, fallback
	 * to software mode for these.
	 */
	if ((vif->type == NL80211_IFTYPE_ADHOC ||
	     vif->type == NL80211_IFTYPE_MESH_POINT) &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		return -EOPNOTSUPP;

	/* fall back to sw encryption for unsupported ciphers */
	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_AES_CMAC:
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIE;
		break;
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
	case WLAN_CIPHER_SUITE_TKIP:
	case WLAN_CIPHER_SUITE_CCMP:
	case WLAN_CIPHER_SUITE_CCMP_256:
	case WLAN_CIPHER_SUITE_GCMP:
	case WLAN_CIPHER_SUITE_GCMP_256:
	case WLAN_CIPHER_SUITE_SMS4:
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (cmd == SET_KEY) {
		key->hw_key_idx = wcid->idx;
		wcid->hw_key_idx = idx;
	} else if (idx == wcid->hw_key_idx) {
		wcid->hw_key_idx = -1;
	}
	mt76_wcid_key_setup(&dev->mt76, wcid,
			    cmd == SET_KEY ? key : NULL);

	return mt7615_mac_wtbl_set_key(dev, wcid, key, cmd);
}