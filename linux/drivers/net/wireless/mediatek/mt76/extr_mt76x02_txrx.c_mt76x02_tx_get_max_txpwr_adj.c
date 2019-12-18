#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wiphy {TYPE_4__** bands; } ;
struct mt76_rate_power {int /*<<< orphan*/ * ofdm; int /*<<< orphan*/ * cck; int /*<<< orphan*/ * ht; int /*<<< orphan*/ * vht; } ;
struct TYPE_7__ {TYPE_1__* chan; } ;
struct TYPE_10__ {struct mt76_rate_power rate_power; TYPE_3__* hw; TYPE_2__ chandef; } ;
struct mt76x02_dev {TYPE_5__ mt76; } ;
struct ieee80211_tx_rate {int flags; int idx; } ;
struct ieee80211_rate {int flags; int hw_value; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_9__ {struct ieee80211_rate* bitrates; } ;
struct TYPE_8__ {struct wiphy* wiphy; } ;
struct TYPE_6__ {int band; } ;

/* Variables and functions */
 int IEEE80211_RATE_SHORT_PREAMBLE ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int NL80211_BAND_2GHZ ; 
 int ieee80211_rate_get_vht_mcs (struct ieee80211_tx_rate const*) ; 
 int ieee80211_rate_get_vht_nss (struct ieee80211_tx_rate const*) ; 

s8 mt76x02_tx_get_max_txpwr_adj(struct mt76x02_dev *dev,
				const struct ieee80211_tx_rate *rate)
{
	s8 max_txpwr;

	if (rate->flags & IEEE80211_TX_RC_VHT_MCS) {
		u8 mcs = ieee80211_rate_get_vht_mcs(rate);

		if (mcs == 8 || mcs == 9) {
			max_txpwr = dev->mt76.rate_power.vht[8];
		} else {
			u8 nss, idx;

			nss = ieee80211_rate_get_vht_nss(rate);
			idx = ((nss - 1) << 3) + mcs;
			max_txpwr = dev->mt76.rate_power.ht[idx & 0xf];
		}
	} else if (rate->flags & IEEE80211_TX_RC_MCS) {
		max_txpwr = dev->mt76.rate_power.ht[rate->idx & 0xf];
	} else {
		enum nl80211_band band = dev->mt76.chandef.chan->band;

		if (band == NL80211_BAND_2GHZ) {
			const struct ieee80211_rate *r;
			struct wiphy *wiphy = dev->mt76.hw->wiphy;
			struct mt76_rate_power *rp = &dev->mt76.rate_power;

			r = &wiphy->bands[band]->bitrates[rate->idx];
			if (r->flags & IEEE80211_RATE_SHORT_PREAMBLE)
				max_txpwr = rp->cck[r->hw_value & 0x3];
			else
				max_txpwr = rp->ofdm[r->hw_value & 0x7];
		} else {
			max_txpwr = dev->mt76.rate_power.ofdm[rate->idx & 0x7];
		}
	}

	return max_txpwr;
}