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
typedef  int /*<<< orphan*/  u32 ;
struct skb_frame_desc {int tx_rate_idx; int tx_rate_flags; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int IEEE80211_TX_RC_40_MHZ_WIDTH ; 
 int IEEE80211_TX_RC_GREEN_FIELD ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int NL80211_BAND_2GHZ ; 
#define  RATE_MODE_CCK 131 
#define  RATE_MODE_HT_GREENFIELD 130 
#define  RATE_MODE_HT_MIX 129 
#define  RATE_MODE_OFDM 128 
 int /*<<< orphan*/  TX_STA_FIFO_BW ; 
 int /*<<< orphan*/  TX_STA_FIFO_MCS ; 
 int /*<<< orphan*/  TX_STA_FIFO_PHYMODE ; 
 int /*<<< orphan*/  TX_STA_FIFO_SGI ; 
 int rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_rate_from_status(struct skb_frame_desc *skbdesc,
				    u32 status, enum nl80211_band band)
{
	u8 flags = 0;
	u8 idx = rt2x00_get_field32(status, TX_STA_FIFO_MCS);

	switch (rt2x00_get_field32(status, TX_STA_FIFO_PHYMODE)) {
	case RATE_MODE_HT_GREENFIELD:
		flags |= IEEE80211_TX_RC_GREEN_FIELD;
		/* fall through */
	case RATE_MODE_HT_MIX:
		flags |= IEEE80211_TX_RC_MCS;
		break;
	case RATE_MODE_OFDM:
		if (band == NL80211_BAND_2GHZ)
			idx += 4;
		break;
	case RATE_MODE_CCK:
		if (idx >= 8)
			idx -= 8;
		break;
	}

	if (rt2x00_get_field32(status, TX_STA_FIFO_BW))
		flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;

	if (rt2x00_get_field32(status, TX_STA_FIFO_SGI))
		flags |= IEEE80211_TX_RC_SHORT_GI;

	skbdesc->tx_rate_idx = idx;
	skbdesc->tx_rate_flags = flags;
}