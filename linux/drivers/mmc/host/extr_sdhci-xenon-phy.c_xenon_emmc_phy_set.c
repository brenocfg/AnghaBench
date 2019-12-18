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
struct xenon_priv {scalar_t__ phy_type; scalar_t__ init_card_type; struct xenon_emmc_phy_regs* emmc_phy_regs; struct xenon_emmc_phy_params* phy_params; } ;
struct xenon_emmc_phy_regs {int logic_timing_val; int /*<<< orphan*/  logic_timing_adj; int /*<<< orphan*/  func_ctrl; int /*<<< orphan*/  pad_ctrl2; int /*<<< orphan*/  timing_adj; int /*<<< orphan*/  pad_ctrl; } ;
struct xenon_emmc_phy_params {int znr; int zpr; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 scalar_t__ EMMC_5_0_PHY ; 
 unsigned char MMC_TIMING_LEGACY ; 
#define  MMC_TIMING_MMC_DDR52 130 
#define  MMC_TIMING_MMC_HS400 129 
#define  MMC_TIMING_UHS_DDR50 128 
 scalar_t__ MMC_TYPE_SDIO ; 
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int XENON_CMD_DDR_MODE ; 
 int XENON_DQ_ASYNC_MODE ; 
 int XENON_DQ_DDR_MODE_MASK ; 
 int XENON_DQ_DDR_MODE_SHIFT ; 
 int XENON_EMMC5_1_FC_CMD_PD ; 
 int XENON_EMMC5_1_FC_CMD_PU ; 
 int XENON_EMMC5_1_FC_DQ_PD ; 
 int XENON_EMMC5_1_FC_DQ_PU ; 
 int XENON_EMMC5_FC_CMD_PD ; 
 int XENON_EMMC5_FC_CMD_PU ; 
 int XENON_EMMC5_FC_DQ_PD ; 
 int XENON_EMMC5_FC_DQ_PU ; 
 int /*<<< orphan*/  XENON_EMMC_5_0_PHY_PAD_CONTROL ; 
 int /*<<< orphan*/  XENON_EMMC_PHY_PAD_CONTROL1 ; 
 int XENON_FC_ALL_CMOS_RECEIVER ; 
 int XENON_FC_CMD_RECEN ; 
 int XENON_FC_DQ_RECEN ; 
 int XENON_FC_QSP_RECEN ; 
 int XENON_OEN_QSN ; 
 int XENON_TIMING_ADJUST_SDIO_MODE ; 
 int XENON_ZNR_MASK ; 
 int XENON_ZNR_SHIFT ; 
 int XENON_ZPR_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct xenon_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenon_emmc_phy_disable_strobe (struct sdhci_host*) ; 
 int /*<<< orphan*/  xenon_emmc_phy_init (struct sdhci_host*) ; 
 scalar_t__ xenon_emmc_phy_slow_mode (struct sdhci_host*,unsigned char) ; 

__attribute__((used)) static void xenon_emmc_phy_set(struct sdhci_host *host,
			       unsigned char timing)
{
	u32 reg;
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	struct xenon_emmc_phy_params *params = priv->phy_params;
	struct xenon_emmc_phy_regs *phy_regs = priv->emmc_phy_regs;

	dev_dbg(mmc_dev(host->mmc), "eMMC PHY setting starts\n");

	/* Setup pad, set bit[28] and bits[26:24] */
	reg = sdhci_readl(host, phy_regs->pad_ctrl);
	reg |= (XENON_FC_DQ_RECEN | XENON_FC_CMD_RECEN |
		XENON_FC_QSP_RECEN | XENON_OEN_QSN);
	/* All FC_XX_RECEIVCE should be set as CMOS Type */
	reg |= XENON_FC_ALL_CMOS_RECEIVER;
	sdhci_writel(host, reg, phy_regs->pad_ctrl);

	/* Set CMD and DQ Pull Up */
	if (priv->phy_type == EMMC_5_0_PHY) {
		reg = sdhci_readl(host, XENON_EMMC_5_0_PHY_PAD_CONTROL);
		reg |= (XENON_EMMC5_FC_CMD_PU | XENON_EMMC5_FC_DQ_PU);
		reg &= ~(XENON_EMMC5_FC_CMD_PD | XENON_EMMC5_FC_DQ_PD);
		sdhci_writel(host, reg, XENON_EMMC_5_0_PHY_PAD_CONTROL);
	} else {
		reg = sdhci_readl(host, XENON_EMMC_PHY_PAD_CONTROL1);
		reg |= (XENON_EMMC5_1_FC_CMD_PU | XENON_EMMC5_1_FC_DQ_PU);
		reg &= ~(XENON_EMMC5_1_FC_CMD_PD | XENON_EMMC5_1_FC_DQ_PD);
		sdhci_writel(host, reg, XENON_EMMC_PHY_PAD_CONTROL1);
	}

	if (timing == MMC_TIMING_LEGACY) {
		xenon_emmc_phy_slow_mode(host, timing);
		goto phy_init;
	}

	/*
	 * If SDIO card, set SDIO Mode
	 * Otherwise, clear SDIO Mode
	 */
	reg = sdhci_readl(host, phy_regs->timing_adj);
	if (priv->init_card_type == MMC_TYPE_SDIO)
		reg |= XENON_TIMING_ADJUST_SDIO_MODE;
	else
		reg &= ~XENON_TIMING_ADJUST_SDIO_MODE;
	sdhci_writel(host, reg, phy_regs->timing_adj);

	if (xenon_emmc_phy_slow_mode(host, timing))
		goto phy_init;

	/*
	 * Set preferred ZNR and ZPR value
	 * The ZNR and ZPR value vary between different boards.
	 * Define them both in sdhci-xenon-emmc-phy.h.
	 */
	reg = sdhci_readl(host, phy_regs->pad_ctrl2);
	reg &= ~((XENON_ZNR_MASK << XENON_ZNR_SHIFT) | XENON_ZPR_MASK);
	reg |= ((params->znr << XENON_ZNR_SHIFT) | params->zpr);
	sdhci_writel(host, reg, phy_regs->pad_ctrl2);

	/*
	 * When setting EMMC_PHY_FUNC_CONTROL register,
	 * SD clock should be disabled
	 */
	reg = sdhci_readl(host, SDHCI_CLOCK_CONTROL);
	reg &= ~SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, reg, SDHCI_CLOCK_CONTROL);

