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
struct TYPE_3__ {int bw; int nss; } ;
struct rtw_efuse {TYPE_1__ hw_cap; } ;
struct rtw_dev {struct rtw_efuse efuse; } ;
struct TYPE_4__ {int* rx_mask; void* rx_highest; int /*<<< orphan*/  tx_params; } ;
struct ieee80211_sta_ht_cap {int ht_supported; int cap; TYPE_2__ mcs; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int IEEE80211_HT_CAP_DSSSCCK40 ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_MAX_AMSDU ; 
 int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_MAX_AMPDU_64K ; 
 int /*<<< orphan*/  IEEE80211_HT_MCS_TX_DEFINED ; 
 int /*<<< orphan*/  IEEE80211_HT_MPDU_DENSITY_16 ; 
 int /*<<< orphan*/  RTW_CHANNEL_WIDTH_40 ; 
 void* cpu_to_le16 (int) ; 

__attribute__((used)) static void rtw_init_ht_cap(struct rtw_dev *rtwdev,
			    struct ieee80211_sta_ht_cap *ht_cap)
{
	struct rtw_efuse *efuse = &rtwdev->efuse;

	ht_cap->ht_supported = true;
	ht_cap->cap = 0;
	ht_cap->cap |= IEEE80211_HT_CAP_SGI_20 |
			IEEE80211_HT_CAP_MAX_AMSDU |
			IEEE80211_HT_CAP_LDPC_CODING |
			(1 << IEEE80211_HT_CAP_RX_STBC_SHIFT);
	if (efuse->hw_cap.bw & BIT(RTW_CHANNEL_WIDTH_40))
		ht_cap->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
				IEEE80211_HT_CAP_DSSSCCK40 |
				IEEE80211_HT_CAP_SGI_40;
	ht_cap->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_cap->ampdu_density = IEEE80211_HT_MPDU_DENSITY_16;
	ht_cap->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;
	if (efuse->hw_cap.nss > 1) {
		ht_cap->mcs.rx_mask[0] = 0xFF;
		ht_cap->mcs.rx_mask[1] = 0xFF;
		ht_cap->mcs.rx_mask[4] = 0x01;
		ht_cap->mcs.rx_highest = cpu_to_le16(300);
	} else {
		ht_cap->mcs.rx_mask[0] = 0xFF;
		ht_cap->mcs.rx_mask[1] = 0x00;
		ht_cap->mcs.rx_mask[4] = 0x01;
		ht_cap->mcs.rx_highest = cpu_to_le16(150);
	}
}