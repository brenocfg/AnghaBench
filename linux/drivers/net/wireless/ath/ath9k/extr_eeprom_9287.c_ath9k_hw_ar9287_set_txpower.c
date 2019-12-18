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
typedef  int /*<<< orphan*/  u16 ;
struct modal_eep_ar9287_header {scalar_t__ ht40PowerIncForPdadc; } ;
struct ath_regulatory {scalar_t__ max_power_level; } ;
struct ar9287_eeprom {struct modal_eep_ar9287_header modalHeader; } ;
struct TYPE_2__ {struct ar9287_eeprom map9287; } ;
struct ath_hw {scalar_t__ tpc_enabled; TYPE_1__ eeprom; } ;
struct ath9k_channel {int dummy; } ;
typedef  int /*<<< orphan*/  ratesArray ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 scalar_t__ AR9287_EEP_MINOR_VER_2 ; 
 int AR9287_PWR_TABLE_OFFSET_DB ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE1 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE2 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE3 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE4 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE5 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE6 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE7 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE8 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE9 ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE_MAX ; 
 scalar_t__ AR_PHY_POWER_TX_RATE_MAX_TPC_ENABLE ; 
 scalar_t__ ATH9K_POW_SM (scalar_t__,int) ; 
 int Ar5416RateSize ; 
 int /*<<< orphan*/  EEP_OL_PWRCTRL ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 scalar_t__ MAX_RATE_POWER ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ar5008_hw_init_rate_txpower (struct ath_hw*,scalar_t__*,struct ath9k_channel*,int) ; 
 scalar_t__ ath9k_hw_ar9287_get_eeprom (struct ath_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath9k_hw_ar9287_get_eeprom_rev (struct ath_hw*) ; 
 struct ath_regulatory* ath9k_hw_regulatory (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_ar9287_power_cal_table (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_set_ar9287_power_per_rate_table (struct ath_hw*,struct ath9k_channel*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ath9k_hw_update_regulatory_maxpower (struct ath_hw*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 size_t rate11l ; 
 size_t rate11s ; 
 size_t rate12mb ; 
 size_t rate18mb ; 
 size_t rate1l ; 
 size_t rate24mb ; 
 size_t rate2l ; 
 size_t rate2s ; 
 size_t rate36mb ; 
 size_t rate48mb ; 
 size_t rate54mb ; 
 size_t rate5_5l ; 
 size_t rate5_5s ; 
 size_t rate6mb ; 
 size_t rate9mb ; 
 size_t rateDupCck ; 
 size_t rateDupOfdm ; 
 size_t rateExtCck ; 
 size_t rateExtOfdm ; 
 size_t rateHt20_0 ; 
 size_t rateHt20_1 ; 
 size_t rateHt20_2 ; 
 size_t rateHt20_3 ; 
 size_t rateHt20_4 ; 
 size_t rateHt20_5 ; 
 size_t rateHt20_6 ; 
 size_t rateHt20_7 ; 
 size_t rateHt40_0 ; 
 size_t rateHt40_1 ; 
 size_t rateHt40_2 ; 
 size_t rateHt40_3 ; 
 size_t rateHt40_4 ; 
 size_t rateHt40_5 ; 
 size_t rateHt40_6 ; 
 size_t rateHt40_7 ; 
 size_t rateXr ; 

__attribute__((used)) static void ath9k_hw_ar9287_set_txpower(struct ath_hw *ah,
					struct ath9k_channel *chan, u16 cfgCtl,
					u8 twiceAntennaReduction,
					u8 powerLimit, bool test)
{
	struct ath_regulatory *regulatory = ath9k_hw_regulatory(ah);
	struct ar9287_eeprom *pEepData = &ah->eeprom.map9287;
	struct modal_eep_ar9287_header *pModal = &pEepData->modalHeader;
	int16_t ratesArray[Ar5416RateSize];
	u8 ht40PowerIncForPdadc = 2;
	int i;

	memset(ratesArray, 0, sizeof(ratesArray));

	if (ath9k_hw_ar9287_get_eeprom_rev(ah) >= AR9287_EEP_MINOR_VER_2)
		ht40PowerIncForPdadc = pModal->ht40PowerIncForPdadc;

	ath9k_hw_set_ar9287_power_per_rate_table(ah, chan,
						 &ratesArray[0], cfgCtl,
						 twiceAntennaReduction,
						 powerLimit);

	ath9k_hw_set_ar9287_power_cal_table(ah, chan);

	regulatory->max_power_level = 0;
	for (i = 0; i < ARRAY_SIZE(ratesArray); i++) {
		if (ratesArray[i] > MAX_RATE_POWER)
			ratesArray[i] = MAX_RATE_POWER;

		if (ratesArray[i] > regulatory->max_power_level)
			regulatory->max_power_level = ratesArray[i];
	}

	ath9k_hw_update_regulatory_maxpower(ah);

	if (test)
		return;

	for (i = 0; i < Ar5416RateSize; i++)
		ratesArray[i] -= AR9287_PWR_TABLE_OFFSET_DB * 2;

	ENABLE_REGWRITE_BUFFER(ah);

	/* OFDM power per rate */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE1,
		  ATH9K_POW_SM(ratesArray[rate18mb], 24)
		  | ATH9K_POW_SM(ratesArray[rate12mb], 16)
		  | ATH9K_POW_SM(ratesArray[rate9mb], 8)
		  | ATH9K_POW_SM(ratesArray[rate6mb], 0));

	REG_WRITE(ah, AR_PHY_POWER_TX_RATE2,
		  ATH9K_POW_SM(ratesArray[rate54mb], 24)
		  | ATH9K_POW_SM(ratesArray[rate48mb], 16)
		  | ATH9K_POW_SM(ratesArray[rate36mb], 8)
		  | ATH9K_POW_SM(ratesArray[rate24mb], 0));

	/* CCK power per rate */
	if (IS_CHAN_2GHZ(chan))	{
		REG_WRITE(ah, AR_PHY_POWER_TX_RATE3,
			  ATH9K_POW_SM(ratesArray[rate2s], 24)
			  | ATH9K_POW_SM(ratesArray[rate2l], 16)
			  | ATH9K_POW_SM(ratesArray[rateXr], 8)
			  | ATH9K_POW_SM(ratesArray[rate1l], 0));
		REG_WRITE(ah, AR_PHY_POWER_TX_RATE4,
			  ATH9K_POW_SM(ratesArray[rate11s], 24)
			  | ATH9K_POW_SM(ratesArray[rate11l], 16)
			  | ATH9K_POW_SM(ratesArray[rate5_5s], 8)
			  | ATH9K_POW_SM(ratesArray[rate5_5l], 0));
	}

	/* HT20 power per rate */
	REG_WRITE(ah, AR_PHY_POWER_TX_RATE5,
		  ATH9K_POW_SM(ratesArray[rateHt20_3], 24)
		  | ATH9K_POW_SM(ratesArray[rateHt20_2], 16)
		  | ATH9K_POW_SM(ratesArray[rateHt20_1], 8)
		  | ATH9K_POW_SM(ratesArray[rateHt20_0], 0));

	REG_WRITE(ah, AR_PHY_POWER_TX_RATE6,
		  ATH9K_POW_SM(ratesArray[rateHt20_7], 24)
		  | ATH9K_POW_SM(ratesArray[rateHt20_6], 16)
		  | ATH9K_POW_SM(ratesArray[rateHt20_5], 8)
		  | ATH9K_POW_SM(ratesArray[rateHt20_4], 0));

	/* HT40 power per rate */
	if (IS_CHAN_HT40(chan))	{
		if (ath9k_hw_ar9287_get_eeprom(ah, EEP_OL_PWRCTRL)) {
			REG_WRITE(ah, AR_PHY_POWER_TX_RATE7,
				  ATH9K_POW_SM(ratesArray[rateHt40_3], 24)
				  | ATH9K_POW_SM(ratesArray[rateHt40_2], 16)
				  | ATH9K_POW_SM(ratesArray[rateHt40_1], 8)
				  | ATH9K_POW_SM(ratesArray[rateHt40_0], 0));

			REG_WRITE(ah, AR_PHY_POWER_TX_RATE8,
				  ATH9K_POW_SM(ratesArray[rateHt40_7], 24)
				  | ATH9K_POW_SM(ratesArray[rateHt40_6], 16)
				  | ATH9K_POW_SM(ratesArray[rateHt40_5], 8)
				  | ATH9K_POW_SM(ratesArray[rateHt40_4], 0));
		} else {
			REG_WRITE(ah, AR_PHY_POWER_TX_RATE7,
				  ATH9K_POW_SM(ratesArray[rateHt40_3] +
					       ht40PowerIncForPdadc, 24)
				  | ATH9K_POW_SM(ratesArray[rateHt40_2] +
						 ht40PowerIncForPdadc, 16)
				  | ATH9K_POW_SM(ratesArray[rateHt40_1] +
						 ht40PowerIncForPdadc, 8)
				  | ATH9K_POW_SM(ratesArray[rateHt40_0] +
						 ht40PowerIncForPdadc, 0));

			REG_WRITE(ah, AR_PHY_POWER_TX_RATE8,
				  ATH9K_POW_SM(ratesArray[rateHt40_7] +
					       ht40PowerIncForPdadc, 24)
				  | ATH9K_POW_SM(ratesArray[rateHt40_6] +
						 ht40PowerIncForPdadc, 16)
				  | ATH9K_POW_SM(ratesArray[rateHt40_5] +
						 ht40PowerIncForPdadc, 8)
				  | ATH9K_POW_SM(ratesArray[rateHt40_4] +
						 ht40PowerIncForPdadc, 0));
		}

		/* Dup/Ext power per rate */
		REG_WRITE(ah, AR_PHY_POWER_TX_RATE9,
			  ATH9K_POW_SM(ratesArray[rateExtOfdm], 24)
			  | ATH9K_POW_SM(ratesArray[rateExtCck], 16)
			  | ATH9K_POW_SM(ratesArray[rateDupOfdm], 8)
			  | ATH9K_POW_SM(ratesArray[rateDupCck], 0));
	}

	/* TPC initializations */
	if (ah->tpc_enabled) {
		int ht40_delta;

		ht40_delta = (IS_CHAN_HT40(chan)) ? ht40PowerIncForPdadc : 0;
		ar5008_hw_init_rate_txpower(ah, ratesArray, chan, ht40_delta);
		/* Enable TPC */
		REG_WRITE(ah, AR_PHY_POWER_TX_RATE_MAX,
			MAX_RATE_POWER | AR_PHY_POWER_TX_RATE_MAX_TPC_ENABLE);
	} else {
		/* Disable TPC */
		REG_WRITE(ah, AR_PHY_POWER_TX_RATE_MAX, MAX_RATE_POWER);
	}

	REGWRITE_BUFFER_FLUSH(ah);
}