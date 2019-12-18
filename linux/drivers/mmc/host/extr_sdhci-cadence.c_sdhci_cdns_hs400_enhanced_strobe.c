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
typedef  scalar_t__ u32 ;
struct sdhci_host {int dummy; } ;
struct sdhci_cdns_priv {scalar_t__ enhanced_strobe; } ;
struct mmc_ios {scalar_t__ enhanced_strobe; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ SDHCI_CDNS_HRS06_MODE_MMC_HS400 ; 
 scalar_t__ SDHCI_CDNS_HRS06_MODE_MMC_HS400ES ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 scalar_t__ sdhci_cdns_get_emmc_mode (struct sdhci_cdns_priv*) ; 
 struct sdhci_cdns_priv* sdhci_cdns_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_cdns_set_emmc_mode (struct sdhci_cdns_priv*,scalar_t__) ; 

__attribute__((used)) static void sdhci_cdns_hs400_enhanced_strobe(struct mmc_host *mmc,
					     struct mmc_ios *ios)
{
	struct sdhci_host *host = mmc_priv(mmc);
	struct sdhci_cdns_priv *priv = sdhci_cdns_priv(host);
	u32 mode;

	priv->enhanced_strobe = ios->enhanced_strobe;

	mode = sdhci_cdns_get_emmc_mode(priv);

	if (mode == SDHCI_CDNS_HRS06_MODE_MMC_HS400 && ios->enhanced_strobe)
		sdhci_cdns_set_emmc_mode(priv,
					 SDHCI_CDNS_HRS06_MODE_MMC_HS400ES);

	if (mode == SDHCI_CDNS_HRS06_MODE_MMC_HS400ES && !ios->enhanced_strobe)
		sdhci_cdns_set_emmc_mode(priv,
					 SDHCI_CDNS_HRS06_MODE_MMC_HS400);
}