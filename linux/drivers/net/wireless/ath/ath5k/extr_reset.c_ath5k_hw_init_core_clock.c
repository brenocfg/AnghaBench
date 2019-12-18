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
typedef  int u32 ;
struct ieee80211_channel {int hw_value; } ;
struct ath_common {int clockrate; } ;
struct ath5k_hw {int ah_bwmode; scalar_t__ ah_version; scalar_t__ ah_radio; scalar_t__ ah_mac_srev; struct ieee80211_channel* ah_current_channel; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
#define  AR5K_BWMODE_10MHZ 133 
#define  AR5K_BWMODE_40MHZ 132 
#define  AR5K_BWMODE_5MHZ 131 
 int /*<<< orphan*/  AR5K_DCU_GBL_IFS_MISC ; 
 int /*<<< orphan*/  AR5K_DCU_GBL_IFS_MISC_USEC_DUR ; 
 int AR5K_INIT_RX_LATENCY_5210 ; 
 int AR5K_INIT_RX_LAT_MAX ; 
 int AR5K_INIT_TXF2TXD_START_DEFAULT ; 
 int AR5K_INIT_TXF2TXD_START_DELAY_10MHZ ; 
 int AR5K_INIT_TXF2TXD_START_DELAY_5MHZ ; 
 int AR5K_INIT_TX_LATENCY_5210 ; 
 int AR5K_INIT_TX_LAT_MIN ; 
#define  AR5K_MODE_11A 130 
#define  AR5K_MODE_11B 129 
#define  AR5K_MODE_11G 128 
 int /*<<< orphan*/  AR5K_PHY_RF_CTL2 ; 
 int /*<<< orphan*/  AR5K_PHY_RF_CTL2_TXF2TXD_START ; 
 int AR5K_REG_MS (int,int /*<<< orphan*/ ) ; 
 int AR5K_REG_SM (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_REG_WRITE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ AR5K_RF2316 ; 
 scalar_t__ AR5K_RF2317 ; 
 scalar_t__ AR5K_RF2413 ; 
 scalar_t__ AR5K_RF5112 ; 
 scalar_t__ AR5K_RF5413 ; 
 scalar_t__ AR5K_SREV_AR5211 ; 
 int /*<<< orphan*/  AR5K_USEC ; 
 int /*<<< orphan*/  AR5K_USEC_1 ; 
 int /*<<< orphan*/  AR5K_USEC_32 ; 
 int /*<<< orphan*/  AR5K_USEC_5211 ; 
 int /*<<< orphan*/  AR5K_USEC_RX_LATENCY_5210 ; 
 int /*<<< orphan*/  AR5K_USEC_RX_LATENCY_5211 ; 
 int /*<<< orphan*/  AR5K_USEC_TX_LATENCY_5210 ; 
 int /*<<< orphan*/  AR5K_USEC_TX_LATENCY_5211 ; 
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_hw_init_core_clock(struct ath5k_hw *ah)
{
	struct ieee80211_channel *channel = ah->ah_current_channel;
	struct ath_common *common = ath5k_hw_common(ah);
	u32 usec_reg, txlat, rxlat, usec, clock, sclock, txf2txs;

	/*
	 * Set core clock frequency
	 */
	switch (channel->hw_value) {
	case AR5K_MODE_11A:
		clock = 40;
		break;
	case AR5K_MODE_11B:
		clock = 22;
		break;
	case AR5K_MODE_11G:
	default:
		clock = 44;
		break;
	}

	/* Use clock multiplier for non-default
	 * bwmode */
	switch (ah->ah_bwmode) {
	case AR5K_BWMODE_40MHZ:
		clock *= 2;
		break;
	case AR5K_BWMODE_10MHZ:
		clock /= 2;
		break;
	case AR5K_BWMODE_5MHZ:
		clock /= 4;
		break;
	default:
		break;
	}

	common->clockrate = clock;

	/*
	 * Set USEC parameters
	 */
	/* Set USEC counter on PCU*/
	usec = clock - 1;
	usec = AR5K_REG_SM(usec, AR5K_USEC_1);

	/* Set usec duration on DCU */
	if (ah->ah_version != AR5K_AR5210)
		AR5K_REG_WRITE_BITS(ah, AR5K_DCU_GBL_IFS_MISC,
					AR5K_DCU_GBL_IFS_MISC_USEC_DUR,
					clock);

	/* Set 32MHz USEC counter */
	if ((ah->ah_radio == AR5K_RF5112) ||
	    (ah->ah_radio == AR5K_RF2413) ||
	    (ah->ah_radio == AR5K_RF5413) ||
	    (ah->ah_radio == AR5K_RF2316) ||
	    (ah->ah_radio == AR5K_RF2317))
		/* Remain on 40MHz clock ? */
		sclock = 40 - 1;
	else
		sclock = 32 - 1;
	sclock = AR5K_REG_SM(sclock, AR5K_USEC_32);

	/*
	 * Set tx/rx latencies
	 */
	usec_reg = ath5k_hw_reg_read(ah, AR5K_USEC_5211);
	txlat = AR5K_REG_MS(usec_reg, AR5K_USEC_TX_LATENCY_5211);
	rxlat = AR5K_REG_MS(usec_reg, AR5K_USEC_RX_LATENCY_5211);

	/*
	 * Set default Tx frame to Tx data start delay
	 */
	txf2txs = AR5K_INIT_TXF2TXD_START_DEFAULT;

	/*
	 * 5210 initvals don't include usec settings
	 * so we need to use magic values here for
	 * tx/rx latencies
	 */
	if (ah->ah_version == AR5K_AR5210) {
		/* same for turbo */
		txlat = AR5K_INIT_TX_LATENCY_5210;
		rxlat = AR5K_INIT_RX_LATENCY_5210;
	}

	if (ah->ah_mac_srev < AR5K_SREV_AR5211) {
		/* 5311 has different tx/rx latency masks
		 * from 5211, since we deal 5311 the same
		 * as 5211 when setting initvals, shift
		 * values here to their proper locations
		 *
		 * Note: Initvals indicate tx/rx/ latencies
		 * are the same for turbo mode */
		txlat = AR5K_REG_SM(txlat, AR5K_USEC_TX_LATENCY_5210);
		rxlat = AR5K_REG_SM(rxlat, AR5K_USEC_RX_LATENCY_5210);
	} else
	switch (ah->ah_bwmode) {
	case AR5K_BWMODE_10MHZ:
		txlat = AR5K_REG_SM(txlat * 2,
				AR5K_USEC_TX_LATENCY_5211);
		rxlat = AR5K_REG_SM(AR5K_INIT_RX_LAT_MAX,
				AR5K_USEC_RX_LATENCY_5211);
		txf2txs = AR5K_INIT_TXF2TXD_START_DELAY_10MHZ;
		break;
	case AR5K_BWMODE_5MHZ:
		txlat = AR5K_REG_SM(txlat * 4,
				AR5K_USEC_TX_LATENCY_5211);
		rxlat = AR5K_REG_SM(AR5K_INIT_RX_LAT_MAX,
				AR5K_USEC_RX_LATENCY_5211);
		txf2txs = AR5K_INIT_TXF2TXD_START_DELAY_5MHZ;
		break;
	case AR5K_BWMODE_40MHZ:
		txlat = AR5K_INIT_TX_LAT_MIN;
		rxlat = AR5K_REG_SM(rxlat / 2,
				AR5K_USEC_RX_LATENCY_5211);
		txf2txs = AR5K_INIT_TXF2TXD_START_DEFAULT;
		break;
	default:
		break;
	}

	usec_reg = (usec | sclock | txlat | rxlat);
	ath5k_hw_reg_write(ah, usec_reg, AR5K_USEC);

	/* On 5112 set tx frame to tx data start delay */
	if (ah->ah_radio == AR5K_RF5112) {
		AR5K_REG_WRITE_BITS(ah, AR5K_PHY_RF_CTL2,
					AR5K_PHY_RF_CTL2_TXF2TXD_START,
					txf2txs);
	}
}