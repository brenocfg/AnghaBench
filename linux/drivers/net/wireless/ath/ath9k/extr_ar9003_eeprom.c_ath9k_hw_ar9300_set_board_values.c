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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_SREV_9330 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9340 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9531 (struct ath_hw*) ; 
 int IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_hw_ant_ctrl_apply (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_apply_minccapwr_thresh (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_apply_tuning_caps (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_atten_apply (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_hw_drive_strength_apply (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_internal_regulator_apply (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_quick_drop_apply (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_hw_thermo_cal_apply (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_thermometer_apply (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_txend_to_xpa_off_apply (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_xlna_bias_strength_apply (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_xpa_bias_level_apply (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_xpa_timing_control_apply (struct ath_hw*,int) ; 

__attribute__((used)) static void ath9k_hw_ar9300_set_board_values(struct ath_hw *ah,
					     struct ath9k_channel *chan)
{
	bool is2ghz = IS_CHAN_2GHZ(chan);
	ar9003_hw_xpa_timing_control_apply(ah, is2ghz);
	ar9003_hw_xpa_bias_level_apply(ah, is2ghz);
	ar9003_hw_ant_ctrl_apply(ah, is2ghz);
	ar9003_hw_drive_strength_apply(ah);
	ar9003_hw_xlna_bias_strength_apply(ah, is2ghz);
	ar9003_hw_atten_apply(ah, chan);
	ar9003_hw_quick_drop_apply(ah, chan->channel);
	if (!AR_SREV_9330(ah) && !AR_SREV_9340(ah) && !AR_SREV_9531(ah))
		ar9003_hw_internal_regulator_apply(ah);
	ar9003_hw_apply_tuning_caps(ah);
	ar9003_hw_apply_minccapwr_thresh(ah, is2ghz);
	ar9003_hw_txend_to_xpa_off_apply(ah, is2ghz);
	ar9003_hw_thermometer_apply(ah);
	ar9003_hw_thermo_cal_apply(ah);
}