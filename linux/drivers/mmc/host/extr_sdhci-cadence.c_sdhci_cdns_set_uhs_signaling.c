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
struct sdhci_cdns_priv {int /*<<< orphan*/  enhanced_strobe; } ;

/* Variables and functions */
#define  MMC_TIMING_MMC_DDR52 131 
#define  MMC_TIMING_MMC_HS 130 
#define  MMC_TIMING_MMC_HS200 129 
#define  MMC_TIMING_MMC_HS400 128 
 scalar_t__ SDHCI_CDNS_HRS06_MODE_MMC_DDR ; 
 scalar_t__ SDHCI_CDNS_HRS06_MODE_MMC_HS200 ; 
 scalar_t__ SDHCI_CDNS_HRS06_MODE_MMC_HS400 ; 
 scalar_t__ SDHCI_CDNS_HRS06_MODE_MMC_HS400ES ; 
 scalar_t__ SDHCI_CDNS_HRS06_MODE_MMC_SDR ; 
 scalar_t__ SDHCI_CDNS_HRS06_MODE_SD ; 
 struct sdhci_cdns_priv* sdhci_cdns_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_cdns_set_emmc_mode (struct sdhci_cdns_priv*,scalar_t__) ; 
 int /*<<< orphan*/  sdhci_set_uhs_signaling (struct sdhci_host*,unsigned int) ; 

__attribute__((used)) static void sdhci_cdns_set_uhs_signaling(struct sdhci_host *host,
					 unsigned int timing)
{
	struct sdhci_cdns_priv *priv = sdhci_cdns_priv(host);
	u32 mode;

	switch (timing) {
	case MMC_TIMING_MMC_HS:
		mode = SDHCI_CDNS_HRS06_MODE_MMC_SDR;
		break;
	case MMC_TIMING_MMC_DDR52:
		mode = SDHCI_CDNS_HRS06_MODE_MMC_DDR;
		break;
	case MMC_TIMING_MMC_HS200:
		mode = SDHCI_CDNS_HRS06_MODE_MMC_HS200;
		break;
	case MMC_TIMING_MMC_HS400:
		if (priv->enhanced_strobe)
			mode = SDHCI_CDNS_HRS06_MODE_MMC_HS400ES;
		else
			mode = SDHCI_CDNS_HRS06_MODE_MMC_HS400;
		break;
	default:
		mode = SDHCI_CDNS_HRS06_MODE_SD;
		break;
	}

	sdhci_cdns_set_emmc_mode(priv, mode);

	/* For SD, fall back to the default handler */
	if (mode == SDHCI_CDNS_HRS06_MODE_SD)
		sdhci_set_uhs_signaling(host, timing);
}