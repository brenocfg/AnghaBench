#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tegra_ahci_priv {scalar_t__ sata_regs; TYPE_3__* soc; TYPE_1__* pdev; } ;
struct ahci_host_priv {struct tegra_ahci_priv* plat_data; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* init ) (struct ahci_host_priv*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SATA_CONFIGURATION_0 ; 
 int SATA_CONFIGURATION_0_CLK_OVERRIDE ; 
 int SATA_CONFIGURATION_0_EN_FPCI ; 
 scalar_t__ SATA_FPCI_BAR5 ; 
 int SATA_FPCI_BAR5_ACCESS_TYPE ; 
 int SATA_FPCI_BAR5_START ; 
 int SATA_FPCI_BAR5_START_MASK ; 
 scalar_t__ SATA_INTR_MASK ; 
 int SATA_INTR_MASK_IP_INT_MASK ; 
 scalar_t__ SCFG_OFFSET ; 
 scalar_t__ T_SATA0_AHCI_HBA_CAP_BKDR ; 
 int T_SATA0_AHCI_HBA_CAP_BKDR_PARTIAL_ST_CAP ; 
 int T_SATA0_AHCI_HBA_CAP_BKDR_SALP ; 
 int T_SATA0_AHCI_HBA_CAP_BKDR_SLUMBER_ST_CAP ; 
 int T_SATA0_AHCI_HBA_CAP_BKDR_SUPP_PM ; 
 scalar_t__ T_SATA0_AHCI_IDP1 ; 
 int T_SATA0_AHCI_IDP1_DATA ; 
 scalar_t__ T_SATA0_BKDOOR_CC ; 
 int T_SATA0_BKDOOR_CC_CLASS_CODE ; 
 int T_SATA0_BKDOOR_CC_CLASS_CODE_MASK ; 
 int T_SATA0_BKDOOR_CC_PROG_IF ; 
 int T_SATA0_BKDOOR_CC_PROG_IF_MASK ; 
 scalar_t__ T_SATA0_CFG2NVOOB_2 ; 
 int T_SATA0_CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW ; 
 int T_SATA0_CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW_MASK ; 
 scalar_t__ T_SATA0_CFG_1 ; 
 int T_SATA0_CFG_1_BUS_MASTER ; 
 int T_SATA0_CFG_1_IO_SPACE ; 
 int T_SATA0_CFG_1_MEMORY_SPACE ; 
 int T_SATA0_CFG_1_SERR ; 
 scalar_t__ T_SATA0_CFG_35 ; 
 int T_SATA0_CFG_35_IDP_INDEX ; 
 int T_SATA0_CFG_35_IDP_INDEX_MASK ; 
 scalar_t__ T_SATA0_CFG_9 ; 
 int T_SATA0_CFG_9_BASE_ADDRESS ; 
 scalar_t__ T_SATA0_CFG_PHY_1 ; 
 int T_SATA0_CFG_PHY_1_PADS_IDDQ_EN ; 
 int T_SATA0_CFG_PHY_1_PAD_PLL_IDDQ_EN ; 
 scalar_t__ T_SATA0_CFG_SATA ; 
 int T_SATA0_CFG_SATA_BACKDOOR_PROG_IF_EN ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL17_0 ; 
 int T_SATA0_CHX_PHY_CTRL17_0_RX_EQ_CTRL_L_GEN1 ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL18_0 ; 
 int T_SATA0_CHX_PHY_CTRL18_0_RX_EQ_CTRL_L_GEN2 ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL20_0 ; 
 int T_SATA0_CHX_PHY_CTRL20_0_RX_EQ_CTRL_H_GEN1 ; 
 scalar_t__ T_SATA0_CHX_PHY_CTRL21_0 ; 
 int T_SATA0_CHX_PHY_CTRL21_0_RX_EQ_CTRL_H_GEN2 ; 
 scalar_t__ T_SATA0_NVOOB ; 
 int T_SATA0_NVOOB_COMMA_CNT ; 
 int T_SATA0_NVOOB_COMMA_CNT_MASK ; 
 int T_SATA0_NVOOB_SQUELCH_FILTER_LENGTH ; 
 int T_SATA0_NVOOB_SQUELCH_FILTER_LENGTH_MASK ; 
 int T_SATA0_NVOOB_SQUELCH_FILTER_MODE ; 
 int T_SATA0_NVOOB_SQUELCH_FILTER_MODE_MASK ; 
 scalar_t__ T_SATA_CFG_PHY_0 ; 
 int T_SATA_CFG_PHY_0_MASK_SQUELCH ; 
 int T_SATA_CFG_PHY_0_USE_7BIT_ALIGN_DET_FOR_SPD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  tegra_ahci_handle_quirks (struct ahci_host_priv*) ; 
 int tegra_ahci_power_on (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int tegra_ahci_controller_init(struct ahci_host_priv *hpriv)
{
	struct tegra_ahci_priv *tegra = hpriv->plat_data;
	int ret;
	u32 val;

	ret = tegra_ahci_power_on(hpriv);
	if (ret) {
		dev_err(&tegra->pdev->dev,
			"failed to power on AHCI controller: %d\n", ret);
		return ret;
	}

	/*
	 * Program the following SATA IPFS registers to allow SW accesses to
	 * SATA's MMIO register range.
	 */
	val = readl(tegra->sata_regs + SATA_FPCI_BAR5);
	val &= ~(SATA_FPCI_BAR5_START_MASK | SATA_FPCI_BAR5_ACCESS_TYPE);
	val |= SATA_FPCI_BAR5_START | SATA_FPCI_BAR5_ACCESS_TYPE;
	writel(val, tegra->sata_regs + SATA_FPCI_BAR5);

	/* Program the following SATA IPFS register to enable the SATA */
	val = readl(tegra->sata_regs + SATA_CONFIGURATION_0);
	val |= SATA_CONFIGURATION_0_EN_FPCI;
	writel(val, tegra->sata_regs + SATA_CONFIGURATION_0);

	/* Electrical settings for better link stability */
	val = T_SATA0_CHX_PHY_CTRL17_0_RX_EQ_CTRL_L_GEN1;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL17_0);
	val = T_SATA0_CHX_PHY_CTRL18_0_RX_EQ_CTRL_L_GEN2;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL18_0);
	val = T_SATA0_CHX_PHY_CTRL20_0_RX_EQ_CTRL_H_GEN1;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL20_0);
	val = T_SATA0_CHX_PHY_CTRL21_0_RX_EQ_CTRL_H_GEN2;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CHX_PHY_CTRL21_0);

	/* For SQUELCH Filter & Gen3 drive getting detected as Gen1 drive */

	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA_CFG_PHY_0);
	val |= T_SATA_CFG_PHY_0_MASK_SQUELCH;
	val &= ~T_SATA_CFG_PHY_0_USE_7BIT_ALIGN_DET_FOR_SPD;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA_CFG_PHY_0);

	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_NVOOB);
	val &= ~(T_SATA0_NVOOB_COMMA_CNT_MASK |
		 T_SATA0_NVOOB_SQUELCH_FILTER_LENGTH_MASK |
		 T_SATA0_NVOOB_SQUELCH_FILTER_MODE_MASK);
	val |= (T_SATA0_NVOOB_COMMA_CNT |
		T_SATA0_NVOOB_SQUELCH_FILTER_LENGTH |
		T_SATA0_NVOOB_SQUELCH_FILTER_MODE);
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_NVOOB);

	/*
	 * Change CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW from 83.3 ns to 58.8ns
	 */
	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG2NVOOB_2);
	val &= ~T_SATA0_CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW_MASK;
	val |= T_SATA0_CFG2NVOOB_2_COMWAKE_IDLE_CNT_LOW;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG2NVOOB_2);

	if (tegra->soc->ops && tegra->soc->ops->init)
		tegra->soc->ops->init(hpriv);

	/*
	 * Program the following SATA configuration registers to
	 * initialize SATA
	 */
	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_1);
	val |= (T_SATA0_CFG_1_IO_SPACE | T_SATA0_CFG_1_MEMORY_SPACE |
		T_SATA0_CFG_1_BUS_MASTER | T_SATA0_CFG_1_SERR);
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_1);
	val = T_SATA0_CFG_9_BASE_ADDRESS;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_9);

	/* Program Class Code and Programming interface for SATA */
	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_SATA);
	val |= T_SATA0_CFG_SATA_BACKDOOR_PROG_IF_EN;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_SATA);

	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_BKDOOR_CC);
	val &=
	    ~(T_SATA0_BKDOOR_CC_CLASS_CODE_MASK |
	      T_SATA0_BKDOOR_CC_PROG_IF_MASK);
	val |= T_SATA0_BKDOOR_CC_CLASS_CODE | T_SATA0_BKDOOR_CC_PROG_IF;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_BKDOOR_CC);

	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_SATA);
	val &= ~T_SATA0_CFG_SATA_BACKDOOR_PROG_IF_EN;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_SATA);

	/* Enabling LPM capabilities through Backdoor Programming */
	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_AHCI_HBA_CAP_BKDR);
	val |= (T_SATA0_AHCI_HBA_CAP_BKDR_PARTIAL_ST_CAP |
		T_SATA0_AHCI_HBA_CAP_BKDR_SLUMBER_ST_CAP |
		T_SATA0_AHCI_HBA_CAP_BKDR_SALP |
		T_SATA0_AHCI_HBA_CAP_BKDR_SUPP_PM);
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_AHCI_HBA_CAP_BKDR);

	/* SATA Second Level Clock Gating configuration
	 * Enabling Gating of Tx/Rx clocks and driving Pad IDDQ and Lane
	 * IDDQ Signals
	 */
	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_35);
	val &= ~T_SATA0_CFG_35_IDP_INDEX_MASK;
	val |= T_SATA0_CFG_35_IDP_INDEX;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_35);

	val = T_SATA0_AHCI_IDP1_DATA;
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_AHCI_IDP1);

	val = readl(tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_PHY_1);
	val |= (T_SATA0_CFG_PHY_1_PADS_IDDQ_EN |
		T_SATA0_CFG_PHY_1_PAD_PLL_IDDQ_EN);
	writel(val, tegra->sata_regs + SCFG_OFFSET + T_SATA0_CFG_PHY_1);

	/* Enabling IPFS Clock Gating */
	val = readl(tegra->sata_regs + SATA_CONFIGURATION_0);
	val &= ~SATA_CONFIGURATION_0_CLK_OVERRIDE;
	writel(val, tegra->sata_regs + SATA_CONFIGURATION_0);

	tegra_ahci_handle_quirks(hpriv);

	/* Unmask SATA interrupts */

	val = readl(tegra->sata_regs + SATA_INTR_MASK);
	val |= SATA_INTR_MASK_IP_INT_MASK;
	writel(val, tegra->sata_regs + SATA_INTR_MASK);

	return 0;
}