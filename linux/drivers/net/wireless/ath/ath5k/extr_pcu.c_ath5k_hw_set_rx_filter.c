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
struct ath5k_hw {scalar_t__ ah_version; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 scalar_t__ AR5K_AR5212 ; 
 int /*<<< orphan*/  AR5K_PHY_ERR_FIL ; 
 int AR5K_PHY_ERR_FIL_CCK ; 
 int AR5K_PHY_ERR_FIL_OFDM ; 
 int AR5K_PHY_ERR_FIL_RADAR ; 
 int /*<<< orphan*/  AR5K_REG_DISABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR5K_RXCFG ; 
 int /*<<< orphan*/  AR5K_RXCFG_ZLFDMA ; 
 int /*<<< orphan*/  AR5K_RX_FILTER ; 
 int AR5K_RX_FILTER_PHYERR ; 
 int AR5K_RX_FILTER_PROM ; 
 int AR5K_RX_FILTER_RADARERR ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 

void
ath5k_hw_set_rx_filter(struct ath5k_hw *ah, u32 filter)
{
	u32 data = 0;

	/* Set PHY error filter register on 5212*/
	if (ah->ah_version == AR5K_AR5212) {
		if (filter & AR5K_RX_FILTER_RADARERR)
			data |= AR5K_PHY_ERR_FIL_RADAR;
		if (filter & AR5K_RX_FILTER_PHYERR)
			data |= AR5K_PHY_ERR_FIL_OFDM | AR5K_PHY_ERR_FIL_CCK;
	}

	/*
	 * The AR5210 uses promiscuous mode to detect radar activity
	 */
	if (ah->ah_version == AR5K_AR5210 &&
			(filter & AR5K_RX_FILTER_RADARERR)) {
		filter &= ~AR5K_RX_FILTER_RADARERR;
		filter |= AR5K_RX_FILTER_PROM;
	}

	/*Zero length DMA (phy error reporting) */
	if (data)
		AR5K_REG_ENABLE_BITS(ah, AR5K_RXCFG, AR5K_RXCFG_ZLFDMA);
	else
		AR5K_REG_DISABLE_BITS(ah, AR5K_RXCFG, AR5K_RXCFG_ZLFDMA);

	/*Write RX Filter register*/
	ath5k_hw_reg_write(ah, filter & 0xff, AR5K_RX_FILTER);

	/*Write PHY error filter register on 5212*/
	if (ah->ah_version == AR5K_AR5212)
		ath5k_hw_reg_write(ah, data, AR5K_PHY_ERR_FIL);

}