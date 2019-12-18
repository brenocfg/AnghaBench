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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tx_corr_coeff ;
struct coeff {int*** mag_coeff; int*** phs_coeff; int* iqc_coeff; } ;
struct ath_hw {int txchainmask; struct ath9k_hw_cal_data* caldata; } ;
struct ath9k_hw_cal_data {int** tx_corr_coeff; int* num_measures; int /*<<< orphan*/  cal_flags; } ;

/* Variables and functions */
 int AR9300_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_PHY_CALIBRATED_GAINS_0 ; 
 int /*<<< orphan*/  AR_PHY_RX_IQCAL_CORR_B0 ; 
 int /*<<< orphan*/  AR_PHY_RX_IQCAL_CORR_B0_LOOPBACK_IQCORR_EN ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_3 ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CONTROL_3_IQCORR_EN ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_00_COEFF_TABLE ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_01_COEFF_TABLE ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_B0 (int) ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_B1 (int) ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_CORR_COEFF_B2 (int) ; 
 int /*<<< orphan*/  AR_PHY_TX_IQCAL_STATUS_B0 ; 
 int /*<<< orphan*/  AR_SREV_9485 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9550 (struct ath_hw*) ; 
 int /*<<< orphan*/  MAX_MAG_DELTA ; 
 int MAX_MEASUREMENT ; 
 int /*<<< orphan*/  MAX_PHS_DELTA ; 
 int REG_READ_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TXIQCAL_DONE ; 
 int /*<<< orphan*/  ar9003_hw_detect_outlier (int**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ar9003_hw_tx_iq_cal_outlier_detection(struct ath_hw *ah,
						  struct coeff *coeff,
						  bool is_reusable)
{
	int i, im, nmeasurement;
	int magnitude, phase;
	u32 tx_corr_coeff[MAX_MEASUREMENT][AR9300_MAX_CHAINS];
	struct ath9k_hw_cal_data *caldata = ah->caldata;

	memset(tx_corr_coeff, 0, sizeof(tx_corr_coeff));
	for (i = 0; i < MAX_MEASUREMENT / 2; i++) {
		tx_corr_coeff[i * 2][0] = tx_corr_coeff[(i * 2) + 1][0] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B0(i);
		if (!AR_SREV_9485(ah)) {
			tx_corr_coeff[i * 2][1] =
			tx_corr_coeff[(i * 2) + 1][1] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B1(i);

			tx_corr_coeff[i * 2][2] =
			tx_corr_coeff[(i * 2) + 1][2] =
					AR_PHY_TX_IQCAL_CORR_COEFF_B2(i);
		}
	}

	/* Load the average of 2 passes */
	for (i = 0; i < AR9300_MAX_CHAINS; i++) {
		if (!(ah->txchainmask & (1 << i)))
			continue;
		nmeasurement = REG_READ_FIELD(ah,
				AR_PHY_TX_IQCAL_STATUS_B0,
				AR_PHY_CALIBRATED_GAINS_0);

		if (nmeasurement > MAX_MEASUREMENT)
			nmeasurement = MAX_MEASUREMENT;

		/*
		 * Skip normal outlier detection for AR9550.
		 */
		if (!AR_SREV_9550(ah)) {
			/* detect outlier only if nmeasurement > 1 */
			if (nmeasurement > 1) {
				/* Detect magnitude outlier */
				ar9003_hw_detect_outlier(coeff->mag_coeff[i],
							 nmeasurement,
							 MAX_MAG_DELTA);

				/* Detect phase outlier */
				ar9003_hw_detect_outlier(coeff->phs_coeff[i],
							 nmeasurement,
							 MAX_PHS_DELTA);
			}
		}

		for (im = 0; im < nmeasurement; im++) {
			magnitude = coeff->mag_coeff[i][im][0];
			phase = coeff->phs_coeff[i][im][0];

			coeff->iqc_coeff[0] =
				(phase & 0x7f) | ((magnitude & 0x7f) << 7);

			if ((im % 2) == 0)
				REG_RMW_FIELD(ah, tx_corr_coeff[im][i],
					AR_PHY_TX_IQCAL_CORR_COEFF_00_COEFF_TABLE,
					coeff->iqc_coeff[0]);
			else
				REG_RMW_FIELD(ah, tx_corr_coeff[im][i],
					AR_PHY_TX_IQCAL_CORR_COEFF_01_COEFF_TABLE,
					coeff->iqc_coeff[0]);

			if (caldata)
				caldata->tx_corr_coeff[im][i] =
					coeff->iqc_coeff[0];
		}
		if (caldata)
			caldata->num_measures[i] = nmeasurement;
	}

	REG_RMW_FIELD(ah, AR_PHY_TX_IQCAL_CONTROL_3,
		      AR_PHY_TX_IQCAL_CONTROL_3_IQCORR_EN, 0x1);
	REG_RMW_FIELD(ah, AR_PHY_RX_IQCAL_CORR_B0,
		      AR_PHY_RX_IQCAL_CORR_B0_LOOPBACK_IQCORR_EN, 0x1);

	if (caldata) {
		if (is_reusable)
			set_bit(TXIQCAL_DONE, &caldata->cal_flags);
		else
			clear_bit(TXIQCAL_DONE, &caldata->cal_flags);
	}

	return;
}