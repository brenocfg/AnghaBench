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
struct mt76_wcid {int hw_key_idx; int sw_iv; int /*<<< orphan*/  idx; } ;
struct mt76x02_vif {int /*<<< orphan*/  idx; struct mt76_wcid group_wcid; } ;
struct mt76x02_sta {struct mt76_wcid wcid; } ;
struct mt76x02_dev {int /*<<< orphan*/  mt76; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {int keyidx; int cipher; int flags; int /*<<< orphan*/  hw_key_idx; } ;
struct ieee80211_hw {struct mt76x02_dev* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int IEEE80211_KEY_FLAG_RX_MGMT ; 
 int IEEE80211_KEY_FLAG_SW_MGMT_TX ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int SET_KEY ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 scalar_t__ mt76_is_usb (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_wcid_key_setup (int /*<<< orphan*/ *,struct mt76_wcid*,struct ieee80211_key_conf*) ; 
 int mt76x02_mac_shared_key_setup (struct mt76x02_dev*,int /*<<< orphan*/ ,int,struct ieee80211_key_conf*) ; 
 int mt76x02_mac_wcid_set_key (struct mt76x02_dev*,int /*<<< orphan*/ ,struct ieee80211_key_conf*) ; 

int mt76x02_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
		    struct ieee80211_vif *vif, struct ieee80211_sta *sta,
		    struct ieee80211_key_conf *key)
{
	struct mt76x02_dev *dev = hw->priv;
	struct mt76x02_vif *mvif = (struct mt76x02_vif *)vif->drv_priv;
	struct mt76x02_sta *msta;
	struct mt76_wcid *wcid;
	int idx = key->keyidx;
	int ret;

	/* fall back to sw encryption for unsupported ciphers */
	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
	case WLAN_CIPHER_SUITE_WEP104:
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

	/*
	 * In USB AP mode, broadcast/multicast frames are setup in beacon
	 * data registers and sent via HW beacons engine, they require to
	 * be already encrypted.
	 */
	if (mt76_is_usb(dev) &&
	    vif->type == NL80211_IFTYPE_AP &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE))
		return -EOPNOTSUPP;

	msta = sta ? (struct mt76x02_sta *)sta->drv_priv : NULL;
	wcid = msta ? &msta->wcid : &mvif->group_wcid;

	if (cmd == SET_KEY) {
		key->hw_key_idx = wcid->idx;
		wcid->hw_key_idx = idx;
		if (key->flags & IEEE80211_KEY_FLAG_RX_MGMT) {
			key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
			wcid->sw_iv = true;
		}
	} else {
		if (idx == wcid->hw_key_idx) {
			wcid->hw_key_idx = -1;
			wcid->sw_iv = false;
		}

		key = NULL;
	}
	mt76_wcid_key_setup(&dev->mt76, wcid, key);

	if (!msta) {
		if (key || wcid->hw_key_idx == idx) {
			ret = mt76x02_mac_wcid_set_key(dev, wcid->idx, key);
			if (ret)
				return ret;
		}

		return mt76x02_mac_shared_key_setup(dev, mvif->idx, idx, key);
	}

	return mt76x02_mac_wcid_set_key(dev, msta->wcid.idx, key);
}