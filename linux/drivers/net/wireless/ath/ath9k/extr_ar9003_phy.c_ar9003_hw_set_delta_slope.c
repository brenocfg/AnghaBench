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
struct chan_centers {int synth_center; } ;
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_SGI_DELTA ; 
 int /*<<< orphan*/  AR_PHY_SGI_DSC_EXP ; 
 int /*<<< orphan*/  AR_PHY_SGI_DSC_MAN ; 
 int /*<<< orphan*/  AR_PHY_TIMING3 ; 
 int /*<<< orphan*/  AR_PHY_TIMING3_DSC_EXP ; 
 int /*<<< orphan*/  AR_PHY_TIMING3_DSC_MAN ; 
 scalar_t__ IS_CHAN_HALF_RATE (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (struct ath9k_channel*) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_get_channel_centers (struct ath_hw*,struct ath9k_channel*,struct chan_centers*) ; 
 int /*<<< orphan*/  ath9k_hw_get_delta_slope_vals (struct ath_hw*,int,int*,int*) ; 

__attribute__((used)) static void ar9003_hw_set_delta_slope(struct ath_hw *ah,
				      struct ath9k_channel *chan)
{
	u32 coef_scaled, ds_coef_exp, ds_coef_man;
	u32 clockMhzScaled = 0x64000000;
	struct chan_centers centers;

	/*
	 * half and quarter rate can divide the scaled clock by 2 or 4
	 * scale for selected channel bandwidth
	 */
	if (IS_CHAN_HALF_RATE(chan))
		clockMhzScaled = clockMhzScaled >> 1;
	else if (IS_CHAN_QUARTER_RATE(chan))
		clockMhzScaled = clockMhzScaled >> 2;

	/*
	 * ALGO -> coef = 1e8/fcarrier*fclock/40;
	 * scaled coef to provide precision for this floating calculation
	 */
	ath9k_hw_get_channel_centers(ah, chan, &centers);
	coef_scaled = clockMhzScaled / centers.synth_center;

	ath9k_hw_get_delta_slope_vals(ah, coef_scaled, &ds_coef_man,
				      &ds_coef_exp);

	REG_RMW_FIELD(ah, AR_PHY_TIMING3,
		      AR_PHY_TIMING3_DSC_MAN, ds_coef_man);
	REG_RMW_FIELD(ah, AR_PHY_TIMING3,
		      AR_PHY_TIMING3_DSC_EXP, ds_coef_exp);

	/*
	 * For Short GI,
	 * scaled coeff is 9/10 that of normal coeff
	 */
	coef_scaled = (9 * coef_scaled) / 10;

	ath9k_hw_get_delta_slope_vals(ah, coef_scaled, &ds_coef_man,
				      &ds_coef_exp);

	/* for short gi */
	REG_RMW_FIELD(ah, AR_PHY_SGI_DELTA,
		      AR_PHY_SGI_DSC_MAN, ds_coef_man);
	REG_RMW_FIELD(ah, AR_PHY_SGI_DELTA,
		      AR_PHY_SGI_DSC_EXP, ds_coef_exp);
}