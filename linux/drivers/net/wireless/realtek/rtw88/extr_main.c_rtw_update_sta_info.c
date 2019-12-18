#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
struct rtw_sta_info {int rssi_level; int bw_mode; int stbc_en; int ldpc_en; int rf_type; int wireless_set; int sgi_enable; int vht_enable; int ra_mask; int rate_id; struct ieee80211_sta* sta; } ;
struct rtw_hal {scalar_t__ current_band_type; } ;
struct TYPE_6__ {int nss; } ;
struct rtw_efuse {TYPE_2__ hw_cap; } ;
struct rtw_dev {struct rtw_hal hal; struct rtw_efuse efuse; } ;
struct TYPE_5__ {int* rx_mask; } ;
struct TYPE_8__ {int cap; scalar_t__ ht_supported; TYPE_1__ mcs; } ;
struct TYPE_7__ {int cap; scalar_t__ vht_supported; } ;
struct ieee80211_sta {int* supp_rates; int bandwidth; TYPE_4__ ht_cap; TYPE_3__ vht_cap; } ;

/* Variables and functions */
 int HT_LDPC_EN ; 
 int HT_STBC_EN ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
#define  IEEE80211_STA_RX_BW_40 129 
#define  IEEE80211_STA_RX_BW_80 128 
 int IEEE80211_VHT_CAP_RXLDPC ; 
 int IEEE80211_VHT_CAP_RXSTBC_MASK ; 
 int IEEE80211_VHT_CAP_SHORT_GI_80 ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int RA_MASK_CCK_IN_HT ; 
 int RA_MASK_CCK_IN_VHT ; 
 int RA_MASK_HT_RATES ; 
 int RA_MASK_HT_RATES_1SS ; 
 int RA_MASK_OFDM_IN_HT_2G ; 
 int RA_MASK_OFDM_IN_HT_5G ; 
 int RA_MASK_OFDM_IN_VHT ; 
 int RA_MASK_VHT_RATES ; 
 int RA_MASK_VHT_RATES_1SS ; 
 int RF_1T1R ; 
 int RF_2T2R ; 
 scalar_t__ RTW_BAND_2G ; 
 scalar_t__ RTW_BAND_5G ; 
 int RTW_CHANNEL_WIDTH_20 ; 
 int RTW_CHANNEL_WIDTH_40 ; 
 int RTW_CHANNEL_WIDTH_80 ; 
 int VHT_LDPC_EN ; 
 int VHT_STBC_EN ; 
 int WIRELESS_CCK ; 
 int WIRELESS_HT ; 
 int WIRELESS_OFDM ; 
 int WIRELESS_VHT ; 
 int get_rate_id (int,int,int) ; 
 int get_vht_ra_mask (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_fw_send_ra_info (struct rtw_dev*,struct rtw_sta_info*) ; 

void rtw_update_sta_info(struct rtw_dev *rtwdev, struct rtw_sta_info *si)
{
	struct ieee80211_sta *sta = si->sta;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	struct rtw_hal *hal = &rtwdev->hal;
	u8 rssi_level;
	u8 wireless_set;
	u8 bw_mode;
	u8 rate_id;
	u8 rf_type = RF_1T1R;
	u8 stbc_en = 0;
	u8 ldpc_en = 0;
	u8 tx_num = 1;
	u64 ra_mask = 0;
	bool is_vht_enable = false;
	bool is_support_sgi = false;

	if (sta->vht_cap.vht_supported) {
		is_vht_enable = true;
		ra_mask |= get_vht_ra_mask(sta);
		if (sta->vht_cap.cap & IEEE80211_VHT_CAP_RXSTBC_MASK)
			stbc_en = VHT_STBC_EN;
		if (sta->vht_cap.cap & IEEE80211_VHT_CAP_RXLDPC)
			ldpc_en = VHT_LDPC_EN;
		if (sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_80)
			is_support_sgi = true;
	} else if (sta->ht_cap.ht_supported) {
		ra_mask |= (sta->ht_cap.mcs.rx_mask[NL80211_BAND_5GHZ] << 20) |
			   (sta->ht_cap.mcs.rx_mask[NL80211_BAND_2GHZ] << 12);
		if (sta->ht_cap.cap & IEEE80211_HT_CAP_RX_STBC)
			stbc_en = HT_STBC_EN;
		if (sta->ht_cap.cap & IEEE80211_HT_CAP_LDPC_CODING)
			ldpc_en = HT_LDPC_EN;
		if (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20 ||
		    sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40)
			is_support_sgi = true;
	}

	if (hal->current_band_type == RTW_BAND_5G) {
		ra_mask |= (u64)sta->supp_rates[NL80211_BAND_5GHZ] << 4;
		if (sta->vht_cap.vht_supported) {
			ra_mask &= RA_MASK_VHT_RATES | RA_MASK_OFDM_IN_VHT;
			wireless_set = WIRELESS_OFDM | WIRELESS_VHT;
		} else if (sta->ht_cap.ht_supported) {
			ra_mask &= RA_MASK_HT_RATES | RA_MASK_OFDM_IN_HT_5G;
			wireless_set = WIRELESS_OFDM | WIRELESS_HT;
		} else {
			wireless_set = WIRELESS_OFDM;
		}
	} else if (hal->current_band_type == RTW_BAND_2G) {
		ra_mask |= sta->supp_rates[NL80211_BAND_2GHZ];
		if (sta->vht_cap.vht_supported) {
			ra_mask &= RA_MASK_VHT_RATES | RA_MASK_CCK_IN_VHT |
				   RA_MASK_OFDM_IN_VHT;
			wireless_set = WIRELESS_CCK | WIRELESS_OFDM |
				       WIRELESS_HT | WIRELESS_VHT;
		} else if (sta->ht_cap.ht_supported) {
			ra_mask &= RA_MASK_HT_RATES | RA_MASK_CCK_IN_HT |
				   RA_MASK_OFDM_IN_HT_2G;
			wireless_set = WIRELESS_CCK | WIRELESS_OFDM |
				       WIRELESS_HT;
		} else if (sta->supp_rates[0] <= 0xf) {
			wireless_set = WIRELESS_CCK;
		} else {
			wireless_set = WIRELESS_CCK | WIRELESS_OFDM;
		}
	} else {
		rtw_err(rtwdev, "Unknown band type\n");
		wireless_set = 0;
	}

	if (efuse->hw_cap.nss == 1) {
		ra_mask &= RA_MASK_VHT_RATES_1SS;
		ra_mask &= RA_MASK_HT_RATES_1SS;
	}

	switch (sta->bandwidth) {
	case IEEE80211_STA_RX_BW_80:
		bw_mode = RTW_CHANNEL_WIDTH_80;
		break;
	case IEEE80211_STA_RX_BW_40:
		bw_mode = RTW_CHANNEL_WIDTH_40;
		break;
	default:
		bw_mode = RTW_CHANNEL_WIDTH_20;
		break;
	}

	if (sta->vht_cap.vht_supported && ra_mask & 0xffc00000) {
		tx_num = 2;
		rf_type = RF_2T2R;
	} else if (sta->ht_cap.ht_supported && ra_mask & 0xfff00000) {
		tx_num = 2;
		rf_type = RF_2T2R;
	}

	rate_id = get_rate_id(wireless_set, bw_mode, tx_num);

	if (wireless_set != WIRELESS_CCK) {
		rssi_level = si->rssi_level;
		if (rssi_level == 0)
			ra_mask &= 0xffffffffffffffffULL;
		else if (rssi_level == 1)
			ra_mask &= 0xfffffffffffffff0ULL;
		else if (rssi_level == 2)
			ra_mask &= 0xffffffffffffefe0ULL;
		else if (rssi_level == 3)
			ra_mask &= 0xffffffffffffcfc0ULL;
		else if (rssi_level == 4)
			ra_mask &= 0xffffffffffff8f80ULL;
		else if (rssi_level >= 5)
			ra_mask &= 0xffffffffffff0f00ULL;
	}

	si->bw_mode = bw_mode;
	si->stbc_en = stbc_en;
	si->ldpc_en = ldpc_en;
	si->rf_type = rf_type;
	si->wireless_set = wireless_set;
	si->sgi_enable = is_support_sgi;
	si->vht_enable = is_vht_enable;
	si->ra_mask = ra_mask;
	si->rate_id = rate_id;

	rtw_fw_send_ra_info(rtwdev, si);
}