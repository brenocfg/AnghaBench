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
struct ath_common {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int AH_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  AR_PHY_ADC_CTL ; 
 int /*<<< orphan*/  AR_PHY_ADC_CTL_OFF_PWDADC ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL_CAL ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL_FLTR_CAL ; 
 int /*<<< orphan*/  AR_PHY_CL_CAL_CTL ; 
 int /*<<< orphan*/  AR_PHY_CL_CAL_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_FC_DYN2040_EN ; 
 int /*<<< orphan*/  AR_PHY_PARALLEL_CAL_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_TPCRG1 ; 
 int /*<<< orphan*/  AR_PHY_TPCRG1_PD_CAL_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_TURBO ; 
 int /*<<< orphan*/  CALIBRATE ; 
 scalar_t__ IS_CHAN_HT20 (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_wait (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool ar9285_hw_cl_cal(struct ath_hw *ah, struct ath9k_channel *chan)
{
	struct ath_common *common = ath9k_hw_common(ah);

	REG_SET_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_CL_CAL_ENABLE);
	if (IS_CHAN_HT20(chan)) {
		REG_SET_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_PARALLEL_CAL_ENABLE);
		REG_SET_BIT(ah, AR_PHY_TURBO, AR_PHY_FC_DYN2040_EN);
		REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL,
			    AR_PHY_AGC_CONTROL_FLTR_CAL);
		REG_CLR_BIT(ah, AR_PHY_TPCRG1, AR_PHY_TPCRG1_PD_CAL_ENABLE);
		REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_CAL);
		if (!ath9k_hw_wait(ah, AR_PHY_AGC_CONTROL,
				  AR_PHY_AGC_CONTROL_CAL, 0, AH_WAIT_TIMEOUT)) {
			ath_dbg(common, CALIBRATE,
				"offset calibration failed to complete in %d ms; noisy environment?\n",
				AH_WAIT_TIMEOUT / 1000);
			return false;
		}
		REG_CLR_BIT(ah, AR_PHY_TURBO, AR_PHY_FC_DYN2040_EN);
		REG_CLR_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_PARALLEL_CAL_ENABLE);
		REG_CLR_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_CL_CAL_ENABLE);
	}
	REG_CLR_BIT(ah, AR_PHY_ADC_CTL, AR_PHY_ADC_CTL_OFF_PWDADC);
	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_FLTR_CAL);
	REG_SET_BIT(ah, AR_PHY_TPCRG1, AR_PHY_TPCRG1_PD_CAL_ENABLE);
	REG_SET_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_CAL);
	if (!ath9k_hw_wait(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_CAL,
			  0, AH_WAIT_TIMEOUT)) {
		ath_dbg(common, CALIBRATE,
			"offset calibration failed to complete in %d ms; noisy environment?\n",
			AH_WAIT_TIMEOUT / 1000);
		return false;
	}

	REG_SET_BIT(ah, AR_PHY_ADC_CTL, AR_PHY_ADC_CTL_OFF_PWDADC);
	REG_CLR_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_CL_CAL_ENABLE);
	REG_CLR_BIT(ah, AR_PHY_AGC_CONTROL, AR_PHY_AGC_CONTROL_FLTR_CAL);

	return true;
}