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
struct xenon_priv {int /*<<< orphan*/  init_card_type; struct xenon_emmc_phy_regs* emmc_phy_regs; struct xenon_emmc_phy_params* phy_params; } ;
struct xenon_emmc_phy_regs {int /*<<< orphan*/  timing_adj; } ;
struct xenon_emmc_phy_params {int /*<<< orphan*/  slow_mode; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {scalar_t__ clock; } ;

/* Variables and functions */
 scalar_t__ MMC_HIGH_52_MAX_DTR ; 
#define  MMC_TIMING_LEGACY 132 
#define  MMC_TIMING_MMC_HS 131 
#define  MMC_TIMING_SD_HS 130 
#define  MMC_TIMING_UHS_SDR12 129 
#define  MMC_TIMING_UHS_SDR25 128 
 int /*<<< orphan*/  MMC_TYPE_SDIO ; 
 int /*<<< orphan*/  XENON_TIMING_ADJUST_SLOW_MODE ; 
 struct xenon_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool xenon_emmc_phy_slow_mode(struct sdhci_host *host,
				     unsigned char timing)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	struct xenon_emmc_phy_params *params = priv->phy_params;
	struct xenon_emmc_phy_regs *phy_regs = priv->emmc_phy_regs;
	u32 reg;
	int ret;

	if (host->clock > MMC_HIGH_52_MAX_DTR)
		return false;

	reg = sdhci_readl(host, phy_regs->timing_adj);
	/* When in slower SDR mode, enable Slow Mode for SDIO
	 * or when Slow Mode flag is set
	 */
	switch (timing) {
	case MMC_TIMING_LEGACY:
		/*
		 * If Slow Mode is required, enable Slow Mode by default
		 * in early init phase to avoid any potential issue.
		 */
		if (params->slow_mode) {
			reg |= XENON_TIMING_ADJUST_SLOW_MODE;
			ret = true;
		} else {
			reg &= ~XENON_TIMING_ADJUST_SLOW_MODE;
			ret = false;
		}
		break;
	case MMC_TIMING_UHS_SDR25:
	case MMC_TIMING_UHS_SDR12:
	case MMC_TIMING_SD_HS:
	case MMC_TIMING_MMC_HS:
		if ((priv->init_card_type == MMC_TYPE_SDIO) ||
		    params->slow_mode) {
			reg |= XENON_TIMING_ADJUST_SLOW_MODE;
			ret = true;
			break;
		}
		/* fall through */
	default:
		reg &= ~XENON_TIMING_ADJUST_SLOW_MODE;
		ret = false;
	}

	sdhci_writel(host, reg, phy_regs->timing_adj);
	return ret;
}