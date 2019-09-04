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
struct mmc_ios {scalar_t__ timing; } ;
struct hi3798cv200_priv {int /*<<< orphan*/  drive_clk; } ;
struct dw_mci {struct hi3798cv200_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDR_REG ; 
 int /*<<< orphan*/  ENABLE_SHIFT ; 
 scalar_t__ MMC_TIMING_LEGACY ; 
 scalar_t__ MMC_TIMING_MMC_DDR52 ; 
 scalar_t__ MMC_TIMING_MMC_HS ; 
 scalar_t__ MMC_TIMING_MMC_HS200 ; 
 scalar_t__ MMC_TIMING_MMC_HS400 ; 
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 int /*<<< orphan*/  SDMMC_DDR_HS400 ; 
 int /*<<< orphan*/  SDMMC_ENABLE_PHASE ; 
 int /*<<< orphan*/  SDMMC_UHS_DDR ; 
 int /*<<< orphan*/  UHS_REG ; 
 int /*<<< orphan*/  clk_set_phase (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mci_readl (struct dw_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct dw_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dw_mci_hi3798cv200_set_ios(struct dw_mci *host, struct mmc_ios *ios)
{
	struct hi3798cv200_priv *priv = host->priv;
	u32 val;

	val = mci_readl(host, UHS_REG);
	if (ios->timing == MMC_TIMING_MMC_DDR52 ||
	    ios->timing == MMC_TIMING_UHS_DDR50)
		val |= SDMMC_UHS_DDR;
	else
		val &= ~SDMMC_UHS_DDR;
	mci_writel(host, UHS_REG, val);

	val = mci_readl(host, ENABLE_SHIFT);
	if (ios->timing == MMC_TIMING_MMC_DDR52)
		val |= SDMMC_ENABLE_PHASE;
	else
		val &= ~SDMMC_ENABLE_PHASE;
	mci_writel(host, ENABLE_SHIFT, val);

	val = mci_readl(host, DDR_REG);
	if (ios->timing == MMC_TIMING_MMC_HS400)
		val |= SDMMC_DDR_HS400;
	else
		val &= ~SDMMC_DDR_HS400;
	mci_writel(host, DDR_REG, val);

	if (ios->timing == MMC_TIMING_MMC_HS ||
	    ios->timing == MMC_TIMING_LEGACY)
		clk_set_phase(priv->drive_clk, 180);
	else if (ios->timing == MMC_TIMING_MMC_HS200)
		clk_set_phase(priv->drive_clk, 135);
}