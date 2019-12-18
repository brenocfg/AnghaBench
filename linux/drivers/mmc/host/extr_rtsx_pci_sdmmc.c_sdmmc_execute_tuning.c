#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rtsx_pcr {int /*<<< orphan*/  pcr_mutex; } ;
struct realtek_pci_sdmmc {struct rtsx_pcr* pcr; scalar_t__ eject; } ;
struct TYPE_2__ {int timing; } ;
struct mmc_host {TYPE_1__ ios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDR50_RX_PHASE (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  DDR50_TX_PHASE (struct rtsx_pcr*) ; 
 int ENOMEDIUM ; 
#define  MMC_TIMING_UHS_DDR50 130 
#define  MMC_TIMING_UHS_SDR104 129 
#define  MMC_TIMING_UHS_SDR50 128 
 int /*<<< orphan*/  RTSX_SD_CARD ; 
 int /*<<< orphan*/  SDR104_TX_PHASE (struct rtsx_pcr*) ; 
 int /*<<< orphan*/  SDR50_TX_PHASE (struct rtsx_pcr*) ; 
 struct realtek_pci_sdmmc* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtsx_pci_card_exclusive_check (struct rtsx_pcr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_start_run (struct rtsx_pcr*) ; 
 int sd_change_phase (struct realtek_pci_sdmmc*,int /*<<< orphan*/ ,int) ; 
 int sd_tuning_rx (struct realtek_pci_sdmmc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdmmc_execute_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct realtek_pci_sdmmc *host = mmc_priv(mmc);
	struct rtsx_pcr *pcr = host->pcr;
	int err = 0;

	if (host->eject)
		return -ENOMEDIUM;

	err = rtsx_pci_card_exclusive_check(host->pcr, RTSX_SD_CARD);
	if (err)
		return err;

	mutex_lock(&pcr->pcr_mutex);

	rtsx_pci_start_run(pcr);

	/* Set initial TX phase */
	switch (mmc->ios.timing) {
	case MMC_TIMING_UHS_SDR104:
		err = sd_change_phase(host, SDR104_TX_PHASE(pcr), false);
		break;

	case MMC_TIMING_UHS_SDR50:
		err = sd_change_phase(host, SDR50_TX_PHASE(pcr), false);
		break;

	case MMC_TIMING_UHS_DDR50:
		err = sd_change_phase(host, DDR50_TX_PHASE(pcr), false);
		break;

	default:
		err = 0;
	}

	if (err)
		goto out;

	/* Tuning RX phase */
	if ((mmc->ios.timing == MMC_TIMING_UHS_SDR104) ||
			(mmc->ios.timing == MMC_TIMING_UHS_SDR50))
		err = sd_tuning_rx(host, opcode);
	else if (mmc->ios.timing == MMC_TIMING_UHS_DDR50)
		err = sd_change_phase(host, DDR50_RX_PHASE(pcr), true);

out:
	mutex_unlock(&pcr->pcr_mutex);

	return err;
}