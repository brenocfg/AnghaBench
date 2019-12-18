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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct modal_eep_ar9287_header {int /*<<< orphan*/  xpaBiasLvl; int /*<<< orphan*/  txFrameToPaOn; int /*<<< orphan*/  txFrameToDataStart; int /*<<< orphan*/  ob_pal_off; int /*<<< orphan*/  ob_qam; int /*<<< orphan*/  ob_psk; int /*<<< orphan*/  ob_cck; int /*<<< orphan*/  db2; int /*<<< orphan*/  db1; int /*<<< orphan*/  thresh62; int /*<<< orphan*/  txEndToRxOn; int /*<<< orphan*/  txFrameToXpaOn; int /*<<< orphan*/  txEndToXpaOff; int /*<<< orphan*/  adcDesiredSize; int /*<<< orphan*/  switchSettling; int /*<<< orphan*/  swSettleHt40; int /*<<< orphan*/ * rxTxMarginCh; int /*<<< orphan*/ * bswAtten; int /*<<< orphan*/ * bswMargin; int /*<<< orphan*/ * txRxAttenCh; int /*<<< orphan*/ * iqCalQCh; int /*<<< orphan*/ * iqCalICh; int /*<<< orphan*/ * antCtrlChain; int /*<<< orphan*/  antCtrlCommon; } ;
struct ar9287_eeprom {struct modal_eep_ar9287_header modalHeader; } ;
struct TYPE_2__ {struct ar9287_eeprom map9287; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9280_PHY_CCA_THRESH62 ; 
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_ATTEN ; 
 int /*<<< orphan*/  AR9280_PHY_RXGAIN_TXRX_MARGIN ; 
 scalar_t__ AR9287_AN_RF2G3_CH0 ; 
 scalar_t__ AR9287_AN_RF2G3_CH1 ; 
 int AR9287_AN_RF2G3_DB1 ; 
 int AR9287_AN_RF2G3_DB2 ; 
 int AR9287_AN_RF2G3_OB_CCK ; 
 int AR9287_AN_RF2G3_OB_PAL_OFF ; 
 int AR9287_AN_RF2G3_OB_PSK ; 
 int AR9287_AN_RF2G3_OB_QAM ; 
 int /*<<< orphan*/  AR9287_AN_TOP2 ; 
 int /*<<< orphan*/  AR9287_AN_TOP2_XPABIAS_LVL ; 
 int /*<<< orphan*/  AR9287_AN_TOP2_XPABIAS_LVL_S ; 
 int AR9287_MAX_CHAINS ; 
 scalar_t__ AR_PHY_CCA ; 
 scalar_t__ AR_PHY_DESIRED_SZ ; 
 int /*<<< orphan*/  AR_PHY_DESIRED_SZ_ADC ; 
 scalar_t__ AR_PHY_EXT_CCA0 ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA0_THRESH62 ; 
 scalar_t__ AR_PHY_GAIN_2GHZ ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_DB ; 
 int /*<<< orphan*/  AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN ; 
 scalar_t__ AR_PHY_RF_CTL2 ; 
 scalar_t__ AR_PHY_RF_CTL3 ; 
 scalar_t__ AR_PHY_RF_CTL4 ; 
 int AR_PHY_RF_CTL4_FRAME_XPAA_ON ; 
 int AR_PHY_RF_CTL4_FRAME_XPAB_ON ; 
 int AR_PHY_RF_CTL4_TX_END_XPAA_OFF ; 
 int AR_PHY_RF_CTL4_TX_END_XPAB_OFF ; 
 scalar_t__ AR_PHY_RXGAIN ; 
 scalar_t__ AR_PHY_SETTLING ; 
 int /*<<< orphan*/  AR_PHY_SETTLING_SWITCH ; 
 scalar_t__ AR_PHY_SWITCH_CHAIN_0 ; 
 scalar_t__ AR_PHY_SWITCH_COM ; 
 scalar_t__ AR_PHY_TIMING_CTRL4 (int /*<<< orphan*/ ) ; 
 int AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF ; 
 int AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF ; 
 int /*<<< orphan*/  AR_PHY_TX_END_DATA_START ; 
 int /*<<< orphan*/  AR_PHY_TX_END_PA_ON ; 
 int /*<<< orphan*/  AR_PHY_TX_END_TO_A2_RX_ON ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 int REG_READ (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,scalar_t__,int) ; 
 int SM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_analog_shift_regwrite (struct ath_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  ath9k_hw_analog_shift_rmw (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_hw_ar9287_set_board_values(struct ath_hw *ah,
					     struct ath9k_channel *chan)
{
	struct ar9287_eeprom *eep = &ah->eeprom.map9287;
	struct modal_eep_ar9287_header *pModal = &eep->modalHeader;
	u32 regChainOffset, regval;
	u8 txRxAttenLocal;
	int i;

	pModal = &eep->modalHeader;

	REG_WRITE(ah, AR_PHY_SWITCH_COM, le32_to_cpu(pModal->antCtrlCommon));

	for (i = 0; i < AR9287_MAX_CHAINS; i++)	{
		regChainOffset = i * 0x1000;

		REG_WRITE(ah, AR_PHY_SWITCH_CHAIN_0 + regChainOffset,
			  le32_to_cpu(pModal->antCtrlChain[i]));

		REG_WRITE(ah, AR_PHY_TIMING_CTRL4(0) + regChainOffset,
			  (REG_READ(ah, AR_PHY_TIMING_CTRL4(0) + regChainOffset)
			   & ~(AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF |
			       AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF)) |
			  SM(pModal->iqCalICh[i],
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_I_COFF) |
			  SM(pModal->iqCalQCh[i],
			     AR_PHY_TIMING_CTRL4_IQCORR_Q_Q_COFF));

		txRxAttenLocal = pModal->txRxAttenCh[i];

		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_MARGIN,
			      pModal->bswMargin[i]);
		REG_RMW_FIELD(ah, AR_PHY_GAIN_2GHZ + regChainOffset,
			      AR_PHY_GAIN_2GHZ_XATTEN1_DB,
			      pModal->bswAtten[i]);
		REG_RMW_FIELD(ah, AR_PHY_RXGAIN + regChainOffset,
			      AR9280_PHY_RXGAIN_TXRX_ATTEN,
			      txRxAttenLocal);
		REG_RMW_FIELD(ah, AR_PHY_RXGAIN + regChainOffset,
			      AR9280_PHY_RXGAIN_TXRX_MARGIN,
			      pModal->rxTxMarginCh[i]);
	}


	if (IS_CHAN_HT40(chan))
		REG_RMW_FIELD(ah, AR_PHY_SETTLING,
			      AR_PHY_SETTLING_SWITCH, pModal->swSettleHt40);
	else
		REG_RMW_FIELD(ah, AR_PHY_SETTLING,
			      AR_PHY_SETTLING_SWITCH, pModal->switchSettling);

	REG_RMW_FIELD(ah, AR_PHY_DESIRED_SZ,
		      AR_PHY_DESIRED_SZ_ADC, pModal->adcDesiredSize);

	REG_WRITE(ah, AR_PHY_RF_CTL4,
		  SM(pModal->txEndToXpaOff, AR_PHY_RF_CTL4_TX_END_XPAA_OFF)
		  | SM(pModal->txEndToXpaOff, AR_PHY_RF_CTL4_TX_END_XPAB_OFF)
		  | SM(pModal->txFrameToXpaOn, AR_PHY_RF_CTL4_FRAME_XPAA_ON)
		  | SM(pModal->txFrameToXpaOn, AR_PHY_RF_CTL4_FRAME_XPAB_ON));

	REG_RMW_FIELD(ah, AR_PHY_RF_CTL3,
		      AR_PHY_TX_END_TO_A2_RX_ON, pModal->txEndToRxOn);

	REG_RMW_FIELD(ah, AR_PHY_CCA,
		      AR9280_PHY_CCA_THRESH62, pModal->thresh62);
	REG_RMW_FIELD(ah, AR_PHY_EXT_CCA0,
		      AR_PHY_EXT_CCA0_THRESH62, pModal->thresh62);

	regval = REG_READ(ah, AR9287_AN_RF2G3_CH0);
	regval &= ~(AR9287_AN_RF2G3_DB1 |
		    AR9287_AN_RF2G3_DB2 |
		    AR9287_AN_RF2G3_OB_CCK |
		    AR9287_AN_RF2G3_OB_PSK |
		    AR9287_AN_RF2G3_OB_QAM |
		    AR9287_AN_RF2G3_OB_PAL_OFF);
	regval |= (SM(pModal->db1, AR9287_AN_RF2G3_DB1) |
		   SM(pModal->db2, AR9287_AN_RF2G3_DB2) |
		   SM(pModal->ob_cck, AR9287_AN_RF2G3_OB_CCK) |
		   SM(pModal->ob_psk, AR9287_AN_RF2G3_OB_PSK) |
		   SM(pModal->ob_qam, AR9287_AN_RF2G3_OB_QAM) |
		   SM(pModal->ob_pal_off, AR9287_AN_RF2G3_OB_PAL_OFF));

	ath9k_hw_analog_shift_regwrite(ah, AR9287_AN_RF2G3_CH0, regval);

	regval = REG_READ(ah, AR9287_AN_RF2G3_CH1);
	regval &= ~(AR9287_AN_RF2G3_DB1 |
		    AR9287_AN_RF2G3_DB2 |
		    AR9287_AN_RF2G3_OB_CCK |
		    AR9287_AN_RF2G3_OB_PSK |
		    AR9287_AN_RF2G3_OB_QAM |
		    AR9287_AN_RF2G3_OB_PAL_OFF);
	regval |= (SM(pModal->db1, AR9287_AN_RF2G3_DB1) |
		   SM(pModal->db2, AR9287_AN_RF2G3_DB2) |
		   SM(pModal->ob_cck, AR9287_AN_RF2G3_OB_CCK) |
		   SM(pModal->ob_psk, AR9287_AN_RF2G3_OB_PSK) |
		   SM(pModal->ob_qam, AR9287_AN_RF2G3_OB_QAM) |
		   SM(pModal->ob_pal_off, AR9287_AN_RF2G3_OB_PAL_OFF));

	ath9k_hw_analog_shift_regwrite(ah, AR9287_AN_RF2G3_CH1, regval);

	REG_RMW_FIELD(ah, AR_PHY_RF_CTL2,
		      AR_PHY_TX_END_DATA_START, pModal->txFrameToDataStart);
	REG_RMW_FIELD(ah, AR_PHY_RF_CTL2,
		      AR_PHY_TX_END_PA_ON, pModal->txFrameToPaOn);

	ath9k_hw_analog_shift_rmw(ah, AR9287_AN_TOP2,
				  AR9287_AN_TOP2_XPABIAS_LVL,
				  AR9287_AN_TOP2_XPABIAS_LVL_S,
				  pModal->xpaBiasLvl);
}