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
typedef  int u32 ;
struct il_rx_phy_res {int /*<<< orphan*/  phy_flags; scalar_t__ non_cfg_phy_buf; } ;
struct il_priv {int dummy; } ;
struct il4965_rx_non_cfg_phy {int /*<<< orphan*/ * rssi_info; int /*<<< orphan*/  agc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STATS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int IL4965_RSSI_OFFSET ; 
 int IL49_AGC_DB_MASK ; 
 int IL49_AGC_DB_POS ; 
 int IL49_RX_PHY_FLAGS_ANTENNAE_MASK ; 
 int IL49_RX_PHY_FLAGS_ANTENNAE_OFFSET ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
il4965_calc_rssi(struct il_priv *il, struct il_rx_phy_res *rx_resp)
{
	/* data from PHY/DSP regarding signal strength, etc.,
	 *   contents are always there, not configurable by host.  */
	struct il4965_rx_non_cfg_phy *ncphy =
	    (struct il4965_rx_non_cfg_phy *)rx_resp->non_cfg_phy_buf;
	u32 agc =
	    (le16_to_cpu(ncphy->agc_info) & IL49_AGC_DB_MASK) >>
	    IL49_AGC_DB_POS;

	u32 valid_antennae =
	    (le16_to_cpu(rx_resp->phy_flags) & IL49_RX_PHY_FLAGS_ANTENNAE_MASK)
	    >> IL49_RX_PHY_FLAGS_ANTENNAE_OFFSET;
	u8 max_rssi = 0;
	u32 i;

	/* Find max rssi among 3 possible receivers.
	 * These values are measured by the digital signal processor (DSP).
	 * They should stay fairly constant even as the signal strength varies,
	 *   if the radio's automatic gain control (AGC) is working right.
	 * AGC value (see below) will provide the "interesting" info. */
	for (i = 0; i < 3; i++)
		if (valid_antennae & (1 << i))
			max_rssi = max(ncphy->rssi_info[i << 1], max_rssi);

	D_STATS("Rssi In A %d B %d C %d Max %d AGC dB %d\n",
		ncphy->rssi_info[0], ncphy->rssi_info[2], ncphy->rssi_info[4],
		max_rssi, agc);

	/* dBm = max_rssi dB - agc dB - constant.
	 * Higher AGC (higher radio gain) means lower signal. */
	return max_rssi - agc - IL4965_RSSI_OFFSET;
}