#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_9__ {int tx_chainmask; } ;
struct TYPE_14__ {int tempSlopeLow; int tempSlopeHigh; } ;
struct TYPE_11__ {int miscConfiguration; int txrxMask; int featureEnable; } ;
struct TYPE_13__ {int tempSlope; } ;
struct TYPE_12__ {int* tempslopextension; } ;
struct TYPE_10__ {int tempSlope; } ;
struct ar9300_eeprom {TYPE_7__ base_ext2; TYPE_4__ baseEepHeader; TYPE_6__ modalHeader5G; int /*<<< orphan*/ * calFreqPier5G; TYPE_5__ base_ext1; TYPE_3__ modalHeader2G; } ;
struct TYPE_8__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_2__ caps; TYPE_1__ eeprom; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_TPC_11_B0 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B1 ; 
 int /*<<< orphan*/  AR_PHY_TPC_11_B2 ; 
 int /*<<< orphan*/  AR_PHY_TPC_18 ; 
 int /*<<< orphan*/  AR_PHY_TPC_18_THERM_CAL_VALUE ; 
 int /*<<< orphan*/  AR_PHY_TPC_19 ; 
 int /*<<< orphan*/  AR_PHY_TPC_19_ALPHA_THERM ; 
 int /*<<< orphan*/  AR_PHY_TPC_19_B1 ; 
 int /*<<< orphan*/  AR_PHY_TPC_19_B1_ALPHA_THERM ; 
 int /*<<< orphan*/  AR_PHY_TPC_19_B2 ; 
 int /*<<< orphan*/  AR_PHY_TPC_6_B0 ; 
 int /*<<< orphan*/  AR_PHY_TPC_6_B1 ; 
 int /*<<< orphan*/  AR_PHY_TPC_6_B2 ; 
 int /*<<< orphan*/  AR_PHY_TPC_6_ERROR_EST_MODE ; 
 int AR_PHY_TPC_6_ERROR_EST_MODE_S ; 
 int /*<<< orphan*/  AR_PHY_TPC_OLPC_GAIN_DELTA ; 
 int AR_PHY_TPC_OLPC_GAIN_DELTA_S ; 
 scalar_t__ AR_SREV_9462_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9531 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9561 (struct ath_hw*) ; 
 int BIT (int) ; 
 int FBIN2FREQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ar9003_hw_power_interpolate (int,int*,int*,int) ; 

