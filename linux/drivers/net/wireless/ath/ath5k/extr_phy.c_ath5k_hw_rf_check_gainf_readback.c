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
typedef  int u32 ;
struct ath5k_rf_reg {int dummy; } ;
struct TYPE_2__ {int g_high; int g_low; int g_current; } ;
struct ath5k_hw {scalar_t__ ah_radio; TYPE_1__ ah_gain; void* ah_rf_regs_count; int /*<<< orphan*/ * ah_rf_banks; } ;

/* Variables and functions */
 int AR5K_GAIN_DYN_ADJUST_HI_MARGIN ; 
 int AR5K_GAIN_DYN_ADJUST_LO_MARGIN ; 
 scalar_t__ AR5K_RF5111 ; 
 int /*<<< orphan*/  AR5K_RF_MIXVGA_OVR ; 
 int /*<<< orphan*/  AR5K_RF_RFGAIN_STEP ; 
 void* ARRAY_SIZE (struct ath5k_rf_reg*) ; 
 int ath5k_hw_rfb_op (struct ath5k_hw*,struct ath5k_rf_reg const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ath5k_rf_reg* rf_regs_5111 ; 
 struct ath5k_rf_reg* rf_regs_5112 ; 

__attribute__((used)) static bool
ath5k_hw_rf_check_gainf_readback(struct ath5k_hw *ah)
{
	const struct ath5k_rf_reg *rf_regs;
	u32 step, mix_ovr, level[4];

	if (ah->ah_rf_banks == NULL)
		return false;

	if (ah->ah_radio == AR5K_RF5111) {

		rf_regs = rf_regs_5111;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5111);

		step = ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_RFGAIN_STEP,
			false);

		level[0] = 0;
		level[1] = (step == 63) ? 50 : step + 4;
		level[2] = (step != 63) ? 64 : level[0];
		level[3] = level[2] + 50;

		ah->ah_gain.g_high = level[3] -
			(step == 63 ? AR5K_GAIN_DYN_ADJUST_HI_MARGIN : -5);
		ah->ah_gain.g_low = level[0] +
			(step == 63 ? AR5K_GAIN_DYN_ADJUST_LO_MARGIN : 0);
	} else {

		rf_regs = rf_regs_5112;
		ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5112);

		mix_ovr = ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_MIXVGA_OVR,
			false);

		level[0] = level[2] = 0;

		if (mix_ovr == 1) {
			level[1] = level[3] = 83;
		} else {
			level[1] = level[3] = 107;
			ah->ah_gain.g_high = 55;
		}
	}

	return (ah->ah_gain.g_current >= level[0] &&
			ah->ah_gain.g_current <= level[1]) ||
		(ah->ah_gain.g_current >= level[2] &&
			ah->ah_gain.g_current <= level[3]);
}