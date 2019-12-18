#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_supported_band {unsigned int n_bitrates; TYPE_3__* bitrates; } ;
struct ieee80211_rx_status {int rate_idx; int /*<<< orphan*/  enc_flags; int /*<<< orphan*/  bw; int /*<<< orphan*/  encoding; } ;
struct ieee80211_hw {TYPE_2__* wiphy; } ;
struct ath_rx_status {int rs_rate; int /*<<< orphan*/  bw; int /*<<< orphan*/  enc_flags; } ;
struct ath_hw {TYPE_4__* curchan; } ;
struct ath_common {struct ath_hw* ah; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_9__ {TYPE_1__* chan; } ;
struct TYPE_8__ {int hw_value; int hw_value_short; } ;
struct TYPE_7__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_6__ {int band; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_CHAN_HALF_RATE (TYPE_4__*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (TYPE_4__*) ; 
 int /*<<< orphan*/  RATE_INFO_BW_10 ; 
 int /*<<< orphan*/  RATE_INFO_BW_5 ; 
 int /*<<< orphan*/  RX_ENC_FLAG_SHORTPRE ; 
 int /*<<< orphan*/  RX_ENC_HT ; 

int ath9k_cmn_process_rate(struct ath_common *common,
			   struct ieee80211_hw *hw,
			   struct ath_rx_status *rx_stats,
			   struct ieee80211_rx_status *rxs)
{
	struct ieee80211_supported_band *sband;
	enum nl80211_band band;
	unsigned int i = 0;
	struct ath_hw *ah = common->ah;

	band = ah->curchan->chan->band;
	sband = hw->wiphy->bands[band];

	if (IS_CHAN_QUARTER_RATE(ah->curchan))
		rxs->bw = RATE_INFO_BW_5;
	else if (IS_CHAN_HALF_RATE(ah->curchan))
		rxs->bw = RATE_INFO_BW_10;

	if (rx_stats->rs_rate & 0x80) {
		/* HT rate */
		rxs->encoding = RX_ENC_HT;
		rxs->enc_flags |= rx_stats->enc_flags;
		rxs->bw = rx_stats->bw;
		rxs->rate_idx = rx_stats->rs_rate & 0x7f;
		return 0;
	}

	for (i = 0; i < sband->n_bitrates; i++) {
		if (sband->bitrates[i].hw_value == rx_stats->rs_rate) {
			rxs->rate_idx = i;
			return 0;
		}
		if (sband->bitrates[i].hw_value_short == rx_stats->rs_rate) {
			rxs->enc_flags |= RX_ENC_FLAG_SHORTPRE;
			rxs->rate_idx = i;
			return 0;
		}
	}

	return -EINVAL;
}