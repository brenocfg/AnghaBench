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
struct TYPE_2__ {int rx_chainmask; int /*<<< orphan*/  tx_chainmask; } ;
struct ath_hw {int enabled_cals; int ah_flags; int rxchainmask; int /*<<< orphan*/  txchainmask; TYPE_1__ caps; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int AH_FASTCC ; 
 int AR9300_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_PHY_ACTIVE ; 
 int /*<<< orphan*/  AR_PHY_ACTIVE_DIS ; 
 int /*<<< orphan*/  AR_PHY_ACTIVE_EN ; 
 int /*<<< orphan*/  AR_PHY_CL_CAL_CTL ; 
 int /*<<< orphan*/  AR_PHY_CL_CAL_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_0 ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_1 ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_1_IQCORR_I_Q_COFF_DELPT ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 int /*<<< orphan*/  DELPT ; 
 scalar_t__ IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HALF_RATE (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_QUARTER_RATE (struct ath9k_channel*) ; 
 int MAXIQCAL ; 
 scalar_t__ REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TX_CL_CAL ; 
 int TX_IQ_ON_AGC_CAL ; 
 int /*<<< orphan*/  ar9003_hw_dynamic_osdac_selection (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ar9003_hw_init_cal_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_manual_peak_cal (struct ath_hw*,int,scalar_t__) ; 
 int /*<<< orphan*/  ar9003_hw_set_chain_masks (struct ath_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_hw_tx_iq_cal_post_proc (struct ath_hw*,int,int) ; 
 int ar9003_hw_tx_iq_cal_run (struct ath_hw*) ; 
 int do_ar9003_agc_cal (struct ath_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool ar9003_hw_init_cal_soc(struct ath_hw *ah,
				   struct ath9k_channel *chan)
{
	bool txiqcal_done = false;
	bool status = true;
	bool run_agc_cal = false, sep_iq_cal = false;
	int i = 0;

	/* Use chip chainmask only for calibration */
	ar9003_hw_set_chain_masks(ah, ah->caps.rx_chainmask, ah->caps.tx_chainmask);

	if (ah->enabled_cals & TX_CL_CAL) {
		REG_SET_BIT(ah, AR_PHY_CL_CAL_CTL, AR_PHY_CL_CAL_ENABLE);
		run_agc_cal = true;
	}

	if (IS_CHAN_HALF_RATE(chan) || IS_CHAN_QUARTER_RATE(chan))
		goto skip_tx_iqcal;

	/* Do Tx IQ Calibration */
	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_1,
		      AR_PHY_TX_IQCAL_CONTROL_1_IQCORR_I_Q_COFF_DELPT,
		      DELPT);

	/*
	 * For AR9485 or later chips, TxIQ cal runs as part of
	 * AGC calibration. Specifically, AR9550 in SoC chips.
	 */
	if (ah->enabled_cals & TX_IQ_ON_AGC_CAL) {
		if (REG_READ_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_0,
				   AR_PHY_TX_IQCAL_CONTROL_0_ENABLE_TXIQ_CAL)) {
				txiqcal_done = true;
		} else {
			txiqcal_done = false;
		}
		run_agc_cal = true;
	} else {
		sep_iq_cal = true;
		run_agc_cal = true;
	}

	/*
	 * In the SoC family, this will run for AR9300, AR9331 and AR9340.
	 */
	if (sep_iq_cal) {
		txiqcal_done = ar9003_hw_tx_iq_cal_run(ah);
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_DIS);
		udelay(5);
		REG_WRITE(ah, AR_PHY_ACTIVE, AR_PHY_ACTIVE_EN);
	}

	if (AR_SREV_9550(ah) && IS_CHAN_2GHZ(chan)) {
		if (!ar9003_hw_dynamic_osdac_selection(ah, txiqcal_done))
			return false;
	}

skip_tx_iqcal:
	if (run_agc_cal || !(ah->ah_flags & AH_FASTCC)) {
		for (i = 0; i < AR9300_MAX_CHAINS; i++) {
			if (!(ah->rxchainmask & (1 << i)))
				continue;

			ar9003_hw_manual_peak_cal(ah, i,
						  IS_CHAN_2GHZ(chan));
		}

		/*
		 * For non-AR9550 chips, we just trigger AGC calibration
		 * in the HW, poll for completion and then process
		 * the results.
		 *
		 * For AR955x, we run it multiple times and use
		 * median IQ correction.
		 */
		if (!AR_SREV_9550(ah)) {
			status = do_ar9003_agc_cal(ah);
			if (!status)
				return false;

			if (txiqcal_done)
				ar9003_hw_tx_iq_cal_post_proc(ah, 0, false);
		} else {
			if (!txiqcal_done) {
				status = do_ar9003_agc_cal(ah);
				if (!status)
					return false;
			} else {
				for (i = 0; i < MAXIQCAL; i++) {
					status = do_ar9003_agc_cal(ah);
					if (!status)
						return false;
					ar9003_hw_tx_iq_cal_post_proc(ah, i, false);
				}
			}
		}
	}

	/* Revert chainmask to runtime parameters */
	ar9003_hw_set_chain_masks(ah, ah->rxchainmask, ah->txchainmask);

	ar9003_hw_init_cal_common(ah);

	return true;
}