__attribute__((used)) static void ar9003_hw_power_control_override(struct ath_hw *ah,
					     int frequency,
					     int *correction,
					     int *voltage, int *temperature)
{
	int temp_slope = 0, temp_slope1 = 0, temp_slope2 = 0;
	struct ar9300_eeprom *eep = &ah->eeprom.ar9300_eep;
	int f[8], t[8], t1[3], t2[3], i;

	REG_RMW(ah, AR_PHY_TPC_11_B0,
		(correction[0] << AR_PHY_TPC_OLPC_GAIN_DELTA_S),
		AR_PHY_TPC_OLPC_GAIN_DELTA);
	if (ah->caps.tx_chainmask & BIT(1))
		REG_RMW(ah, AR_PHY_TPC_11_B1,
			(correction[1] << AR_PHY_TPC_OLPC_GAIN_DELTA_S),
			AR_PHY_TPC_OLPC_GAIN_DELTA);
	if (ah->caps.tx_chainmask & BIT(2))
		REG_RMW(ah, AR_PHY_TPC_11_B2,
			(correction[2] << AR_PHY_TPC_OLPC_GAIN_DELTA_S),
			AR_PHY_TPC_OLPC_GAIN_DELTA);

	/* enable open loop power control on chip */
	REG_RMW(ah, AR_PHY_TPC_6_B0,
		(3 << AR_PHY_TPC_6_ERROR_EST_MODE_S),
		AR_PHY_TPC_6_ERROR_EST_MODE);
	if (ah->caps.tx_chainmask & BIT(1))
		REG_RMW(ah, AR_PHY_TPC_6_B1,
			(3 << AR_PHY_TPC_6_ERROR_EST_MODE_S),
			AR_PHY_TPC_6_ERROR_EST_MODE);
	if (ah->caps.tx_chainmask & BIT(2))
		REG_RMW(ah, AR_PHY_TPC_6_B2,
			(3 << AR_PHY_TPC_6_ERROR_EST_MODE_S),
			AR_PHY_TPC_6_ERROR_EST_MODE);

	/*
	 * enable temperature compensation
	 * Need to use register names
	 */
	if (frequency < 4000) {
		temp_slope = eep->modalHeader2G.tempSlope;
	} else {
		if (AR_SREV_9550(ah)) {
			t[0] = eep->base_ext1.tempslopextension[2];
			t1[0] = eep->base_ext1.tempslopextension[3];
			t2[0] = eep->base_ext1.tempslopextension[4];
			f[0] = 5180;

			t[1] = eep->modalHeader5G.tempSlope;
			t1[1] = eep->base_ext1.tempslopextension[0];
			t2[1] = eep->base_ext1.tempslopextension[1];
			f[1] = 5500;

			t[2] = eep->base_ext1.tempslopextension[5];
			t1[2] = eep->base_ext1.tempslopextension[6];
			t2[2] = eep->base_ext1.tempslopextension[7];
			f[2] = 5785;

			temp_slope = ar9003_hw_power_interpolate(frequency,
								 f, t, 3);
			temp_slope1 = ar9003_hw_power_interpolate(frequency,
								   f, t1, 3);
			temp_slope2 = ar9003_hw_power_interpolate(frequency,
								   f, t2, 3);

			goto tempslope;
		}

		if ((eep->baseEepHeader.miscConfiguration & 0x20) != 0) {
			for (i = 0; i < 8; i++) {
				t[i] = eep->base_ext1.tempslopextension[i];
				f[i] = FBIN2FREQ(eep->calFreqPier5G[i], 0);
			}
			temp_slope = ar9003_hw_power_interpolate((s32) frequency,
								 f, t, 8);
		} else if (eep->base_ext2.tempSlopeLow != 0) {
			t[0] = eep->base_ext2.tempSlopeLow;
			f[0] = 5180;
			t[1] = eep->modalHeader5G.tempSlope;
			f[1] = 5500;
			t[2] = eep->base_ext2.tempSlopeHigh;
			f[2] = 5785;
			temp_slope = ar9003_hw_power_interpolate((s32) frequency,
								 f, t, 3);
		} else {
			temp_slope = eep->modalHeader5G.tempSlope;
		}
	}

tempslope:
	if (AR_SREV_9550(ah) || AR_SREV_9531(ah) || AR_SREV_9561(ah)) {
		u8 txmask = (eep->baseEepHeader.txrxMask & 0xf0) >> 4;

		/*
		 * AR955x has tempSlope register for each chain.
		 * Check whether temp_compensation feature is enabled or not.
		 */
		if (eep->baseEepHeader.featureEnable & 0x1) {
			if (frequency < 4000) {
				if (txmask & BIT(0))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      eep->base_ext2.tempSlopeLow);
				if (txmask & BIT(1))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19_B1,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      temp_slope);
				if (txmask & BIT(2))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19_B2,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      eep->base_ext2.tempSlopeHigh);
			} else {
				if (txmask & BIT(0))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      temp_slope);
				if (txmask & BIT(1))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19_B1,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      temp_slope1);
				if (txmask & BIT(2))
					REG_RMW_FIELD(ah, AR_PHY_TPC_19_B2,
						      AR_PHY_TPC_19_ALPHA_THERM,
						      temp_slope2);
			}
		} else {
			/*
			 * If temp compensation is not enabled,
			 * set all registers to 0.
			 */
			if (txmask & BIT(0))
				REG_RMW_FIELD(ah, AR_PHY_TPC_19,
					      AR_PHY_TPC_19_ALPHA_THERM, 0);
			if (txmask & BIT(1))
				REG_RMW_FIELD(ah, AR_PHY_TPC_19_B1,
					      AR_PHY_TPC_19_ALPHA_THERM, 0);
			if (txmask & BIT(2))
				REG_RMW_FIELD(ah, AR_PHY_TPC_19_B2,
					      AR_PHY_TPC_19_ALPHA_THERM, 0);
		}
	} else {
		REG_RMW_FIELD(ah, AR_PHY_TPC_19,
			      AR_PHY_TPC_19_ALPHA_THERM, temp_slope);
	}

	if (AR_SREV_9462_20_OR_LATER(ah))
		REG_RMW_FIELD(ah, AR_PHY_TPC_19_B1,
			      AR_PHY_TPC_19_B1_ALPHA_THERM, temp_slope);


	REG_RMW_FIELD(ah, AR_PHY_TPC_18, AR_PHY_TPC_18_THERM_CAL_VALUE,
		      temperature[0]);
}