#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ath5k_eeprom_info {int** ee_ob; int** ee_db; int* ee_tx_end2xlna_enable; int* ee_thr_62; int* ee_tx_end2xpa_disable; int* ee_tx_frm2xpa_enable; int* ee_pga_desired_size; int* ee_noise_floor_thr; int* ee_xlna_gain; int* ee_x_gain; int* ee_xpd; int* ee_fixed_bias; int* ee_false_detect; int* ee_xr_power; int* ee_i_gain; int ee_cck_ofdm_power_delta; int ee_scaled_cck_delta; int* ee_i_cal; int* ee_q_cal; int* ee_margin_tx_rx; int* ee_turbo_max_power; int ee_cck_ofdm_gain_delta; scalar_t__ ee_version; int* ee_switch_settling_turbo; int* ee_atn_tx_rx_turbo; int* ee_margin_tx_rx_turbo; int* ee_adc_desired_size_turbo; int* ee_pga_desired_size_turbo; int ee_pd_gain_overlap; int /*<<< orphan*/  ee_misc0; scalar_t__* ee_n_piers; TYPE_3__* ee_pwr_cal_g; TYPE_2__* ee_pwr_cal_b; scalar_t__* ee_adc_desired_size; } ;
struct TYPE_4__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {scalar_t__ ah_ee_version; TYPE_1__ ah_capabilities; } ;
typedef  scalar_t__ s8 ;
struct TYPE_6__ {void* freq; } ;
struct TYPE_5__ {void* freq; } ;

/* Variables and functions */
 int AR5K_EEPROM_CCK_OFDM_DELTA ; 
 void* AR5K_EEPROM_CHANNEL_DIS ; 
 int AR5K_EEPROM_EEMAP (int /*<<< orphan*/ ) ; 
 int AR5K_EEPROM_I_GAIN ; 
#define  AR5K_EEPROM_MODE_11A 130 
#define  AR5K_EEPROM_MODE_11B 129 
#define  AR5K_EEPROM_MODE_11G 128 
 int /*<<< orphan*/  AR5K_EEPROM_READ (int /*<<< orphan*/ ,int) ; 
 scalar_t__ AR5K_EEPROM_VERSION_3_2 ; 
 scalar_t__ AR5K_EEPROM_VERSION_3_3 ; 
 scalar_t__ AR5K_EEPROM_VERSION_3_4 ; 
 scalar_t__ AR5K_EEPROM_VERSION_4_0 ; 
 scalar_t__ AR5K_EEPROM_VERSION_4_1 ; 
 scalar_t__ AR5K_EEPROM_VERSION_4_2 ; 
 scalar_t__ AR5K_EEPROM_VERSION_4_6 ; 
 scalar_t__ AR5K_EEPROM_VERSION_5_0 ; 
 void* ath5k_eeprom_bin2freq (struct ath5k_eeprom_info*,int,unsigned int) ; 

