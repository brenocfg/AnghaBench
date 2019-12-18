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
typedef  int u8 ;
typedef  int u16 ;
struct ieee80211_tx_rate {int idx; int count; int /*<<< orphan*/  flags; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int EINVAL ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_80_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_GREEN_FIELD ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_SHORT_GI ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_VHT_MCS ; 
#define  MT_PHY_BW_20 135 
#define  MT_PHY_BW_40 134 
#define  MT_PHY_BW_80 133 
#define  MT_PHY_TYPE_CCK 132 
#define  MT_PHY_TYPE_HT 131 
#define  MT_PHY_TYPE_HT_GF 130 
#define  MT_PHY_TYPE_OFDM 129 
#define  MT_PHY_TYPE_VHT 128 
 int /*<<< orphan*/  MT_RXWI_RATE_BW ; 
 int /*<<< orphan*/  MT_RXWI_RATE_INDEX ; 
 int /*<<< orphan*/  MT_RXWI_RATE_PHY ; 
 int MT_RXWI_RATE_SGI ; 
 int NL80211_BAND_2GHZ ; 

__attribute__((used)) static int
mt76x02_mac_process_tx_rate(struct ieee80211_tx_rate *txrate, u16 rate,
			    enum nl80211_band band)
{
	u8 idx = FIELD_GET(MT_RXWI_RATE_INDEX, rate);

	txrate->idx = 0;
	txrate->flags = 0;
	txrate->count = 1;

	switch (FIELD_GET(MT_RXWI_RATE_PHY, rate)) {
	case MT_PHY_TYPE_OFDM:
		if (band == NL80211_BAND_2GHZ)
			idx += 4;

		txrate->idx = idx;
		return 0;
	case MT_PHY_TYPE_CCK:
		if (idx >= 8)
			idx -= 8;

		txrate->idx = idx;
		return 0;
	case MT_PHY_TYPE_HT_GF:
		txrate->flags |= IEEE80211_TX_RC_GREEN_FIELD;
		/* fall through */
	case MT_PHY_TYPE_HT:
		txrate->flags |= IEEE80211_TX_RC_MCS;
		txrate->idx = idx;
		break;
	case MT_PHY_TYPE_VHT:
		txrate->flags |= IEEE80211_TX_RC_VHT_MCS;
		txrate->idx = idx;
		break;
	default:
		return -EINVAL;
	}

	switch (FIELD_GET(MT_RXWI_RATE_BW, rate)) {
	case MT_PHY_BW_20:
		break;
	case MT_PHY_BW_40:
		txrate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		break;
	case MT_PHY_BW_80:
		txrate->flags |= IEEE80211_TX_RC_80_MHZ_WIDTH;
		break;
	default:
		return -EINVAL;
	}

	if (rate & MT_RXWI_RATE_SGI)
		txrate->flags |= IEEE80211_TX_RC_SHORT_GI;

	return 0;
}