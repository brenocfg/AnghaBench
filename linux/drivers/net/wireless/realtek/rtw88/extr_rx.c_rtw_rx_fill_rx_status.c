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
typedef  size_t u8 ;
struct rtw_rx_pkt_stat {scalar_t__ rate; scalar_t__ bw; int /*<<< orphan*/ * rx_power; int /*<<< orphan*/  signal_power; int /*<<< orphan*/  tsf_low; scalar_t__ decrypted; scalar_t__ crc_err; } ;
struct TYPE_8__ {size_t rf_path_num; } ;
struct rtw_dev {TYPE_4__ hal; struct ieee80211_hw* hw; } ;
struct ieee80211_rx_status {int nss; int /*<<< orphan*/ * chain_signal; int /*<<< orphan*/  chains; int /*<<< orphan*/  signal; int /*<<< orphan*/  bw; int /*<<< orphan*/  mactime; int /*<<< orphan*/  flag; scalar_t__ rate_idx; int /*<<< orphan*/  band; int /*<<< orphan*/  encoding; int /*<<< orphan*/  freq; } ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct TYPE_7__ {TYPE_2__ chandef; } ;
struct ieee80211_hw {TYPE_3__ conf; } ;
struct ieee80211_hdr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  band; int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 scalar_t__ DESC_RATE1M ; 
 scalar_t__ DESC_RATE54M ; 
 scalar_t__ DESC_RATE6M ; 
 scalar_t__ DESC_RATEMCS0 ; 
 scalar_t__ DESC_RATEMCS15 ; 
 scalar_t__ DESC_RATEVHT1SS_MCS0 ; 
 scalar_t__ DESC_RATEVHT1SS_MCS9 ; 
 scalar_t__ DESC_RATEVHT2SS_MCS0 ; 
 scalar_t__ DESC_RATEVHT2SS_MCS9 ; 
 scalar_t__ DESC_RATEVHT3SS_MCS0 ; 
 scalar_t__ DESC_RATEVHT3SS_MCS9 ; 
 scalar_t__ DESC_RATEVHT4SS_MCS0 ; 
 scalar_t__ DESC_RATEVHT4SS_MCS9 ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  RATE_INFO_BW_20 ; 
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 int /*<<< orphan*/  RATE_INFO_BW_80 ; 
 scalar_t__ RTW_CHANNEL_WIDTH_40 ; 
 scalar_t__ RTW_CHANNEL_WIDTH_80 ; 
 int /*<<< orphan*/  RX_ENC_HT ; 
 int /*<<< orphan*/  RX_ENC_VHT ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_FCS_CRC ; 
 int /*<<< orphan*/  RX_FLAG_MACTIME_START ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_status*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_rx_addr_match (struct rtw_dev*,struct rtw_rx_pkt_stat*,struct ieee80211_hdr*) ; 

void rtw_rx_fill_rx_status(struct rtw_dev *rtwdev,
			   struct rtw_rx_pkt_stat *pkt_stat,
			   struct ieee80211_hdr *hdr,
			   struct ieee80211_rx_status *rx_status,
			   u8 *phy_status)
{
	struct ieee80211_hw *hw = rtwdev->hw;
	u8 path;

	memset(rx_status, 0, sizeof(*rx_status));
	rx_status->freq = hw->conf.chandef.chan->center_freq;
	rx_status->band = hw->conf.chandef.chan->band;
	if (pkt_stat->crc_err)
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	if (pkt_stat->decrypted)
		rx_status->flag |= RX_FLAG_DECRYPTED;

	if (pkt_stat->rate >= DESC_RATEVHT1SS_MCS0)
		rx_status->encoding = RX_ENC_VHT;
	else if (pkt_stat->rate >= DESC_RATEMCS0)
		rx_status->encoding = RX_ENC_HT;

	if (pkt_stat->rate >= DESC_RATEVHT1SS_MCS0 &&
	    pkt_stat->rate <= DESC_RATEVHT1SS_MCS9) {
		rx_status->nss = 1;
		rx_status->rate_idx = pkt_stat->rate - DESC_RATEVHT1SS_MCS0;
	} else if (pkt_stat->rate >= DESC_RATEVHT2SS_MCS0 &&
		   pkt_stat->rate <= DESC_RATEVHT2SS_MCS9) {
		rx_status->nss = 2;
		rx_status->rate_idx = pkt_stat->rate - DESC_RATEVHT2SS_MCS0;
	} else if (pkt_stat->rate >= DESC_RATEVHT3SS_MCS0 &&
		   pkt_stat->rate <= DESC_RATEVHT3SS_MCS9) {
		rx_status->nss = 3;
		rx_status->rate_idx = pkt_stat->rate - DESC_RATEVHT3SS_MCS0;
	} else if (pkt_stat->rate >= DESC_RATEVHT4SS_MCS0 &&
		   pkt_stat->rate <= DESC_RATEVHT4SS_MCS9) {
		rx_status->nss = 4;
		rx_status->rate_idx = pkt_stat->rate - DESC_RATEVHT4SS_MCS0;
	} else if (pkt_stat->rate >= DESC_RATEMCS0 &&
		   pkt_stat->rate <= DESC_RATEMCS15) {
		rx_status->rate_idx = pkt_stat->rate - DESC_RATEMCS0;
	} else if (rx_status->band == NL80211_BAND_5GHZ &&
		   pkt_stat->rate >= DESC_RATE6M &&
		   pkt_stat->rate <= DESC_RATE54M) {
		rx_status->rate_idx = pkt_stat->rate - DESC_RATE6M;
	} else if (rx_status->band == NL80211_BAND_2GHZ &&
		   pkt_stat->rate >= DESC_RATE1M &&
		   pkt_stat->rate <= DESC_RATE54M) {
		rx_status->rate_idx = pkt_stat->rate - DESC_RATE1M;
	} else {
		rx_status->rate_idx = 0;
	}

	rx_status->flag |= RX_FLAG_MACTIME_START;
	rx_status->mactime = pkt_stat->tsf_low;

	if (pkt_stat->bw == RTW_CHANNEL_WIDTH_80)
		rx_status->bw = RATE_INFO_BW_80;
	else if (pkt_stat->bw == RTW_CHANNEL_WIDTH_40)
		rx_status->bw = RATE_INFO_BW_40;
	else
		rx_status->bw = RATE_INFO_BW_20;

	rx_status->signal = pkt_stat->signal_power;
	for (path = 0; path < rtwdev->hal.rf_path_num; path++) {
		rx_status->chains |= BIT(path);
		rx_status->chain_signal[path] = pkt_stat->rx_power[path];
	}

	rtw_rx_addr_match(rtwdev, pkt_stat, hdr);
}