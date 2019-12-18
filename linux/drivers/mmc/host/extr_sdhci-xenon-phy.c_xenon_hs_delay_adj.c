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
struct sdhci_host {scalar_t__ clock; int timing; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MMC_TIMING_MMC_DDR52 132 
#define  MMC_TIMING_MMC_HS200 131 
#define  MMC_TIMING_MMC_HS400 130 
#define  MMC_TIMING_UHS_DDR50 129 
#define  MMC_TIMING_UHS_SDR104 128 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ XENON_DEFAULT_SDCLK_FREQ ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int xenon_emmc_phy_config_tuning (struct sdhci_host*) ; 
 int /*<<< orphan*/  xenon_emmc_phy_strobe_delay_adj (struct sdhci_host*) ; 

__attribute__((used)) static int xenon_hs_delay_adj(struct sdhci_host *host)
{
	int ret = 0;

	if (WARN_ON(host->clock <= XENON_DEFAULT_SDCLK_FREQ))
		return -EINVAL;

	switch (host->timing) {
	case MMC_TIMING_MMC_HS400:
		xenon_emmc_phy_strobe_delay_adj(host);
		return 0;
	case MMC_TIMING_MMC_HS200:
	case MMC_TIMING_UHS_SDR104:
		return xenon_emmc_phy_config_tuning(host);
	case MMC_TIMING_MMC_DDR52:
	case MMC_TIMING_UHS_DDR50:
		/*
		 * DDR Mode requires driver to scan Sampling Fixed Delay Line,
		 * to find out a perfect operation sampling point.
		 * It is hard to implement such a scan in host driver
		 * since initiating commands by host driver is not safe.
		 * Thus so far just keep PHY Sampling Fixed Delay in
		 * default value of DDR mode.
		 *
		 * If any timing issue occurs in DDR mode on Marvell products,
		 * please contact maintainer for internal support in Marvell.
		 */
		dev_warn_once(mmc_dev(host->mmc), "Timing issue might occur in DDR mode\n");
		return 0;
	}

	return ret;
}