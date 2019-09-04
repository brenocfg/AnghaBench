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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct sky2_status_le {int dummy; } ;
struct sky2_hw {scalar_t__ chip_id; int ports; scalar_t__ chip_rev; int st_size; int st_dma; scalar_t__ st_idx; int /*<<< orphan*/  st_le; struct pci_dev* pdev; } ;
struct pci_dev {scalar_t__ pcie_cap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ B0_CTST ; 
 scalar_t__ B0_HWE_IMSK ; 
 int /*<<< orphan*/  B0_HWE_ISRC ; 
 scalar_t__ B28_DPT_CTRL ; 
 scalar_t__ B28_Y2_ASF_STAT_CMD ; 
 scalar_t__ B2_I2C_IRQ ; 
 scalar_t__ B2_TI_CTRL ; 
 scalar_t__ B2_TST_CTRL1 ; 
 int /*<<< orphan*/  B3_RI_CTRL ; 
 int /*<<< orphan*/  B3_RI_RTO_R1 ; 
 int /*<<< orphan*/  B3_RI_RTO_R2 ; 
 int /*<<< orphan*/  B3_RI_RTO_XA1 ; 
 int /*<<< orphan*/  B3_RI_RTO_XA2 ; 
 int /*<<< orphan*/  B3_RI_RTO_XS1 ; 
 int /*<<< orphan*/  B3_RI_RTO_XS2 ; 
 int /*<<< orphan*/  B3_RI_WTO_R1 ; 
 int /*<<< orphan*/  B3_RI_WTO_R2 ; 
 int /*<<< orphan*/  B3_RI_WTO_XA1 ; 
 int /*<<< orphan*/  B3_RI_WTO_XA2 ; 
 int /*<<< orphan*/  B3_RI_WTO_XS1 ; 
 int /*<<< orphan*/  B3_RI_WTO_XS2 ; 
 scalar_t__ CHIP_ID_YUKON_EX ; 
 scalar_t__ CHIP_ID_YUKON_OPT ; 
 scalar_t__ CHIP_ID_YUKON_OP_2 ; 
 scalar_t__ CHIP_ID_YUKON_PRM ; 
 scalar_t__ CHIP_ID_YUKON_SUPR ; 
 scalar_t__ CHIP_ID_YUKON_XL ; 
 scalar_t__ CHIP_REV_YU_PRM_A0 ; 
 scalar_t__ CHIP_REV_YU_SU_B0 ; 
 scalar_t__ CPU_WDOG ; 
 int CS_MRST_CLR ; 
 int CS_RST_CLR ; 
 int CS_RST_SET ; 
 int DPT_STOP ; 
 int /*<<< orphan*/  GMAC_CTRL ; 
 int /*<<< orphan*/  GMAC_LINK_CTRL ; 
 scalar_t__ GMAC_TI_ST_CTRL ; 
 int GMC_BYP_MACSECRX_ON ; 
 int GMC_BYP_MACSECTX_ON ; 
 int GMC_BYP_RETR_ON ; 
 int GMLC_RST_CLR ; 
 int GMLC_RST_SET ; 
 int GMT_ST_CLR_IRQ ; 
 int GMT_ST_STOP ; 
 int GPC_INTPOL ; 
 scalar_t__ GPHY_CTRL ; 
 scalar_t__ HCU_CCSR ; 
 int HCU_CCSR_AHB_RST ; 
 int HCU_CCSR_CPU_CLK_DIVIDE_MSK ; 
 int HCU_CCSR_CPU_RST_MODE ; 
 int HCU_CCSR_UC_STATE_MSK ; 
 int /*<<< orphan*/  PCI_DEV_REG3 ; 
 scalar_t__ PCI_ERR_UNCOR_STATUS ; 
 scalar_t__ PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_ASPMC ; 
 scalar_t__ PCI_LDO_CTRL ; 
 scalar_t__ PCI_STATUS ; 
 int PCI_STATUS_ERROR_BITS ; 
 int PEX_DB_ACCESS ; 
 int PHY_M_UNDOC1 ; 
 scalar_t__ PSM_CONFIG_REG3 ; 
 scalar_t__ PSM_CONFIG_REG4 ; 
 int PSM_CONFIG_REG4_RST_PHY_LINK_DETECT ; 
 int PSM_CONFIG_REG4_TIMER_PHY_LINK_DETECT_BASE ; 
 int /*<<< orphan*/  P_CLK_MACSEC_DIS ; 
 scalar_t__ RAM_BUFFER (int,int /*<<< orphan*/ ) ; 
 int RI_RST_CLR ; 
 int SC_STAT_OP_ON ; 
 int SC_STAT_RST_CLR ; 
 int SC_STAT_RST_SET ; 
 scalar_t__ SK_REG (int,int /*<<< orphan*/ ) ; 
 int SK_RI_TO_53 ; 
 scalar_t__ STAT_CTRL ; 
 scalar_t__ STAT_FIFO_ISR_WM ; 
 scalar_t__ STAT_FIFO_WM ; 
 scalar_t__ STAT_ISR_TIMER_CTRL ; 
 scalar_t__ STAT_ISR_TIMER_INI ; 
 scalar_t__ STAT_LAST_IDX ; 
 scalar_t__ STAT_LEV_TIMER_CTRL ; 
 scalar_t__ STAT_LEV_TIMER_INI ; 
 scalar_t__ STAT_LIST_ADDR_HI ; 
 scalar_t__ STAT_LIST_ADDR_LO ; 
 scalar_t__ STAT_TX_IDX_TH ; 
 scalar_t__ STAT_TX_TIMER_CTRL ; 
 scalar_t__ STAT_TX_TIMER_INI ; 
 int TIM_CLR_IRQ ; 
 int TIM_START ; 
 int TIM_STOP ; 
 int TST_CFG_WRITE_OFF ; 
 int TST_CFG_WRITE_ON ; 
 int /*<<< orphan*/  TXA_CTRL ; 
 int TXA_ENA_ARB ; 
 int Y2_ASF_DISABLE ; 
 int Y2_ASF_RESET ; 
 scalar_t__ Y2_CFG_AER ; 
 scalar_t__ Y2_CFG_SPC ; 
 int Y2_HWE_ALL_MASK ; 
 int Y2_IS_PCI_EXP ; 
 scalar_t__ Y2_PEX_PHY_DATA ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  sky2_gmac_reset (struct sky2_hw*,int) ; 
 int sky2_pci_read16 (struct sky2_hw*,scalar_t__) ; 
 int /*<<< orphan*/  sky2_pci_write16 (struct sky2_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  sky2_pci_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_power_on (struct sky2_hw*) ; 
 int sky2_read16 (struct sky2_hw*,scalar_t__) ; 
 int sky2_read32 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int sky2_us2clk (struct sky2_hw*,int) ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,scalar_t__,int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,scalar_t__,int) ; 

__attribute__((used)) static void sky2_reset(struct sky2_hw *hw)
{
	struct pci_dev *pdev = hw->pdev;
	u16 status;
	int i;
	u32 hwe_mask = Y2_HWE_ALL_MASK;

	/* disable ASF */
	if (hw->chip_id == CHIP_ID_YUKON_EX
	    || hw->chip_id == CHIP_ID_YUKON_SUPR) {
		sky2_write32(hw, CPU_WDOG, 0);
		status = sky2_read16(hw, HCU_CCSR);
		status &= ~(HCU_CCSR_AHB_RST | HCU_CCSR_CPU_RST_MODE |
			    HCU_CCSR_UC_STATE_MSK);
		/*
		 * CPU clock divider shouldn't be used because
		 * - ASF firmware may malfunction
		 * - Yukon-Supreme: Parallel FLASH doesn't support divided clocks
		 */
		status &= ~HCU_CCSR_CPU_CLK_DIVIDE_MSK;
		sky2_write16(hw, HCU_CCSR, status);
		sky2_write32(hw, CPU_WDOG, 0);
	} else
		sky2_write8(hw, B28_Y2_ASF_STAT_CMD, Y2_ASF_RESET);
	sky2_write16(hw, B0_CTST, Y2_ASF_DISABLE);

	/* do a SW reset */
	sky2_write8(hw, B0_CTST, CS_RST_SET);
	sky2_write8(hw, B0_CTST, CS_RST_CLR);

	/* allow writes to PCI config */
	sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);