	reg = sdhci_readl(host, phy_regs->func_ctrl);
	switch (timing) {
	case MMC_TIMING_MMC_HS400:
		reg |= (XENON_DQ_DDR_MODE_MASK << XENON_DQ_DDR_MODE_SHIFT) |
		       XENON_CMD_DDR_MODE;
		reg &= ~XENON_DQ_ASYNC_MODE;
		break;
	case MMC_TIMING_UHS_DDR50:
	case MMC_TIMING_MMC_DDR52:
		reg |= (XENON_DQ_DDR_MODE_MASK << XENON_DQ_DDR_MODE_SHIFT) |
		       XENON_CMD_DDR_MODE | XENON_DQ_ASYNC_MODE;
		break;
	default:
		reg &= ~((XENON_DQ_DDR_MODE_MASK << XENON_DQ_DDR_MODE_SHIFT) |
			 XENON_CMD_DDR_MODE);
		reg |= XENON_DQ_ASYNC_MODE;
	}
	sdhci_writel(host, reg, phy_regs->func_ctrl);

	/* Enable bus clock */
	reg = sdhci_readl(host, SDHCI_CLOCK_CONTROL);
	reg |= SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, reg, SDHCI_CLOCK_CONTROL);

	if (timing == MMC_TIMING_MMC_HS400)
		/* Hardware team recommend a value for HS400 */
		sdhci_writel(host, phy_regs->logic_timing_val,
			     phy_regs->logic_timing_adj);
	else
		xenon_emmc_phy_disable_strobe(host);

phy_init:
	xenon_emmc_phy_init(host);

	dev_dbg(mmc_dev(host->mmc), "eMMC PHY setting completes\n");
}