__attribute__((used)) static int ath5k_eeprom_read_modes(struct ath5k_hw *ah, u32 *offset,
		unsigned int mode)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 o = *offset;
	u16 val;

	ee->ee_n_piers[mode] = 0;
	AR5K_EEPROM_READ(o++, val);
	ee->ee_adc_desired_size[mode]	= (s8)((val >> 8) & 0xff);
	switch (mode) {
	case AR5K_EEPROM_MODE_11A:
		ee->ee_ob[mode][3]	= (val >> 5) & 0x7;
		ee->ee_db[mode][3]	= (val >> 2) & 0x7;
		ee->ee_ob[mode][2]	= (val << 1) & 0x7;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_ob[mode][2]	|= (val >> 15) & 0x1;
		ee->ee_db[mode][2]	= (val >> 12) & 0x7;
		ee->ee_ob[mode][1]	= (val >> 9) & 0x7;
		ee->ee_db[mode][1]	= (val >> 6) & 0x7;
		ee->ee_ob[mode][0]	= (val >> 3) & 0x7;
		ee->ee_db[mode][0]	= val & 0x7;
		break;
	case AR5K_EEPROM_MODE_11G:
	case AR5K_EEPROM_MODE_11B:
		ee->ee_ob[mode][1]	= (val >> 4) & 0x7;
		ee->ee_db[mode][1]	= val & 0x7;
		break;
	}

	AR5K_EEPROM_READ(o++, val);
	ee->ee_tx_end2xlna_enable[mode]	= (val >> 8) & 0xff;
	ee->ee_thr_62[mode]		= val & 0xff;

	if (ah->ah_ee_version <= AR5K_EEPROM_VERSION_3_2)
		ee->ee_thr_62[mode] = mode == AR5K_EEPROM_MODE_11A ? 15 : 28;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_tx_end2xpa_disable[mode]	= (val >> 8) & 0xff;
	ee->ee_tx_frm2xpa_enable[mode]	= val & 0xff;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_pga_desired_size[mode]	= (val >> 8) & 0xff;

	if ((val & 0xff) & 0x80)
		ee->ee_noise_floor_thr[mode] = -((((val & 0xff) ^ 0xff)) + 1);
	else
		ee->ee_noise_floor_thr[mode] = val & 0xff;

	if (ah->ah_ee_version <= AR5K_EEPROM_VERSION_3_2)
		ee->ee_noise_floor_thr[mode] =
		    mode == AR5K_EEPROM_MODE_11A ? -54 : -1;

	AR5K_EEPROM_READ(o++, val);
	ee->ee_xlna_gain[mode]		= (val >> 5) & 0xff;
	ee->ee_x_gain[mode]		= (val >> 1) & 0xf;
	ee->ee_xpd[mode]		= val & 0x1;

	if (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_0 &&
	    mode != AR5K_EEPROM_MODE_11B)
		ee->ee_fixed_bias[mode] = (val >> 13) & 0x1;

	if (ah->ah_ee_version >= AR5K_EEPROM_VERSION_3_3) {
		AR5K_EEPROM_READ(o++, val);
		ee->ee_false_detect[mode] = (val >> 6) & 0x7f;

		if (mode == AR5K_EEPROM_MODE_11A)
			ee->ee_xr_power[mode] = val & 0x3f;
		else {
			/* b_DB_11[bg] and b_OB_11[bg] */
			ee->ee_ob[mode][0] = val & 0x7;
			ee->ee_db[mode][0] = (val >> 3) & 0x7;
		}
	}

	if (ah->ah_ee_version < AR5K_EEPROM_VERSION_3_4) {
		ee->ee_i_gain[mode] = AR5K_EEPROM_I_GAIN;
		ee->ee_cck_ofdm_power_delta = AR5K_EEPROM_CCK_OFDM_DELTA;
	} else {
		ee->ee_i_gain[mode] = (val >> 13) & 0x7;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_i_gain[mode] |= (val << 3) & 0x38;

		if (mode == AR5K_EEPROM_MODE_11G) {
			ee->ee_cck_ofdm_power_delta = (val >> 3) & 0xff;
			if (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_6)
				ee->ee_scaled_cck_delta = (val >> 11) & 0x1f;
		}
	}

	if (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_0 &&
			mode == AR5K_EEPROM_MODE_11A) {
		ee->ee_i_cal[mode] = (val >> 8) & 0x3f;
		ee->ee_q_cal[mode] = (val >> 3) & 0x1f;
	}

	if (ah->ah_ee_version < AR5K_EEPROM_VERSION_4_0)
		goto done;

	/* Note: >= v5 have bg freq piers on another location
	 * so these freq piers are ignored for >= v5 (should be 0xff
	 * anyway) */
	switch (mode) {
	case AR5K_EEPROM_MODE_11A:
		if (ah->ah_ee_version < AR5K_EEPROM_VERSION_4_1)
			break;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_margin_tx_rx[mode] = val & 0x3f;
		break;
	case AR5K_EEPROM_MODE_11B:
		AR5K_EEPROM_READ(o++, val);

		ee->ee_pwr_cal_b[0].freq =
			ath5k_eeprom_bin2freq(ee, val & 0xff, mode);
		if (ee->ee_pwr_cal_b[0].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		ee->ee_pwr_cal_b[1].freq =
			ath5k_eeprom_bin2freq(ee, (val >> 8) & 0xff, mode);
		if (ee->ee_pwr_cal_b[1].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_pwr_cal_b[2].freq =
			ath5k_eeprom_bin2freq(ee, val & 0xff, mode);
		if (ee->ee_pwr_cal_b[2].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		if (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_1)
			ee->ee_margin_tx_rx[mode] = (val >> 8) & 0x3f;
		break;
	case AR5K_EEPROM_MODE_11G:
		AR5K_EEPROM_READ(o++, val);

		ee->ee_pwr_cal_g[0].freq =
			ath5k_eeprom_bin2freq(ee, val & 0xff, mode);
		if (ee->ee_pwr_cal_g[0].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		ee->ee_pwr_cal_g[1].freq =
			ath5k_eeprom_bin2freq(ee, (val >> 8) & 0xff, mode);
		if (ee->ee_pwr_cal_g[1].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_turbo_max_power[mode] = val & 0x7f;
		ee->ee_xr_power[mode] = (val >> 7) & 0x3f;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_pwr_cal_g[2].freq =
			ath5k_eeprom_bin2freq(ee, val & 0xff, mode);
		if (ee->ee_pwr_cal_g[2].freq != AR5K_EEPROM_CHANNEL_DIS)
			ee->ee_n_piers[mode]++;

		if (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_1)
			ee->ee_margin_tx_rx[mode] = (val >> 8) & 0x3f;

		AR5K_EEPROM_READ(o++, val);
		ee->ee_i_cal[mode] = (val >> 5) & 0x3f;
		ee->ee_q_cal[mode] = val & 0x1f;

		if (ah->ah_ee_version >= AR5K_EEPROM_VERSION_4_2) {
			AR5K_EEPROM_READ(o++, val);
			ee->ee_cck_ofdm_gain_delta = val & 0xff;
		}
		break;
	}

	/*
	 * Read turbo mode information on newer EEPROM versions
	 */
	if (ee->ee_version < AR5K_EEPROM_VERSION_5_0)
		goto done;

	switch (mode) {
	case AR5K_EEPROM_MODE_11A:
		ee->ee_switch_settling_turbo[mode] = (val >> 6) & 0x7f;

		ee->ee_atn_tx_rx_turbo[mode] = (val >> 13) & 0x7;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_atn_tx_rx_turbo[mode] |= (val & 0x7) << 3;
		ee->ee_margin_tx_rx_turbo[mode] = (val >> 3) & 0x3f;

		ee->ee_adc_desired_size_turbo[mode] = (val >> 9) & 0x7f;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_adc_desired_size_turbo[mode] |= (val & 0x1) << 7;
		ee->ee_pga_desired_size_turbo[mode] = (val >> 1) & 0xff;

		if (AR5K_EEPROM_EEMAP(ee->ee_misc0) >= 2)
			ee->ee_pd_gain_overlap = (val >> 9) & 0xf;
		break;
	case AR5K_EEPROM_MODE_11G:
		ee->ee_switch_settling_turbo[mode] = (val >> 8) & 0x7f;

		ee->ee_atn_tx_rx_turbo[mode] = (val >> 15) & 0x7;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_atn_tx_rx_turbo[mode] |= (val & 0x1f) << 1;
		ee->ee_margin_tx_rx_turbo[mode] = (val >> 5) & 0x3f;

		ee->ee_adc_desired_size_turbo[mode] = (val >> 11) & 0x7f;
		AR5K_EEPROM_READ(o++, val);
		ee->ee_adc_desired_size_turbo[mode] |= (val & 0x7) << 5;
		ee->ee_pga_desired_size_turbo[mode] = (val >> 3) & 0xff;
		break;
	}

done:
	/* return new offset */
	*offset = o;

	return 0;
}