	/* clear PCI errors, if any */
	status = sky2_pci_read16(hw, PCI_STATUS);
	status |= PCI_STATUS_ERROR_BITS;
	sky2_pci_write16(hw, PCI_STATUS, status);

	sky2_write8(hw, B0_CTST, CS_MRST_CLR);

	if (pci_is_pcie(pdev)) {
		sky2_write32(hw, Y2_CFG_AER + PCI_ERR_UNCOR_STATUS,
			     0xfffffffful);

		/* If error bit is stuck on ignore it */
		if (sky2_read32(hw, B0_HWE_ISRC) & Y2_IS_PCI_EXP)
			dev_info(&pdev->dev, "ignoring stuck error report bit\n");
		else
			hwe_mask |= Y2_IS_PCI_EXP;
	}

	sky2_power_on(hw);
	sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

	for (i = 0; i < hw->ports; i++) {
		sky2_write8(hw, SK_REG(i, GMAC_LINK_CTRL), GMLC_RST_SET);
		sky2_write8(hw, SK_REG(i, GMAC_LINK_CTRL), GMLC_RST_CLR);

		if (hw->chip_id == CHIP_ID_YUKON_EX ||
		    hw->chip_id == CHIP_ID_YUKON_SUPR)
			sky2_write16(hw, SK_REG(i, GMAC_CTRL),
				     GMC_BYP_MACSECRX_ON | GMC_BYP_MACSECTX_ON
				     | GMC_BYP_RETR_ON);

	}

