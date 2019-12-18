#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct rtl_sta_info {scalar_t__ wireless_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;
struct rtl_phy {int dummy; } ;
struct rtl_priv {TYPE_1__ mac80211; struct rtl_phy phy; } ;
struct rtl_hal {scalar_t__ current_bandtype; } ;
struct ieee80211_tx_rate {int idx; } ;
struct ieee80211_sta {scalar_t__ bandwidth; scalar_t__ drv_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_MODE_MCS8_RIX ; 
 int /*<<< orphan*/  AC_MODE_MCS9_RIX ; 
 int A_MODE_MAX_RIX ; 
 scalar_t__ BAND_ON_2_4G ; 
 int B_MODE_MAX_RIX ; 
 int G_MODE_MAX_RIX ; 
 scalar_t__ IEEE80211_STA_RX_BW_20 ; 
 int N_MODE_MCS15_RIX ; 
 int N_MODE_MCS7_RIX ; 
#define  RF_2T2R 130 
#define  RF_3T3R 129 
#define  RF_4T4R 128 
 scalar_t__ WIRELESS_MODE_A ; 
 scalar_t__ WIRELESS_MODE_AC_24G ; 
 scalar_t__ WIRELESS_MODE_AC_5G ; 
 scalar_t__ WIRELESS_MODE_B ; 
 scalar_t__ WIRELESS_MODE_G ; 
 scalar_t__ WIRELESS_MODE_N_24G ; 
 scalar_t__ WIRELESS_MODE_N_5G ; 
 int get_rf_type (struct rtl_phy*) ; 
 int /*<<< orphan*/  ieee80211_rate_set_vht (struct ieee80211_tx_rate*,int /*<<< orphan*/ ,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 scalar_t__ rtl_is_special_data (int /*<<< orphan*/ ,struct sk_buff*,int,int) ; 

__attribute__((used)) static u8 _rtl_rc_get_highest_rix(struct rtl_priv *rtlpriv,
				  struct ieee80211_sta *sta,
				  struct sk_buff *skb, bool not_data)
{
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_sta_info *sta_entry = NULL;
	u16 wireless_mode = 0;
	u8 nss;
	struct ieee80211_tx_rate rate;

	switch (get_rf_type(rtlphy)) {
	case RF_4T4R:
		nss = 4;
		break;
	case RF_3T3R:
		nss = 3;
		break;
	case RF_2T2R:
		nss = 2;
		break;
	default:
		nss = 1;
		break;
	}

	/*
	 *this rate is no use for true rate, firmware
	 *will control rate at all it just used for
	 *1.show in iwconfig in B/G mode
	 *2.in rtl_get_tcb_desc when we check rate is
	 *      1M we will not use FW rate but user rate.
	 */

	if (sta) {
		sta_entry = (struct rtl_sta_info *)sta->drv_priv;
		wireless_mode = sta_entry->wireless_mode;
	}

	if (rtl_is_special_data(rtlpriv->mac80211.hw, skb, true, false) ||
	    not_data) {
		return 0;
	} else {
		if (rtlhal->current_bandtype == BAND_ON_2_4G) {
			if (wireless_mode == WIRELESS_MODE_B) {
				return B_MODE_MAX_RIX;
			} else if (wireless_mode == WIRELESS_MODE_G) {
				return G_MODE_MAX_RIX;
			} else if (wireless_mode == WIRELESS_MODE_N_24G) {
				if (nss == 1)
					return N_MODE_MCS7_RIX;
				else
					return N_MODE_MCS15_RIX;
			} else if (wireless_mode == WIRELESS_MODE_AC_24G) {
				if (sta->bandwidth == IEEE80211_STA_RX_BW_20) {
					ieee80211_rate_set_vht(&rate,
							       AC_MODE_MCS8_RIX,
							       nss);
					goto out;
				} else {
					ieee80211_rate_set_vht(&rate,
							       AC_MODE_MCS9_RIX,
							       nss);
					goto out;
				}
			}
			return 0;
		} else {
			if (wireless_mode == WIRELESS_MODE_A) {
				return A_MODE_MAX_RIX;
			} else if (wireless_mode == WIRELESS_MODE_N_5G) {
				if (nss == 1)
					return N_MODE_MCS7_RIX;
				else
					return N_MODE_MCS15_RIX;
			} else if (wireless_mode == WIRELESS_MODE_AC_5G) {
				if (sta->bandwidth == IEEE80211_STA_RX_BW_20) {
					ieee80211_rate_set_vht(&rate,
							       AC_MODE_MCS8_RIX,
							       nss);
					goto out;
				} else {
					ieee80211_rate_set_vht(&rate,
							       AC_MODE_MCS9_RIX,
							       nss);
					goto out;
				}
			}
			return 0;
		}
	}

out:
	return rate.idx;
}