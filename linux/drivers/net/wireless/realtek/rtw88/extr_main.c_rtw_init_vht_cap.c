#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ ptcl; int nss; } ;
struct rtw_efuse {TYPE_1__ hw_cap; } ;
struct rtw_dev {struct rtw_efuse efuse; } ;
struct TYPE_4__ {void* tx_highest; void* rx_highest; void* tx_mcs_map; void* rx_mcs_map; } ;
struct ieee80211_sta_vht_cap {int vht_supported; int cap; TYPE_2__ vht_mcs; } ;
typedef  void* __le16 ;

/* Variables and functions */
 scalar_t__ EFUSE_HW_CAP_IGNORE ; 
 scalar_t__ EFUSE_HW_CAP_PTCL_VHT ; 
 int IEEE80211_VHT_CAP_HTC_VHT ; 
 int IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK ; 
 int IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 ; 
 int IEEE80211_VHT_CAP_RXLDPC ; 
 int IEEE80211_VHT_CAP_RXSTBC_1 ; 
 int IEEE80211_VHT_CAP_SHORT_GI_80 ; 
 int IEEE80211_VHT_CAP_TXSTBC ; 
 int IEEE80211_VHT_MCS_NOT_SUPPORTED ; 
 int IEEE80211_VHT_MCS_SUPPORT_0_9 ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void rtw_init_vht_cap(struct rtw_dev *rtwdev,
			     struct ieee80211_sta_vht_cap *vht_cap)
{
	struct rtw_efuse *efuse = &rtwdev->efuse;
	u16 mcs_map;
	__le16 highest;

	if (efuse->hw_cap.ptcl != EFUSE_HW_CAP_IGNORE &&
	    efuse->hw_cap.ptcl != EFUSE_HW_CAP_PTCL_VHT)
		return;

	vht_cap->vht_supported = true;
	vht_cap->cap = IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 |
		       IEEE80211_VHT_CAP_RXLDPC |
		       IEEE80211_VHT_CAP_SHORT_GI_80 |
		       IEEE80211_VHT_CAP_TXSTBC |
		       IEEE80211_VHT_CAP_RXSTBC_1 |
		       IEEE80211_VHT_CAP_HTC_VHT |
		       IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK |
		       0;
	mcs_map = IEEE80211_VHT_MCS_SUPPORT_0_9 << 0 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 4 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 6 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 8 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 10 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 12 |
		  IEEE80211_VHT_MCS_NOT_SUPPORTED << 14;
	if (efuse->hw_cap.nss > 1) {
		highest = cpu_to_le16(780);
		mcs_map |= IEEE80211_VHT_MCS_SUPPORT_0_9 << 2;
	} else {
		highest = cpu_to_le16(390);
		mcs_map |= IEEE80211_VHT_MCS_NOT_SUPPORTED << 2;
	}

	vht_cap->vht_mcs.rx_mcs_map = cpu_to_le16(mcs_map);
	vht_cap->vht_mcs.tx_mcs_map = cpu_to_le16(mcs_map);
	vht_cap->vht_mcs.rx_highest = highest;
	vht_cap->vht_mcs.tx_highest = highest;
}