	if (hw->chip_id == CHIP_ID_YUKON_SUPR && hw->chip_rev > CHIP_REV_YU_SU_B0) {
		/* enable MACSec clock gating */
		sky2_pci_write32(hw, PCI_DEV_REG3, P_CLK_MACSEC_DIS);
	}

	if (hw->chip_id == CHIP_ID_YUKON_OPT ||
	    hw->chip_id == CHIP_ID_YUKON_PRM ||
	    hw->chip_id == CHIP_ID_YUKON_OP_2) {
		u16 reg;

		if (hw->chip_id == CHIP_ID_YUKON_OPT && hw->chip_rev == 0) {
			/* disable PCI-E PHY power down (set PHY reg 0x80, bit 7 */
			sky2_write32(hw, Y2_PEX_PHY_DATA, (0x80UL << 16) | (1 << 7));

			/* set PHY Link Detect Timer to 1.1 second (11x 100ms) */
			reg = 10;

			/* re-enable PEX PM in PEX PHY debug reg. 8 (clear bit 12) */
			sky2_write32(hw, Y2_PEX_PHY_DATA, PEX_DB_ACCESS | (0x08UL << 16));
		} else {
			/* set PHY Link Detect Timer to 0.4 second (4x 100ms) */
			reg = 3;
		}

		reg <<= PSM_CONFIG_REG4_TIMER_PHY_LINK_DETECT_BASE;
		reg |= PSM_CONFIG_REG4_RST_PHY_LINK_DETECT;

		/* reset PHY Link Detect */
		sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_ON);
		sky2_pci_write16(hw, PSM_CONFIG_REG4, reg);

		/* check if PSMv2 was running before */
		reg = sky2_pci_read16(hw, PSM_CONFIG_REG3);
		if (reg & PCI_EXP_LNKCTL_ASPMC)
			/* restore the PCIe Link Control register */
			sky2_pci_write16(hw, pdev->pcie_cap + PCI_EXP_LNKCTL,
					 reg);

		if (hw->chip_id == CHIP_ID_YUKON_PRM &&
			hw->chip_rev == CHIP_REV_YU_PRM_A0) {
			/* change PHY Interrupt polarity to low active */
			reg = sky2_read16(hw, GPHY_CTRL);
			sky2_write16(hw, GPHY_CTRL, reg | GPC_INTPOL);

			/* adapt HW for low active PHY Interrupt */
			reg = sky2_read16(hw, Y2_CFG_SPC + PCI_LDO_CTRL);
			sky2_write16(hw, Y2_CFG_SPC + PCI_LDO_CTRL, reg | PHY_M_UNDOC1);
		}

