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
struct rtsx_pcr {int /*<<< orphan*/  pcr_mutex; } ;
struct realtek_pci_sdmmc {int vpclk; int double_clk; int initial_mode; int clock; int /*<<< orphan*/  ssc_depth; struct rtsx_pcr* pcr; scalar_t__ eject; } ;
struct mmc_ios {int clock; int /*<<< orphan*/  timing; int /*<<< orphan*/  power_mode; int /*<<< orphan*/  bus_width; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
#define  MMC_TIMING_MMC_DDR52 132 
#define  MMC_TIMING_UHS_DDR50 131 
#define  MMC_TIMING_UHS_SDR104 130 
#define  MMC_TIMING_UHS_SDR25 129 
#define  MMC_TIMING_UHS_SDR50 128 
 int /*<<< orphan*/  RTSX_SD_CARD ; 
 int /*<<< orphan*/  RTSX_SSC_DEPTH_1M ; 
 int /*<<< orphan*/  RTSX_SSC_DEPTH_2M ; 
 int /*<<< orphan*/  RTSX_SSC_DEPTH_500K ; 
 struct realtek_pci_sdmmc* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rtsx_pci_card_exclusive_check (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_start_run (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  rtsx_pci_switch_clock (struct rtsx_pcr*,int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sd_set_bus_width (struct realtek_pci_sdmmc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_set_power_mode (struct realtek_pci_sdmmc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_set_timing (struct realtek_pci_sdmmc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdmmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct realtek_pci_sdmmc *host = mmc_priv(mmc);
	struct rtsx_pcr *pcr = host->pcr;

	if (host->eject)
		return;

	if (rtsx_pci_card_exclusive_check(host->pcr, RTSX_SD_CARD))
		return;

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);

	sd_set_bus_width(host, ios->bus_width);
	sd_set_power_mode(host, ios->power_mode);
	sd_set_timing(host, ios->timing);

	host->vpclk = false;
	host->double_clk = true;

	switch (ios->timing) {
	case MMC_TIMING_UHS_SDR104:
	case MMC_TIMING_UHS_SDR50:
		host->ssc_depth = RTSX_SSC_DEPTH_2M;
		host->vpclk = true;
		host->double_clk = false;
		break;
	case MMC_TIMING_MMC_DDR52:
	case MMC_TIMING_UHS_DDR50:
	case MMC_TIMING_UHS_SDR25:
		host->ssc_depth = RTSX_SSC_DEPTH_1M;
		break;
	default:
		host->ssc_depth = RTSX_SSC_DEPTH_500K;
		break;
	}

	host->initial_mode = (ios->clock <= 1000000) ? true : false;

	host->clock = ios->clock;
	rtsx_pci_switch_clock(pcr, ios->clock, host->ssc_depth,
			host->initial_mode, host->double_clk, host->vpclk);

	mutex_unlock(&pcr->pcr_mutex);
}