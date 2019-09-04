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
 int /*<<< orphan*/  IC_VER_A ; 
 int /*<<< orphan*/  PHY_ANA08 ; 
 int PHY_ANA08_RX_EQ_DCGAIN ; 
 int PHY_ANA08_RX_EQ_VAL ; 
 int PHY_ANA08_SCP ; 
 int PHY_ANA08_SEL_IPI ; 
 int PHY_ANA08_SEL_RX_EN ; 
 int /*<<< orphan*/  PHY_ANA1A ; 
 int PHY_ANA1A_REV ; 
 int PHY_ANA1A_RXT_BIST ; 
 int PHY_ANA1A_TXR_BIST ; 
 int PHY_ANA1A_TXR_LOOPBACK ; 
 int /*<<< orphan*/  PHY_ANA1D ; 
 int PHY_ANA1D_DEBUG_ADDR ; 
 int /*<<< orphan*/  PHY_DIG1E ; 
 int PHY_DIG1E_D0_X_D1 ; 
 int PHY_DIG1E_RCLK_REF_HOST ; 
 int PHY_DIG1E_RCLK_RX_EIDLE_ON ; 
 int PHY_DIG1E_RCLK_TX_EN_KEEP ; 
 int PHY_DIG1E_RCLK_TX_TERM_KEEP ; 
 int PHY_DIG1E_REV ; 
 int PHY_DIG1E_RX_EN_KEEP ; 
 int PHY_DIG1E_RX_ON_HOST ; 
 int PHY_DIG1E_RX_TERM_KEEP ; 
 int PHY_DIG1E_TX_EN_KEEP ; 
 int PHY_DIG1E_TX_TERM_KEEP ; 
 int /*<<< orphan*/  PHY_PCR ; 
 int PHY_PCR_FORCE_CODE ; 
 int PHY_PCR_OOBS_CALI_50 ; 
 int PHY_PCR_OOBS_SEN_90 ; 
 int PHY_PCR_OOBS_VCM_08 ; 
 int PHY_PCR_RSSI_EN ; 
 int /*<<< orphan*/  PHY_SSCCR2 ; 
 int PHY_SSCCR2_PLL_NCODE ; 
 int PHY_SSCCR2_TIME0 ; 
 int PHY_SSCCR2_TIME2_WIDTH ; 
 int /*<<< orphan*/  PHY_SSCCR3 ; 
 int PHY_SSCCR3_CHECK_DELAY ; 
 int PHY_SSCCR3_STEP_IN ; 
 int /*<<< orphan*/  RTS524A_PM_CTRL3 ; 
 scalar_t__ is_version (struct rtsx_pcr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_write_phy_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int) ; 
 int rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rts524a_optimize_phy(struct rtsx_pcr *pcr)
{
	int err;

	err = rtsx_pci_write_register(pcr, RTS524A_PM_CTRL3,
		D3_DELINK_MODE_EN, 0x00);
	if (err < 0)
		return err;

	rtsx_pci_write_phy_register(pcr, PHY_PCR,
		PHY_PCR_FORCE_CODE | PHY_PCR_OOBS_CALI_50 |
		PHY_PCR_OOBS_VCM_08 | PHY_PCR_OOBS_SEN_90 | PHY_PCR_RSSI_EN);
	rtsx_pci_write_phy_register(pcr, PHY_SSCCR3,
		PHY_SSCCR3_STEP_IN | PHY_SSCCR3_CHECK_DELAY);

	if (is_version(pcr, 0x524A, IC_VER_A)) {
		rtsx_pci_write_phy_register(pcr, PHY_SSCCR3,
			PHY_SSCCR3_STEP_IN | PHY_SSCCR3_CHECK_DELAY);
		rtsx_pci_write_phy_register(pcr, PHY_SSCCR2,
			PHY_SSCCR2_PLL_NCODE | PHY_SSCCR2_TIME0 |
			PHY_SSCCR2_TIME2_WIDTH);
		rtsx_pci_write_phy_register(pcr, PHY_ANA1A,
			PHY_ANA1A_TXR_LOOPBACK | PHY_ANA1A_RXT_BIST |
			PHY_ANA1A_TXR_BIST | PHY_ANA1A_REV);
		rtsx_pci_write_phy_register(pcr, PHY_ANA1D,
			PHY_ANA1D_DEBUG_ADDR);
		rtsx_pci_write_phy_register(pcr, PHY_DIG1E,
			PHY_DIG1E_REV | PHY_DIG1E_D0_X_D1 |
			PHY_DIG1E_RX_ON_HOST | PHY_DIG1E_RCLK_REF_HOST |
			PHY_DIG1E_RCLK_TX_EN_KEEP |
			PHY_DIG1E_RCLK_TX_TERM_KEEP |
			PHY_DIG1E_RCLK_RX_EIDLE_ON | PHY_DIG1E_TX_TERM_KEEP |
			PHY_DIG1E_RX_TERM_KEEP | PHY_DIG1E_TX_EN_KEEP |
			PHY_DIG1E_RX_EN_KEEP);
	}

	rtsx_pci_write_phy_register(pcr, PHY_ANA08,
		PHY_ANA08_RX_EQ_DCGAIN | PHY_ANA08_SEL_RX_EN |
		PHY_ANA08_RX_EQ_VAL | PHY_ANA08_SCP | PHY_ANA08_SEL_IPI);

	return 0;
}