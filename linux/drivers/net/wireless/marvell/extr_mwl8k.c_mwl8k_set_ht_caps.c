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
typedef  int u32 ;
struct TYPE_3__ {int* rx_mask; int tx_params; } ;
struct TYPE_4__ {int ht_supported; TYPE_1__ mcs; int /*<<< orphan*/  cap; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; } ;
struct ieee80211_supported_band {TYPE_2__ ht_cap; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_AGGREGATION ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_DELAY_BA ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_GRN_FLD ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_MAX_AMSDU ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_RX_STBC ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_20 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_TX_STBC ; 
 int /*<<< orphan*/  IEEE80211_HT_MAX_AMPDU_64K ; 
 int IEEE80211_HT_MCS_TX_DEFINED ; 
 int IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT ; 
 int IEEE80211_HT_MCS_TX_RX_DIFF ; 
 int /*<<< orphan*/  IEEE80211_HT_MPDU_DENSITY_NONE ; 
 int MWL8K_CAP_40MHZ ; 
 int MWL8K_CAP_AMPDU ; 
 int MWL8K_CAP_DELAY_BA ; 
 int MWL8K_CAP_GREENFIELD ; 
 int MWL8K_CAP_MAX_AMSDU ; 
 int MWL8K_CAP_RX_ANTENNA_MASK ; 
 int MWL8K_CAP_RX_STBC ; 
 int MWL8K_CAP_SHORTGI_20MHZ ; 
 int MWL8K_CAP_SHORTGI_40MHZ ; 
 int MWL8K_CAP_TX_ANTENNA_MASK ; 
 int MWL8K_CAP_TX_STBC ; 
 int hweight32 (int) ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mwl8k_set_ht_caps(struct ieee80211_hw *hw,
		  struct ieee80211_supported_band *band, u32 cap)
{
	int rx_streams;
	int tx_streams;

	band->ht_cap.ht_supported = 1;

	if (cap & MWL8K_CAP_MAX_AMSDU)
		band->ht_cap.cap |= IEEE80211_HT_CAP_MAX_AMSDU;
	if (cap & MWL8K_CAP_GREENFIELD)
		band->ht_cap.cap |= IEEE80211_HT_CAP_GRN_FLD;
	if (cap & MWL8K_CAP_AMPDU) {
		ieee80211_hw_set(hw, AMPDU_AGGREGATION);
		band->ht_cap.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;
		band->ht_cap.ampdu_density = IEEE80211_HT_MPDU_DENSITY_NONE;
	}
	if (cap & MWL8K_CAP_RX_STBC)
		band->ht_cap.cap |= IEEE80211_HT_CAP_RX_STBC;
	if (cap & MWL8K_CAP_TX_STBC)
		band->ht_cap.cap |= IEEE80211_HT_CAP_TX_STBC;
	if (cap & MWL8K_CAP_SHORTGI_40MHZ)
		band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_40;
	if (cap & MWL8K_CAP_SHORTGI_20MHZ)
		band->ht_cap.cap |= IEEE80211_HT_CAP_SGI_20;
	if (cap & MWL8K_CAP_DELAY_BA)
		band->ht_cap.cap |= IEEE80211_HT_CAP_DELAY_BA;
	if (cap & MWL8K_CAP_40MHZ)
		band->ht_cap.cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;

	rx_streams = hweight32(cap & MWL8K_CAP_RX_ANTENNA_MASK);
	tx_streams = hweight32(cap & MWL8K_CAP_TX_ANTENNA_MASK);

	band->ht_cap.mcs.rx_mask[0] = 0xff;
	if (rx_streams >= 2)
		band->ht_cap.mcs.rx_mask[1] = 0xff;
	if (rx_streams >= 3)
		band->ht_cap.mcs.rx_mask[2] = 0xff;
	band->ht_cap.mcs.rx_mask[4] = 0x01;
	band->ht_cap.mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;

	if (rx_streams != tx_streams) {
		band->ht_cap.mcs.tx_params |= IEEE80211_HT_MCS_TX_RX_DIFF;
		band->ht_cap.mcs.tx_params |= (tx_streams - 1) <<
				IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT;
	}
}