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
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {int timing; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
#define  MMC_TIMING_MMC_DDR52 135 
#define  MMC_TIMING_MMC_HS200 134 
#define  MMC_TIMING_MMC_HS400 133 
#define  MMC_TIMING_UHS_DDR50 132 
#define  MMC_TIMING_UHS_SDR104 131 
#define  MMC_TIMING_UHS_SDR12 130 
#define  MMC_TIMING_UHS_SDR25 129 
#define  MMC_TIMING_UHS_SDR50 128 
 int /*<<< orphan*/  SDHCI_PRESET_FOR_DDR50 ; 
 int /*<<< orphan*/  SDHCI_PRESET_FOR_HS400 ; 
 int /*<<< orphan*/  SDHCI_PRESET_FOR_SDR104 ; 
 int /*<<< orphan*/  SDHCI_PRESET_FOR_SDR12 ; 
 int /*<<< orphan*/  SDHCI_PRESET_FOR_SDR25 ; 
 int /*<<< orphan*/  SDHCI_PRESET_FOR_SDR50 ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 sdhci_get_preset_value(struct sdhci_host *host)
{
	u16 preset = 0;

	switch (host->timing) {
	case MMC_TIMING_UHS_SDR12:
		preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR12);
		break;
	case MMC_TIMING_UHS_SDR25:
		preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR25);
		break;
	case MMC_TIMING_UHS_SDR50:
		preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR50);
		break;
	case MMC_TIMING_UHS_SDR104:
	case MMC_TIMING_MMC_HS200:
		preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR104);
		break;
	case MMC_TIMING_UHS_DDR50:
	case MMC_TIMING_MMC_DDR52:
		preset = sdhci_readw(host, SDHCI_PRESET_FOR_DDR50);
		break;
	case MMC_TIMING_MMC_HS400:
		preset = sdhci_readw(host, SDHCI_PRESET_FOR_HS400);
		break;
	default:
		pr_warn("%s: Invalid UHS-I mode selected\n",
			mmc_hostname(host->mmc));
		preset = sdhci_readw(host, SDHCI_PRESET_FOR_SDR12);
		break;
	}
	return preset;
}