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
typedef  scalar_t__ u8 ;
struct rtw_sec_desc {scalar_t__ total_cam_num; } ;
struct rtw_dev {int /*<<< orphan*/  mutex; struct rtw_sec_desc sec; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_key_conf {int cipher; int flags; scalar_t__ keyidx; scalar_t__ hw_key_idx; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;
typedef  enum set_key_cmd { ____Placeholder_set_key_cmd } set_key_cmd ;

/* Variables and functions */
#define  DISABLE_KEY 137 
 int ENOSPC ; 
 int ENOTSUPP ; 
 int EOPNOTSUPP ; 
 int IEEE80211_KEY_FLAG_GENERATE_IV ; 
 int IEEE80211_KEY_FLAG_GENERATE_MMIC ; 
 int IEEE80211_KEY_FLAG_PAIRWISE ; 
 int IEEE80211_KEY_FLAG_SW_MGMT_TX ; 
 scalar_t__ RTW_CAM_AES ; 
 scalar_t__ RTW_CAM_TKIP ; 
 scalar_t__ RTW_CAM_WEP104 ; 
 scalar_t__ RTW_CAM_WEP40 ; 
#define  SET_KEY 136 
#define  WLAN_CIPHER_SUITE_AES_CMAC 135 
#define  WLAN_CIPHER_SUITE_BIP_CMAC_256 134 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_128 133 
#define  WLAN_CIPHER_SUITE_BIP_GMAC_256 132 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_sec_clear_cam (struct rtw_dev*,struct rtw_sec_desc*,scalar_t__) ; 
 scalar_t__ rtw_sec_get_free_cam (struct rtw_sec_desc*) ; 
 int /*<<< orphan*/  rtw_sec_write_cam (struct rtw_dev*,struct rtw_sec_desc*,struct ieee80211_sta*,struct ieee80211_key_conf*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int rtw_ops_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
			   struct ieee80211_vif *vif, struct ieee80211_sta *sta,
			   struct ieee80211_key_conf *key)
{
	struct rtw_dev *rtwdev = hw->priv;
	struct rtw_sec_desc *sec = &rtwdev->sec;
	u8 hw_key_type;
	u8 hw_key_idx;
	int ret = 0;

	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
		hw_key_type = RTW_CAM_WEP40;
		break;
	case WLAN_CIPHER_SUITE_WEP104:
		hw_key_type = RTW_CAM_WEP104;
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		hw_key_type = RTW_CAM_TKIP;
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		hw_key_type = RTW_CAM_AES;
		key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
		break;
	case WLAN_CIPHER_SUITE_AES_CMAC:
	case WLAN_CIPHER_SUITE_BIP_CMAC_256:
	case WLAN_CIPHER_SUITE_BIP_GMAC_128:
	case WLAN_CIPHER_SUITE_BIP_GMAC_256:
		/* suppress error messages */
		return -EOPNOTSUPP;
	default:
		return -ENOTSUPP;
	}

	mutex_lock(&rtwdev->mutex);

	if (key->flags & IEEE80211_KEY_FLAG_PAIRWISE) {
		hw_key_idx = rtw_sec_get_free_cam(sec);
	} else {
		/* multiple interfaces? */
		hw_key_idx = key->keyidx;
	}

	if (hw_key_idx > sec->total_cam_num) {
		ret = -ENOSPC;
		goto out;
	}

	switch (cmd) {
	case SET_KEY:
		/* need sw generated IV */
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		key->hw_key_idx = hw_key_idx;
		rtw_sec_write_cam(rtwdev, sec, sta, key,
				  hw_key_type, hw_key_idx);
		break;
	case DISABLE_KEY:
		rtw_sec_clear_cam(rtwdev, sec, key->hw_key_idx);
		break;
	}

out:
	mutex_unlock(&rtwdev->mutex);

	return ret;
}