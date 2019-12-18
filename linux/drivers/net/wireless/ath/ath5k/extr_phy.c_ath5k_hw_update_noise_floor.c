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
typedef  size_t u8 ;
typedef  int u32 ;
struct ath5k_eeprom_info {int* ee_noise_floor_thr; } ;
struct TYPE_2__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {int ah_noise_floor; int /*<<< orphan*/  ah_cal_mask; int /*<<< orphan*/  ah_current_channel; TYPE_1__ ah_capabilities; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_CALIBRATION_NF ; 
 int /*<<< orphan*/  AR5K_PHY_AGCCTL ; 
 int AR5K_PHY_AGCCTL_NF ; 
 int AR5K_PHY_AGCCTL_NF_EN ; 
 int AR5K_PHY_AGCCTL_NF_NOUPDATE ; 
 int /*<<< orphan*/  AR5K_PHY_NF ; 
 int AR5K_PHY_NF_M ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AR5K_REG_MASKED_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int,int) ; 
 int AR5K_TUNE_CCA_MAX_GOOD_VALUE ; 
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_CALIBRATE ; 
 size_t ath5k_eeprom_mode_from_channel (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int ath5k_hw_get_median_noise_floor (struct ath5k_hw*) ; 
 int ath5k_hw_read_measured_noise_floor (struct ath5k_hw*) ; 
 int ath5k_hw_reg_read (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_reg_write (struct ath5k_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_register_timeout (struct ath5k_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath5k_hw_update_nfcal_hist (struct ath5k_hw*,int) ; 

void
ath5k_hw_update_noise_floor(struct ath5k_hw *ah)
{
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u32 val;
	s16 nf, threshold;
	u8 ee_mode;

	/* keep last value if calibration hasn't completed */
	if (ath5k_hw_reg_read(ah, AR5K_PHY_AGCCTL) & AR5K_PHY_AGCCTL_NF) {
		ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
			"NF did not complete in calibration window\n");

		return;
	}

	ah->ah_cal_mask |= AR5K_CALIBRATION_NF;

	ee_mode = ath5k_eeprom_mode_from_channel(ah, ah->ah_current_channel);

	/* completed NF calibration, test threshold */
	nf = ath5k_hw_read_measured_noise_floor(ah);
	threshold = ee->ee_noise_floor_thr[ee_mode];

	if (nf > threshold) {
		ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
			"noise floor failure detected; "
			"read %d, threshold %d\n",
			nf, threshold);

		nf = AR5K_TUNE_CCA_MAX_GOOD_VALUE;
	}

	ath5k_hw_update_nfcal_hist(ah, nf);
	nf = ath5k_hw_get_median_noise_floor(ah);

	/* load noise floor (in .5 dBm) so the hardware will use it */
	val = ath5k_hw_reg_read(ah, AR5K_PHY_NF) & ~AR5K_PHY_NF_M;
	val |= (nf * 2) & AR5K_PHY_NF_M;
	ath5k_hw_reg_write(ah, val, AR5K_PHY_NF);

	AR5K_REG_MASKED_BITS(ah, AR5K_PHY_AGCCTL, AR5K_PHY_AGCCTL_NF,
		~(AR5K_PHY_AGCCTL_NF_EN | AR5K_PHY_AGCCTL_NF_NOUPDATE));

	ath5k_hw_register_timeout(ah, AR5K_PHY_AGCCTL, AR5K_PHY_AGCCTL_NF,
		0, false);

	/*
	 * Load a high max CCA Power value (-50 dBm in .5 dBm units)
	 * so that we're not capped by the median we just loaded.
	 * This will be used as the initial value for the next noise
	 * floor calibration.
	 */
	val = (val & ~AR5K_PHY_NF_M) | ((-50 * 2) & AR5K_PHY_NF_M);
	ath5k_hw_reg_write(ah, val, AR5K_PHY_NF);
	AR5K_REG_ENABLE_BITS(ah, AR5K_PHY_AGCCTL,
		AR5K_PHY_AGCCTL_NF_EN |
		AR5K_PHY_AGCCTL_NF_NOUPDATE |
		AR5K_PHY_AGCCTL_NF);

	ah->ah_noise_floor = nf;

	ah->ah_cal_mask &= ~AR5K_CALIBRATION_NF;

	ATH5K_DBG(ah, ATH5K_DEBUG_CALIBRATE,
		"noise floor calibrated: %d\n", nf);
}