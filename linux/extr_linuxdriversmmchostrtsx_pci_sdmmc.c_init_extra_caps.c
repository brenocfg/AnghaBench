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
struct rtsx_pcr {int extra_caps; } ;
struct realtek_pci_sdmmc {struct rtsx_pcr* pcr; struct mmc_host* mmc; } ;
struct mmc_host {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int EXTRA_CAPS_MMC_8BIT ; 
 int EXTRA_CAPS_MMC_HSDDR ; 
 int EXTRA_CAPS_SD_DDR50 ; 
 int EXTRA_CAPS_SD_SDR104 ; 
 int EXTRA_CAPS_SD_SDR50 ; 
 int /*<<< orphan*/  MMC_CAP_1_8V_DDR ; 
 int /*<<< orphan*/  MMC_CAP_8_BIT_DATA ; 
 int /*<<< orphan*/  MMC_CAP_UHS_DDR50 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_SDR104 ; 
 int /*<<< orphan*/  MMC_CAP_UHS_SDR50 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdmmc_dev (struct realtek_pci_sdmmc*) ; 

__attribute__((used)) static void init_extra_caps(struct realtek_pci_sdmmc *host)
{
	struct mmc_host *mmc = host->mmc;
	struct rtsx_pcr *pcr = host->pcr;

	dev_dbg(sdmmc_dev(host), "pcr->extra_caps = 0x%x\n", pcr->extra_caps);

	if (pcr->extra_caps & EXTRA_CAPS_SD_SDR50)
		mmc->caps |= MMC_CAP_UHS_SDR50;
	if (pcr->extra_caps & EXTRA_CAPS_SD_SDR104)
		mmc->caps |= MMC_CAP_UHS_SDR104;
	if (pcr->extra_caps & EXTRA_CAPS_SD_DDR50)
		mmc->caps |= MMC_CAP_UHS_DDR50;
	if (pcr->extra_caps & EXTRA_CAPS_MMC_HSDDR)
		mmc->caps |= MMC_CAP_1_8V_DDR;
	if (pcr->extra_caps & EXTRA_CAPS_MMC_8BIT)
		mmc->caps |= MMC_CAP_8_BIT_DATA;
}