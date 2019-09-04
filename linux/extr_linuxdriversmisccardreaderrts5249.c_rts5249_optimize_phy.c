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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D3_DELINK_MODE_EN ; 
 int /*<<< orphan*/  PHY_BPCR ; 
 int PHY_BPCR_CMIRROR_EN ; 
 int PHY_BPCR_IBRXSEL ; 
 int PHY_BPCR_IBTXSEL ; 
 int PHY_BPCR_IB_FILTER ; 
 int /*<<< orphan*/  PHY_FLD3 ; 
 int PHY_FLD3_RXDELINK ; 
 int PHY_FLD3_TIMER_4 ; 
 int PHY_FLD3_TIMER_6 ; 
 int /*<<< orphan*/  PHY_FLD4 ; 
 int PHY_FLD4_BER_CHK_EN ; 
 int PHY_FLD4_BER_COUNT ; 
 int PHY_FLD4_BER_TIMER ; 
 int PHY_FLD4_FLDEN_SEL ; 
 int PHY_FLD4_REQ_ADDA ; 
 int PHY_FLD4_REQ_REF ; 
 int PHY_FLD4_RXAMP_OFF ; 
 int /*<<< orphan*/  PHY_PCR ; 
 int PHY_PCR_FORCE_CODE ; 
 int PHY_PCR_OOBS_CALI_50 ; 
 int PHY_PCR_OOBS_SEN_90 ; 
 int PHY_PCR_OOBS_VCM_08 ; 
 int PHY_PCR_RSSI_EN ; 
 int PHY_PCR_RX10K ; 
 int /*<<< orphan*/  PHY_RCR1 ; 
 int PHY_RCR1_ADP_TIME_4 ; 
 int PHY_RCR1_VCO_COARSE ; 
 int /*<<< orphan*/  PHY_RCR2 ; 
 int PHY_RCR2_CALIB_LATE ; 
 int PHY_RCR2_CDR_SC_12P ; 
 int PHY_RCR2_CDR_SR_2 ; 
 int PHY_RCR2_EMPHASE_EN ; 
 int PHY_RCR2_FREQSEL_12 ; 
 int PHY_RCR2_NADJR ; 
 int /*<<< orphan*/  PHY_RDR ; 
 int PHY_RDR_RXDSEL_1_9 ; 
 int /*<<< orphan*/  PHY_REV ; 
 int PHY_REV_CLKREQ_DT_1_0 ; 
 int PHY_REV_CLKREQ_TX_EN ; 
 int PHY_REV_P1_EN ; 
 int PHY_REV_RESV ; 
 int PHY_REV_RXIDLE_EN ; 
 int PHY_REV_RXIDLE_LATCHED ; 
 int PHY_REV_RX_PWST ; 
 int PHY_REV_STOP_CLKRD ; 
 int PHY_REV_STOP_CLKWR ; 
 int PHY_SSC_AUTO_PWD ; 
 int /*<<< orphan*/  PHY_TUNE ; 
 int PHY_TUNE_SDBUS_33 ; 
 int PHY_TUNE_TUNEA12 ; 
 int PHY_TUNE_TUNED12 ; 
 int PHY_TUNE_TUNED18 ; 
 int PHY_TUNE_TUNEREF_1_0 ; 
 int PHY_TUNE_VBGSEL_1252 ; 
 int /*<<< orphan*/  PM_CTRL3 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtsx_pci_write_phy_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int) ; 
 int rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rts5249_optimize_phy(struct rtsx_pcr *pcr)
{
	int err;

	err = rtsx_pci_write_register(pcr, PM_CTRL3, D3_DELINK_MODE_EN, 0x00);
	if (err < 0)
		return err;

	err = rtsx_pci_write_phy_register(pcr, PHY_REV,
			PHY_REV_RESV | PHY_REV_RXIDLE_LATCHED |
			PHY_REV_P1_EN | PHY_REV_RXIDLE_EN |
			PHY_REV_CLKREQ_TX_EN | PHY_REV_RX_PWST |
			PHY_REV_CLKREQ_DT_1_0 | PHY_REV_STOP_CLKRD |
			PHY_REV_STOP_CLKWR);
	if (err < 0)
		return err;

	msleep(1);

	err = rtsx_pci_write_phy_register(pcr, PHY_BPCR,
			PHY_BPCR_IBRXSEL | PHY_BPCR_IBTXSEL |
			PHY_BPCR_IB_FILTER | PHY_BPCR_CMIRROR_EN);
	if (err < 0)
		return err;

	err = rtsx_pci_write_phy_register(pcr, PHY_PCR,
			PHY_PCR_FORCE_CODE | PHY_PCR_OOBS_CALI_50 |
			PHY_PCR_OOBS_VCM_08 | PHY_PCR_OOBS_SEN_90 |
			PHY_PCR_RSSI_EN | PHY_PCR_RX10K);
	if (err < 0)
		return err;

	err = rtsx_pci_write_phy_register(pcr, PHY_RCR2,
			PHY_RCR2_EMPHASE_EN | PHY_RCR2_NADJR |
			PHY_RCR2_CDR_SR_2 | PHY_RCR2_FREQSEL_12 |
			PHY_RCR2_CDR_SC_12P | PHY_RCR2_CALIB_LATE);
	if (err < 0)
		return err;

	err = rtsx_pci_write_phy_register(pcr, PHY_FLD4,
			PHY_FLD4_FLDEN_SEL | PHY_FLD4_REQ_REF |
			PHY_FLD4_RXAMP_OFF | PHY_FLD4_REQ_ADDA |
			PHY_FLD4_BER_COUNT | PHY_FLD4_BER_TIMER |
			PHY_FLD4_BER_CHK_EN);
	if (err < 0)
		return err;
	err = rtsx_pci_write_phy_register(pcr, PHY_RDR,
			PHY_RDR_RXDSEL_1_9 | PHY_SSC_AUTO_PWD);
	if (err < 0)
		return err;
	err = rtsx_pci_write_phy_register(pcr, PHY_RCR1,
			PHY_RCR1_ADP_TIME_4 | PHY_RCR1_VCO_COARSE);
	if (err < 0)
		return err;
	err = rtsx_pci_write_phy_register(pcr, PHY_FLD3,
			PHY_FLD3_TIMER_4 | PHY_FLD3_TIMER_6 |
			PHY_FLD3_RXDELINK);
	if (err < 0)
		return err;

	return rtsx_pci_write_phy_register(pcr, PHY_TUNE,
			PHY_TUNE_TUNEREF_1_0 | PHY_TUNE_VBGSEL_1252 |
			PHY_TUNE_SDBUS_33 | PHY_TUNE_TUNED18 |
			PHY_TUNE_TUNED12 | PHY_TUNE_TUNEA12);
}