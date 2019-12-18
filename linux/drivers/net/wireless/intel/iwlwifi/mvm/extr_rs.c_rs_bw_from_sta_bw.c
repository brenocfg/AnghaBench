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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_vht_cap {int /*<<< orphan*/  supp_mcs; int /*<<< orphan*/  vht_cap_info; } ;
struct ieee80211_sta_vht_cap {int /*<<< orphan*/  vht_mcs; int /*<<< orphan*/  cap; } ;
struct ieee80211_sta {int bandwidth; int /*<<< orphan*/  rx_nss; struct ieee80211_sta_vht_cap vht_cap; } ;

/* Variables and functions */
#define  IEEE80211_STA_RX_BW_160 131 
#define  IEEE80211_STA_RX_BW_20 130 
#define  IEEE80211_STA_RX_BW_40 129 
#define  IEEE80211_STA_RX_BW_80 128 
 int /*<<< orphan*/  IEEE80211_VHT_CHANWIDTH_160MHZ ; 
 int /*<<< orphan*/  RATE_MCS_CHAN_WIDTH_160 ; 
 int /*<<< orphan*/  RATE_MCS_CHAN_WIDTH_20 ; 
 int /*<<< orphan*/  RATE_MCS_CHAN_WIDTH_40 ; 
 int /*<<< orphan*/  RATE_MCS_CHAN_WIDTH_80 ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_vht_max_nss (struct ieee80211_vht_cap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 rs_bw_from_sta_bw(struct ieee80211_sta *sta)
{
	struct ieee80211_sta_vht_cap *sta_vht_cap = &sta->vht_cap;
	struct ieee80211_vht_cap vht_cap = {
		.vht_cap_info = cpu_to_le32(sta_vht_cap->cap),
		.supp_mcs = sta_vht_cap->vht_mcs,
	};

	switch (sta->bandwidth) {
	case IEEE80211_STA_RX_BW_160:
		/*
		 * Don't use 160 MHz if VHT extended NSS support
		 * says we cannot use 2 streams, we don't want to
		 * deal with this.
		 * We only check MCS 0 - they will support that if
		 * we got here at all and we don't care which MCS,
		 * we want to determine a more global state.
		 */
		if (ieee80211_get_vht_max_nss(&vht_cap,
					      IEEE80211_VHT_CHANWIDTH_160MHZ,
					      0, true) < sta->rx_nss)
			return RATE_MCS_CHAN_WIDTH_80;
		return RATE_MCS_CHAN_WIDTH_160;
	case IEEE80211_STA_RX_BW_80:
		return RATE_MCS_CHAN_WIDTH_80;
	case IEEE80211_STA_RX_BW_40:
		return RATE_MCS_CHAN_WIDTH_40;
	case IEEE80211_STA_RX_BW_20:
	default:
		return RATE_MCS_CHAN_WIDTH_20;
	}
}