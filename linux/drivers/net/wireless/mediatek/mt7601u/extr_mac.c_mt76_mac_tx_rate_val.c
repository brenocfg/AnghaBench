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
typedef  int u16 ;
struct TYPE_7__ {TYPE_1__* chan; } ;
struct mt7601u_dev {TYPE_5__* hw; TYPE_2__ chandef; } ;
struct ieee80211_tx_rate {int flags; int idx; } ;
struct ieee80211_rate {int hw_value_short; int hw_value; } ;
struct TYPE_10__ {TYPE_4__* wiphy; } ;
struct TYPE_9__ {TYPE_3__** bands; } ;
struct TYPE_8__ {struct ieee80211_rate* bitrates; } ;
struct TYPE_6__ {int band; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_GREEN_FIELD ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int IEEE80211_TX_RC_USE_SHORT_PREAMBLE ; 
 int MT_PHY_TYPE_HT ; 
 int MT_PHY_TYPE_HT_GF ; 
 int /*<<< orphan*/  MT_RXWI_RATE_BW ; 
 int /*<<< orphan*/  MT_RXWI_RATE_MCS ; 
 int /*<<< orphan*/  MT_RXWI_RATE_PHY ; 
 int MT_RXWI_RATE_SGI ; 

u16 mt76_mac_tx_rate_val(struct mt7601u_dev *dev,
			 const struct ieee80211_tx_rate *rate, u8 *nss_val)
{
	u16 rateval;
	u8 phy, rate_idx;
	u8 nss = 1;
	u8 bw = 0;

	if (rate->flags & IEEE80211_TX_RC_MCS) {
		rate_idx = rate->idx;
		nss = 1 + (rate->idx >> 3);
		phy = MT_PHY_TYPE_HT;
		if (rate->flags & IEEE80211_TX_RC_GREEN_FIELD)
			phy = MT_PHY_TYPE_HT_GF;
		if (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			bw = 1;
	} else {
		const struct ieee80211_rate *r;
		int band = dev->chandef.chan->band;
		u16 val;

		r = &dev->hw->wiphy->bands[band]->bitrates[rate->idx];
		if (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
			val = r->hw_value_short;
		else
			val = r->hw_value;

		phy = val >> 8;
		rate_idx = val & 0xff;
		bw = 0;
	}

	rateval = FIELD_PREP(MT_RXWI_RATE_MCS, rate_idx);
	rateval |= FIELD_PREP(MT_RXWI_RATE_PHY, phy);
	rateval |= FIELD_PREP(MT_RXWI_RATE_BW, bw);
	if (rate->flags & IEEE80211_TX_RC_SHORT_GI)
		rateval |= MT_RXWI_RATE_SGI;

	*nss_val = nss;
	return rateval;
}