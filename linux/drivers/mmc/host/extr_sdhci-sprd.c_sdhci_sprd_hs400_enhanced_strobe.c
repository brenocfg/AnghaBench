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
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_sprd_host {int /*<<< orphan*/ * phy_delay; } ;
struct sdhci_host {int dummy; } ;
struct mmc_ios {int /*<<< orphan*/  enhanced_strobe; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int MMC_TIMING_MMC_HS400 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_MASK ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int /*<<< orphan*/  SDHCI_SPRD_CTRL_HS400ES ; 
 int /*<<< orphan*/  SDHCI_SPRD_REG_32_DLL_DLY ; 
 struct sdhci_sprd_host* TO_SPRD_HOST (struct sdhci_host*) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_sprd_sd_clk_off (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_sprd_sd_clk_on (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_sprd_hs400_enhanced_strobe(struct mmc_host *mmc,
					     struct mmc_ios *ios)
{
	struct sdhci_host *host = mmc_priv(mmc);
	struct sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);
	u32 *p = sprd_host->phy_delay;
	u16 ctrl_2;

	if (!ios->enhanced_strobe)
		return;

	sdhci_sprd_sd_clk_off(host);

	/* Set HS400 enhanced strobe mode */
	ctrl_2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	ctrl_2 |= SDHCI_SPRD_CTRL_HS400ES;
	sdhci_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);

	sdhci_sprd_sd_clk_on(host);

	/* Set the PHY DLL delay value for HS400 enhanced strobe mode */
	sdhci_writel(host, p[MMC_TIMING_MMC_HS400 + 1],
		     SDHCI_SPRD_REG_32_DLL_DLY);
}