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
struct sdhci_host {scalar_t__ timing; scalar_t__ tuning_mode; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ MMC_TIMING_MMC_DDR52 ; 
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 scalar_t__ SDHCI_TUNING_MODE_1 ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int sdhci_execute_tuning (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenon_retune_setup (struct sdhci_host*) ; 

__attribute__((used)) static int xenon_execute_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct sdhci_host *host = mmc_priv(mmc);

	if (host->timing == MMC_TIMING_UHS_DDR50 ||
		host->timing == MMC_TIMING_MMC_DDR52)
		return 0;

	/*
	 * Currently force Xenon driver back to support mode 1 only,
	 * even though Xenon might claim to support mode 2 or mode 3.
	 * It requires more time to test mode 2/mode 3 on more platforms.
	 */
	if (host->tuning_mode != SDHCI_TUNING_MODE_1)
		xenon_retune_setup(host);

	return sdhci_execute_tuning(mmc, opcode);
}