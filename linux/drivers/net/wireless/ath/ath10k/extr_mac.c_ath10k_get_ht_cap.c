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
typedef  int u32 ;
struct TYPE_2__ {int* rx_mask; int /*<<< orphan*/  tx_params; } ;
struct ieee80211_sta_ht_cap {int ht_supported; int cap; TYPE_1__ mcs; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; int /*<<< orphan*/  member_0; } ;
struct ath10k {int ht_cap_info; int cfg_tx_chainmask; int vht_cap_info; int num_rf_chains; int cfg_rx_chainmask; } ;

/* Variables and functions */
 int BIT (int) ; 
 int IEEE80211_HT_CAP_DSSSCCK40 ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_LSIG_TXOP_PROT ; 
 int IEEE80211_HT_CAP_MAX_AMSDU ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int IEEE80211_HT_CAP_RX_STBC_SHIFT ; 
 int IEEE80211_HT_CAP_SGI_20 ; 
 int IEEE80211_HT_CAP_SGI_40 ; 
 int IEEE80211_HT_CAP_SM_PS_SHIFT ; 
 int IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_HT_CAP_TX_STBC ; 
 int /*<<< orphan*/  IEEE80211_HT_MAX_AMPDU_64K ; 
 int /*<<< orphan*/  IEEE80211_HT_MCS_TX_DEFINED ; 
 int /*<<< orphan*/  IEEE80211_HT_MPDU_DENSITY_8 ; 
 int WLAN_HT_CAP_SM_PS_DISABLED ; 
 int WLAN_HT_CAP_SM_PS_DYNAMIC ; 
 int WMI_HT_CAP_DYNAMIC_SMPS ; 
 int WMI_HT_CAP_ENABLED ; 
 int WMI_HT_CAP_HT20_SGI ; 
 int WMI_HT_CAP_HT40_SGI ; 
 int WMI_HT_CAP_LDPC ; 
 int WMI_HT_CAP_L_SIG_TXOP_PROT ; 
 int WMI_HT_CAP_RX_LDPC ; 
 int WMI_HT_CAP_RX_STBC ; 
 int WMI_HT_CAP_RX_STBC_MASK_SHIFT ; 
 int WMI_HT_CAP_TX_LDPC ; 
 int WMI_HT_CAP_TX_STBC ; 
 int WMI_VHT_CAP_MAX_MPDU_LEN_MASK ; 

__attribute__((used)) static struct ieee80211_sta_ht_cap ath10k_get_ht_cap(struct ath10k *ar)
{
	int i;
	struct ieee80211_sta_ht_cap ht_cap = {0};

	if (!(ar->ht_cap_info & WMI_HT_CAP_ENABLED))
		return ht_cap;

	ht_cap.ht_supported = 1;
	ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
	ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_8;
	ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
	ht_cap.cap |= IEEE80211_HT_CAP_DSSSCCK40;
	ht_cap.cap |=
		WLAN_HT_CAP_SM_PS_DISABLED << IEEE80211_HT_CAP_SM_PS_SHIFT;

	if (ar->ht_cap_info & WMI_HT_CAP_HT20_SGI)
		ht_cap.cap |= IEEE80211_HT_CAP_SGI_20;

	if (ar->ht_cap_info & WMI_HT_CAP_HT40_SGI)
		ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;

	if (ar->ht_cap_info & WMI_HT_CAP_DYNAMIC_SMPS) {
		u32 smps;

		smps   = WLAN_HT_CAP_SM_PS_DYNAMIC;
		smps <<= IEEE80211_HT_CAP_SM_PS_SHIFT;

		ht_cap.cap |= smps;
	}

	if (ar->ht_cap_info & WMI_HT_CAP_TX_STBC && (ar->cfg_tx_chainmask > 1))
		ht_cap.cap |= IEEE80211_HT_CAP_TX_STBC;

	if (ar->ht_cap_info & WMI_HT_CAP_RX_STBC) {
		u32 stbc;

		stbc   = ar->ht_cap_info;
		stbc  &= WMI_HT_CAP_RX_STBC;
		stbc >>= WMI_HT_CAP_RX_STBC_MASK_SHIFT;
		stbc <<= IEEE80211_HT_CAP_RX_STBC_SHIFT;
		stbc  &= IEEE80211_HT_CAP_RX_STBC;

		ht_cap.cap |= stbc;
	}

	if (ar->ht_cap_info & WMI_HT_CAP_LDPC || (ar->ht_cap_info &
	    WMI_HT_CAP_RX_LDPC && (ar->ht_cap_info & WMI_HT_CAP_TX_LDPC)))
		ht_cap.cap |= IEEE80211_HT_CAP_LDPC_CODING;

	if (ar->ht_cap_info & WMI_HT_CAP_L_SIG_TXOP_PROT)
		ht_cap.cap |= IEEE80211_HT_CAP_LSIG_TXOP_PROT;

	/* max AMSDU is implicitly taken from vht_cap_info */
	if (ar->vht_cap_info & WMI_VHT_CAP_MAX_MPDU_LEN_MASK)
		ht_cap.cap |= IEEE80211_HT_CAP_MAX_AMSDU;

	for (i = 0; i < ar->num_rf_chains; i++) {
		if (ar->cfg_rx_chainmask & BIT(i))
			ht_cap.mcs.rx_mask[i] = 0xFF;
	}

	ht_cap.mcs.tx_params |= IEEE80211_HT_MCS_TX_DEFINED;

	return ht_cap;
}