		sky2_write8(hw, B2_TST_CTRL1, TST_CFG_WRITE_OFF);

		/* re-enable PEX PM in PEX PHY debug reg. 8 (clear bit 12) */
		sky2_write32(hw, Y2_PEX_PHY_DATA, PEX_DB_ACCESS | (0x08UL << 16));
	}

	/* Clear I2C IRQ noise */
	sky2_write32(hw, B2_I2C_IRQ, 1);

	/* turn off hardware timer (unused) */
	sky2_write8(hw, B2_TI_CTRL, TIM_STOP);
	sky2_write8(hw, B2_TI_CTRL, TIM_CLR_IRQ);

	/* Turn off descriptor polling */
	sky2_write32(hw, B28_DPT_CTRL, DPT_STOP);

	/* Turn off receive timestamp */
	sky2_write8(hw, GMAC_TI_ST_CTRL, GMT_ST_STOP);
	sky2_write8(hw, GMAC_TI_ST_CTRL, GMT_ST_CLR_IRQ);

	/* enable the Tx Arbiters */
	for (i = 0; i < hw->ports; i++)
		sky2_write8(hw, SK_REG(i, TXA_CTRL), TXA_ENA_ARB);

	/* Initialize ram interface */
	for (i = 0; i < hw->ports; i++) {
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_CTRL), RI_RST_CLR);

		sky2_write8(hw, RAM_BUFFER(i, B3_RI_WTO_R1), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_WTO_XA1), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_WTO_XS1), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_RTO_R1), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_RTO_XA1), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_RTO_XS1), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_WTO_R2), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_WTO_XA2), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_WTO_XS2), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_RTO_R2), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_RTO_XA2), SK_RI_TO_53);
		sky2_write8(hw, RAM_BUFFER(i, B3_RI_RTO_XS2), SK_RI_TO_53);
	}

	sky2_write32(hw, B0_HWE_IMSK, hwe_mask);

	for (i = 0; i < hw->ports; i++)
		sky2_gmac_reset(hw, i);

	memset(hw->st_le, 0, hw->st_size * sizeof(struct sky2_status_le));
	hw->st_idx = 0;

	sky2_write32(hw, STAT_CTRL, SC_STAT_RST_SET);
	sky2_write32(hw, STAT_CTRL, SC_STAT_RST_CLR);

	sky2_write32(hw, STAT_LIST_ADDR_LO, hw->st_dma);
	sky2_write32(hw, STAT_LIST_ADDR_HI, (u64) hw->st_dma >> 32);

	/* Set the list last index */
	sky2_write16(hw, STAT_LAST_IDX, hw->st_size - 1);

	sky2_write16(hw, STAT_TX_IDX_TH, 10);
	sky2_write8(hw, STAT_FIFO_WM, 16);

	/* set Status-FIFO ISR watermark */
	if (hw->chip_id == CHIP_ID_YUKON_XL && hw->chip_rev == 0)
		sky2_write8(hw, STAT_FIFO_ISR_WM, 4);
	else
		sky2_write8(hw, STAT_FIFO_ISR_WM, 16);

	sky2_write32(hw, STAT_TX_TIMER_INI, sky2_us2clk(hw, 1000));
	sky2_write32(hw, STAT_ISR_TIMER_INI, sky2_us2clk(hw, 20));
	sky2_write32(hw, STAT_LEV_TIMER_INI, sky2_us2clk(hw, 100));

	/* enable status unit */
	sky2_write32(hw, STAT_CTRL, SC_STAT_OP_ON);

	sky2_write8(hw, STAT_TX_TIMER_CTRL, TIM_START);
	sky2_write8(hw, STAT_LEV_TIMER_CTRL, TIM_START);
	sky2_write8(hw, STAT_ISR_TIMER_CTRL, TIM_START);
}