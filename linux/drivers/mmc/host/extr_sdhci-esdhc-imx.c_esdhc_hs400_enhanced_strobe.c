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
struct sdhci_host {scalar_t__ ioaddr; } ;
struct mmc_ios {scalar_t__ enhanced_strobe; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ ESDHC_MIX_CTRL ; 
 int /*<<< orphan*/  ESDHC_MIX_CTRL_HS400_ES_EN ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void esdhc_hs400_enhanced_strobe(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct sdhci_host *host = mmc_priv(mmc);
	u32 m;

	m = readl(host->ioaddr + ESDHC_MIX_CTRL);
	if (ios->enhanced_strobe)
		m |= ESDHC_MIX_CTRL_HS400_ES_EN;
	else
		m &= ~ESDHC_MIX_CTRL_HS400_ES_EN;
	writel(m, host->ioaddr + ESDHC_MIX_CTRL);
}