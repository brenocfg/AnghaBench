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
struct ieee80211_rx_status {int rate_idx; int enc_flags; int /*<<< orphan*/  bw; int /*<<< orphan*/  encoding; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
#define  MT_PHY_TYPE_CCK 131 
#define  MT_PHY_TYPE_HT 130 
#define  MT_PHY_TYPE_HT_GF 129 
#define  MT_PHY_TYPE_OFDM 128 
 int MT_RXWI_RATE_BW ; 
 int /*<<< orphan*/  MT_RXWI_RATE_MCS ; 
 int /*<<< orphan*/  MT_RXWI_RATE_PHY ; 
 int MT_RXWI_RATE_SGI ; 
 int MT_RXWI_RATE_STBC ; 
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 int RX_ENC_FLAG_HT_GF ; 
 int RX_ENC_FLAG_SHORTPRE ; 
 int RX_ENC_FLAG_SHORT_GI ; 
 int RX_ENC_FLAG_STBC_SHIFT ; 
 int /*<<< orphan*/  RX_ENC_HT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void
mt76_mac_process_rate(struct ieee80211_rx_status *status, u16 rate)
{
	u8 idx = FIELD_GET(MT_RXWI_RATE_MCS, rate);

	switch (FIELD_GET(MT_RXWI_RATE_PHY, rate)) {
	case MT_PHY_TYPE_OFDM:
		if (WARN_ON(idx >= 8))
			idx = 0;
		idx += 4;

		status->rate_idx = idx;
		return;
	case MT_PHY_TYPE_CCK:
		if (idx >= 8) {
			idx -= 8;
			status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
		}

		if (WARN_ON(idx >= 4))
			idx = 0;

		status->rate_idx = idx;
		return;
	case MT_PHY_TYPE_HT_GF:
		status->enc_flags |= RX_ENC_FLAG_HT_GF;
		/* fall through */
	case MT_PHY_TYPE_HT:
		status->encoding = RX_ENC_HT;
		status->rate_idx = idx;
		break;
	default:
		WARN_ON(1);
		return;
	}

	if (rate & MT_RXWI_RATE_SGI)
		status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	if (rate & MT_RXWI_RATE_STBC)
		status->enc_flags |= 1 << RX_ENC_FLAG_STBC_SHIFT;

	if (rate & MT_RXWI_RATE_BW)
		status->bw = RATE_INFO_BW_40;
}