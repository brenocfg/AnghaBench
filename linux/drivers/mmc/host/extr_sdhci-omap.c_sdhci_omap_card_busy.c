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
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_omap_host {int dummy; } ;
struct sdhci_host {int ier; int /*<<< orphan*/  irq; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int AC12_V1V8_SIGEN ; 
 int CON_CLKEXTFREE ; 
 int CON_PADEN ; 
 int PSTATE_DATI ; 
 int PSTATE_DLEV_DAT0 ; 
 int SDHCI_INT_CARD_INT ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_OMAP_AC12 ; 
 int /*<<< orphan*/  SDHCI_OMAP_CON ; 
 int /*<<< orphan*/  SDHCI_OMAP_PSTATE ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int sdhci_omap_readl (struct sdhci_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_omap_writel (struct sdhci_omap_host*,int /*<<< orphan*/ ,int) ; 
 struct sdhci_omap_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sdhci_omap_card_busy(struct mmc_host *mmc)
{
	u32 reg, ac12;
	int ret = false;
	struct sdhci_host *host = mmc_priv(mmc);
	struct sdhci_pltfm_host *pltfm_host;
	struct sdhci_omap_host *omap_host;
	u32 ier = host->ier;

	pltfm_host = sdhci_priv(host);
	omap_host = sdhci_pltfm_priv(pltfm_host);

	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_CON);
	ac12 = sdhci_omap_readl(omap_host, SDHCI_OMAP_AC12);
	reg &= ~CON_CLKEXTFREE;
	if (ac12 & AC12_V1V8_SIGEN)
		reg |= CON_CLKEXTFREE;
	reg |= CON_PADEN;
	sdhci_omap_writel(omap_host, SDHCI_OMAP_CON, reg);

	disable_irq(host->irq);
	ier |= SDHCI_INT_CARD_INT;
	sdhci_writel(host, ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, ier, SDHCI_SIGNAL_ENABLE);

	/*
	 * Delay is required for PSTATE to correctly reflect
	 * DLEV/CLEV values after PADEN is set.
	 */
	usleep_range(50, 100);
	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_PSTATE);
	if ((reg & PSTATE_DATI) || !(reg & PSTATE_DLEV_DAT0))
		ret = true;

	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_CON);
	reg &= ~(CON_CLKEXTFREE | CON_PADEN);
	sdhci_omap_writel(omap_host, SDHCI_OMAP_CON, reg);

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
	enable_irq(host->irq);

	return ret;
}