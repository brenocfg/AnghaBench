#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ieee80211_rx_status {int rate_idx; int /*<<< orphan*/  encoding; int /*<<< orphan*/  enc_flags; int /*<<< orphan*/  bw; int /*<<< orphan*/  band; int /*<<< orphan*/  freq; int /*<<< orphan*/  flag; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; int /*<<< orphan*/  band; } ;
struct ar9170_rx_macstatus {int error; int status; } ;
struct ar9170_rx_head {int* plcp; } ;
struct ar9170 {int filter_state; TYPE_1__* hw; struct ieee80211_channel* channel; int /*<<< orphan*/  sniffer_enabled; int /*<<< orphan*/  tx_fcs_errors; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int AR9170_ENC_ALG_NONE ; 
 int AR9170_ENC_ALG_TKIP ; 
 int AR9170_RX_ENC_SOFTWARE ; 
 int AR9170_RX_ERROR_DECRYPT ; 
 int AR9170_RX_ERROR_FCS ; 
 int AR9170_RX_ERROR_MMIC ; 
 int AR9170_RX_ERROR_PLCP ; 
 int AR9170_RX_ERROR_WRONG_RA ; 
#define  AR9170_RX_PHY_RATE_CCK_11M 143 
#define  AR9170_RX_PHY_RATE_CCK_1M 142 
#define  AR9170_RX_PHY_RATE_CCK_2M 141 
#define  AR9170_RX_PHY_RATE_CCK_5M 140 
 int AR9170_RX_STATUS_MODULATION ; 
#define  AR9170_RX_STATUS_MODULATION_CCK 139 
#define  AR9170_RX_STATUS_MODULATION_DUPOFDM 138 
#define  AR9170_RX_STATUS_MODULATION_HT 137 
#define  AR9170_RX_STATUS_MODULATION_OFDM 136 
 int AR9170_RX_STATUS_SHORT_PREAMBLE ; 
#define  AR9170_TXRX_PHY_RATE_OFDM_12M 135 
#define  AR9170_TXRX_PHY_RATE_OFDM_18M 134 
#define  AR9170_TXRX_PHY_RATE_OFDM_24M 133 
#define  AR9170_TXRX_PHY_RATE_OFDM_36M 132 
#define  AR9170_TXRX_PHY_RATE_OFDM_48M 131 
#define  AR9170_TXRX_PHY_RATE_OFDM_54M 130 
#define  AR9170_TXRX_PHY_RATE_OFDM_6M 129 
#define  AR9170_TXRX_PHY_RATE_OFDM_9M 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENODATA ; 
 int ENOSYS ; 
 int FIF_FCSFAIL ; 
 int FIF_PLCPFAIL ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 int /*<<< orphan*/  RX_ENC_FLAG_SHORTPRE ; 
 int /*<<< orphan*/  RX_ENC_FLAG_SHORT_GI ; 
 int /*<<< orphan*/  RX_ENC_HT ; 
 int /*<<< orphan*/  RX_FLAG_DECRYPTED ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_FCS_CRC ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_PLCP_CRC ; 
 int /*<<< orphan*/  RX_FLAG_MMIC_ERROR ; 
 int ar9170_get_decrypt_type (struct ar9170_rx_macstatus*) ; 
 int clamp (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ net_ratelimit () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wiphy_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int carl9170_rx_mac_status(struct ar9170 *ar,
	struct ar9170_rx_head *head, struct ar9170_rx_macstatus *mac,
	struct ieee80211_rx_status *status)
{
	struct ieee80211_channel *chan;
	u8 error, decrypt;

	BUILD_BUG_ON(sizeof(struct ar9170_rx_head) != 12);
	BUILD_BUG_ON(sizeof(struct ar9170_rx_macstatus) != 4);

	error = mac->error;

	if (error & AR9170_RX_ERROR_WRONG_RA) {
		if (!ar->sniffer_enabled)
			return -EINVAL;
	}

	if (error & AR9170_RX_ERROR_PLCP) {
		if (!(ar->filter_state & FIF_PLCPFAIL))
			return -EINVAL;

		status->flag |= RX_FLAG_FAILED_PLCP_CRC;
	}

	if (error & AR9170_RX_ERROR_FCS) {
		ar->tx_fcs_errors++;

		if (!(ar->filter_state & FIF_FCSFAIL))
			return -EINVAL;

		status->flag |= RX_FLAG_FAILED_FCS_CRC;
	}

	decrypt = ar9170_get_decrypt_type(mac);
	if (!(decrypt & AR9170_RX_ENC_SOFTWARE) &&
	    decrypt != AR9170_ENC_ALG_NONE) {
		if ((decrypt == AR9170_ENC_ALG_TKIP) &&
		    (error & AR9170_RX_ERROR_MMIC))
			status->flag |= RX_FLAG_MMIC_ERROR;

		status->flag |= RX_FLAG_DECRYPTED;
	}

	if (error & AR9170_RX_ERROR_DECRYPT && !ar->sniffer_enabled)
		return -ENODATA;

	error &= ~(AR9170_RX_ERROR_MMIC |
		   AR9170_RX_ERROR_FCS |
		   AR9170_RX_ERROR_WRONG_RA |
		   AR9170_RX_ERROR_DECRYPT |
		   AR9170_RX_ERROR_PLCP);

	/* drop any other error frames */
	if (unlikely(error)) {
		/* TODO: update netdevice's RX dropped/errors statistics */

		if (net_ratelimit())
			wiphy_dbg(ar->hw->wiphy, "received frame with "
			       "suspicious error code (%#x).\n", error);

		return -EINVAL;
	}

	chan = ar->channel;
	if (chan) {
		status->band = chan->band;
		status->freq = chan->center_freq;
	}

	switch (mac->status & AR9170_RX_STATUS_MODULATION) {
	case AR9170_RX_STATUS_MODULATION_CCK:
		if (mac->status & AR9170_RX_STATUS_SHORT_PREAMBLE)
			status->enc_flags |= RX_ENC_FLAG_SHORTPRE;
		switch (head->plcp[0]) {
		case AR9170_RX_PHY_RATE_CCK_1M:
			status->rate_idx = 0;
			break;
		case AR9170_RX_PHY_RATE_CCK_2M:
			status->rate_idx = 1;
			break;
		case AR9170_RX_PHY_RATE_CCK_5M:
			status->rate_idx = 2;
			break;
		case AR9170_RX_PHY_RATE_CCK_11M:
			status->rate_idx = 3;
			break;
		default:
			if (net_ratelimit()) {
				wiphy_err(ar->hw->wiphy, "invalid plcp cck "
				       "rate (%x).\n", head->plcp[0]);
			}

			return -EINVAL;
		}
		break;

	case AR9170_RX_STATUS_MODULATION_DUPOFDM:
	case AR9170_RX_STATUS_MODULATION_OFDM:
		switch (head->plcp[0] & 0xf) {
		case AR9170_TXRX_PHY_RATE_OFDM_6M:
			status->rate_idx = 0;
			break;
		case AR9170_TXRX_PHY_RATE_OFDM_9M:
			status->rate_idx = 1;
			break;
		case AR9170_TXRX_PHY_RATE_OFDM_12M:
			status->rate_idx = 2;
			break;
		case AR9170_TXRX_PHY_RATE_OFDM_18M:
			status->rate_idx = 3;
			break;
		case AR9170_TXRX_PHY_RATE_OFDM_24M:
			status->rate_idx = 4;
			break;
		case AR9170_TXRX_PHY_RATE_OFDM_36M:
			status->rate_idx = 5;
			break;
		case AR9170_TXRX_PHY_RATE_OFDM_48M:
			status->rate_idx = 6;
			break;
		case AR9170_TXRX_PHY_RATE_OFDM_54M:
			status->rate_idx = 7;
			break;
		default:
			if (net_ratelimit()) {
				wiphy_err(ar->hw->wiphy, "invalid plcp ofdm "
					"rate (%x).\n", head->plcp[0]);
			}

			return -EINVAL;
		}
		if (status->band == NL80211_BAND_2GHZ)
			status->rate_idx += 4;
		break;

	case AR9170_RX_STATUS_MODULATION_HT:
		if (head->plcp[3] & 0x80)
			status->bw = RATE_INFO_BW_40;
		if (head->plcp[6] & 0x80)
			status->enc_flags |= RX_ENC_FLAG_SHORT_GI;

		status->rate_idx = clamp(head->plcp[3] & 0x7f, 0, 75);
		status->encoding = RX_ENC_HT;
		break;

	default:
		BUG();
		return -ENOSYS;
	}

	return 0;
}