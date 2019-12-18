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
struct mt7603_sta {struct mt76_wcid wcid; } ;
struct mt7603_vif {struct mt7603_sta sta; } ;
struct mt7603_dev {int /*<<< orphan*/  mt76; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {int keyidx; int cipher; int flags; int /*<<< orphan*/  hw_key_idx; } ;
struct ieee80211_hw {struct mt7603_dev* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int SET_KEY ; 
#define  WLAN_CIPHER_SUITE_CCMP 129 
#define  WLAN_CIPHER_SUITE_TKIP 128 
 int mt7603_wtbl_set_key (struct mt7603_dev*,int /*<<< orphan*/ ,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  mt76_wcid_key_setup (int /*<<< orphan*/ *,struct mt76_wcid*,struct ieee80211_key_conf*) ; 

__attribute__((used)) static int
mt7603_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
	       struct ieee80211_vif *vif, struct ieee80211_sta *sta,
	       struct ieee80211_key_conf *key)
{
	struct mt7603_dev *dev = hw->priv;
	struct mt7603_vif *mvif = (struct mt7603_vif *)vif->drv_priv;
	struct mt7603_sta *msta = sta ? (struct mt7603_sta *)sta->drv_priv :
				  &mvif->sta;
	struct mt76_wcid *wcid = &msta->wcid;
	int idx = key->keyidx;

	/* fall back to sw encryption for unsupported ciphers */
	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_TKIP:
	case WLAN_CIPHER_SUITE_CCMP:
		break;
	default:
		return -EOPNOTSUPP;
	}

	/*
	 * The hardware does not support per-STA RX GTK, fall back
	 * to software mode for these.
	 */
	if ((vif->type == NL80211_IFTYPE_ADHOC ||
	     vif->type == NL80211_IFTYPE_MESH_POINT) &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		return -EOPNOTSUPP;

	if (cmd == SET_KEY) {
		key->hw_key_idx = wcid->idx;
		wcid->hw_key_idx = idx;
	} else {
		if (idx == wcid->hw_key_idx)
			wcid->hw_key_idx = -1;

		key = NULL;
	}
	mt76_wcid_key_setup(&dev->mt76, wcid, key);

	return mt7603_wtbl_set_key(dev, wcid->idx, key);
}