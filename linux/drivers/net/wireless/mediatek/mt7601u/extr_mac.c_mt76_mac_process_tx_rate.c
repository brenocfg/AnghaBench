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

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_GREEN_FIELD ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_MCS ; 
 int /*<<< orphan*/  IEEE80211_TX_RC_SHORT_GI ; 
 int MT_PHY_BW_40 ; 
#define  MT_PHY_TYPE_CCK 131 
#define  MT_PHY_TYPE_HT 130 
#define  MT_PHY_TYPE_HT_GF 129 
#define  MT_PHY_TYPE_OFDM 128 
 int /*<<< orphan*/  MT_TXWI_RATE_BW ; 
 int /*<<< orphan*/  MT_TXWI_RATE_MCS ; 
 int /*<<< orphan*/  MT_TXWI_RATE_PHY_MODE ; 
 int MT_TXWI_RATE_SGI ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void
mt76_mac_process_tx_rate(struct ieee80211_tx_rate *txrate, u16 rate)
{
	u8 idx = FIELD_GET(MT_TXWI_RATE_MCS, rate);

	txrate->idx = 0;
	txrate->flags = 0;
	txrate->count = 1;

	switch (FIELD_GET(MT_TXWI_RATE_PHY_MODE, rate)) {
	case MT_PHY_TYPE_OFDM:
		txrate->idx = idx + 4;
		return;
	case MT_PHY_TYPE_CCK:
		if (idx >= 8)
			idx -= 8;

		txrate->idx = idx;
		return;
	case MT_PHY_TYPE_HT_GF:
		txrate->flags |= IEEE80211_TX_RC_GREEN_FIELD;
		/* fall through */
	case MT_PHY_TYPE_HT:
		txrate->flags |= IEEE80211_TX_RC_MCS;
		txrate->idx = idx;
		break;
	default:
		WARN_ON(1);
		return;
	}

	if (FIELD_GET(MT_TXWI_RATE_BW, rate) == MT_PHY_BW_40)
		txrate->flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;

	if (rate & MT_TXWI_RATE_SGI)
		txrate->flags |= IEEE80211_TX_RC_SHORT_GI;
}