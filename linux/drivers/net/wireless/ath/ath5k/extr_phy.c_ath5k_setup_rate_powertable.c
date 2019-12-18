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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct ath5k_rate_pcal_info {int target_power_6to24; int target_power_36; int target_power_48; int target_power_54; } ;
struct TYPE_2__ {int* txp_rates_power_table; int txp_min_pwr; int txp_cur_pwr; int txp_ofdm; int txp_offset; scalar_t__ txp_cck_ofdm_gainf_delta; scalar_t__ txp_max_pwr; } ;
struct ath5k_hw {scalar_t__ ah_phy_revision; TYPE_1__ ah_txpower; } ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ AR5K_EEPROM_MODE_11G ; 
 scalar_t__ AR5K_SREV_PHY_5212A ; 
 int min (int,int) ; 

__attribute__((used)) static void
ath5k_setup_rate_powertable(struct ath5k_hw *ah, u16 max_pwr,
			struct ath5k_rate_pcal_info *rate_info,
			u8 ee_mode)
{
	unsigned int i;
	u16 *rates;
	s16 rate_idx_scaled = 0;

	/* max_pwr is power level we got from driver/user in 0.5dB
	 * units, switch to 0.25dB units so we can compare */
	max_pwr *= 2;
	max_pwr = min(max_pwr, (u16) ah->ah_txpower.txp_max_pwr) / 2;

	/* apply rate limits */
	rates = ah->ah_txpower.txp_rates_power_table;

	/* OFDM rates 6 to 24Mb/s */
	for (i = 0; i < 5; i++)
		rates[i] = min(max_pwr, rate_info->target_power_6to24);

	/* Rest OFDM rates */
	rates[5] = min(rates[0], rate_info->target_power_36);
	rates[6] = min(rates[0], rate_info->target_power_48);
	rates[7] = min(rates[0], rate_info->target_power_54);

	/* CCK rates */
	/* 1L */
	rates[8] = min(rates[0], rate_info->target_power_6to24);
	/* 2L */
	rates[9] = min(rates[0], rate_info->target_power_36);
	/* 2S */
	rates[10] = min(rates[0], rate_info->target_power_36);
	/* 5L */
	rates[11] = min(rates[0], rate_info->target_power_48);
	/* 5S */
	rates[12] = min(rates[0], rate_info->target_power_48);
	/* 11L */
	rates[13] = min(rates[0], rate_info->target_power_54);
	/* 11S */
	rates[14] = min(rates[0], rate_info->target_power_54);

	/* XR rates */
	rates[15] = min(rates[0], rate_info->target_power_6to24);

	/* CCK rates have different peak to average ratio
	 * so we have to tweak their power so that gainf
	 * correction works ok. For this we use OFDM to
	 * CCK delta from eeprom */
	if ((ee_mode == AR5K_EEPROM_MODE_11G) &&
	(ah->ah_phy_revision < AR5K_SREV_PHY_5212A))
		for (i = 8; i <= 15; i++)
			rates[i] -= ah->ah_txpower.txp_cck_ofdm_gainf_delta;

	/* Save min/max and current tx power for this channel
	 * in 0.25dB units.
	 *
	 * Note: We use rates[0] for current tx power because
	 * it covers most of the rates, in most cases. It's our
	 * tx power limit and what the user expects to see. */
	ah->ah_txpower.txp_min_pwr = 2 * rates[7];
	ah->ah_txpower.txp_cur_pwr = 2 * rates[0];

	/* Set max txpower for correct OFDM operation on all rates
	 * -that is the txpower for 54Mbit-, it's used for the PAPD
	 * gain probe and it's in 0.5dB units */
	ah->ah_txpower.txp_ofdm = rates[7];

	/* Now that we have all rates setup use table offset to
	 * match the power range set by user with the power indices
	 * on PCDAC/PDADC table */
	for (i = 0; i < 16; i++) {
		rate_idx_scaled = rates[i] + ah->ah_txpower.txp_offset;
		/* Don't get out of bounds */
		if (rate_idx_scaled > 63)
			rate_idx_scaled = 63;
		if (rate_idx_scaled < 0)
			rate_idx_scaled = 0;
		rates[i] = rate_idx_scaled;
	}
}