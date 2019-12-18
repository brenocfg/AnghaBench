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
struct sdhci_host {scalar_t__ timing; int /*<<< orphan*/  flags; int /*<<< orphan*/  mmc; } ;
struct TYPE_2__ {int bus_width; } ;
struct mmc_host {TYPE_1__ ios; } ;

/* Variables and functions */
 int EINVAL ; 
 int MMC_BUS_WIDTH_4 ; 
 int MMC_BUS_WIDTH_8 ; 
 int /*<<< orphan*/  MMC_SEND_TUNING_BLOCK_HS200 ; 
 scalar_t__ MMC_TIMING_MMC_HS200 ; 
 int /*<<< orphan*/  SDHCI_HS400_TUNING ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __sdhci_o2_execute_tuning (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_end_tuning (struct sdhci_host*) ; 
 int sdhci_execute_tuning (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_o2_dll_recovery (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_o2_set_tuning_mode (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_o2_wait_dll_detect_lock (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_set_bus_width (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_start_tuning (struct sdhci_host*) ; 

__attribute__((used)) static int sdhci_o2_execute_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct sdhci_host *host = mmc_priv(mmc);
	int current_bus_width = 0;

	/*
	 * This handler only implements the eMMC tuning that is specific to
	 * this controller.  Fall back to the standard method for other TIMING.
	 */
	if (host->timing != MMC_TIMING_MMC_HS200)
		return sdhci_execute_tuning(mmc, opcode);

	if (WARN_ON(opcode != MMC_SEND_TUNING_BLOCK_HS200))
		return -EINVAL;
	/*
	 * Judge the tuning reason, whether caused by dll shift
	 * If cause by dll shift, should call sdhci_o2_dll_recovery
	 */
	if (!sdhci_o2_wait_dll_detect_lock(host))
		if (!sdhci_o2_dll_recovery(host)) {
			pr_err("%s: o2 dll recovery failed\n",
				mmc_hostname(host->mmc));
			return -EINVAL;
		}
	/*
	 * o2 sdhci host didn't support 8bit emmc tuning
	 */
	if (mmc->ios.bus_width == MMC_BUS_WIDTH_8) {
		current_bus_width = mmc->ios.bus_width;
		mmc->ios.bus_width = MMC_BUS_WIDTH_4;
		sdhci_set_bus_width(host, MMC_BUS_WIDTH_4);
	}

	sdhci_o2_set_tuning_mode(host);

	sdhci_start_tuning(host);

	__sdhci_o2_execute_tuning(host, opcode);

	sdhci_end_tuning(host);

	if (current_bus_width == MMC_BUS_WIDTH_8) {
		mmc->ios.bus_width = MMC_BUS_WIDTH_8;
		sdhci_set_bus_width(host, current_bus_width);
	}

	host->flags &= ~SDHCI_HS400_TUNING;
	return 0;
}