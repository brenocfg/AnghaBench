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
struct sdhci_host {scalar_t__ timing; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int sdhci_execute_tuning (struct mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usdhc_execute_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct sdhci_host *host = mmc_priv(mmc);

	/*
	 * i.MX uSDHC internally already uses a fixed optimized timing for
	 * DDR50, normally does not require tuning for DDR50 mode.
	 */
	if (host->timing == MMC_TIMING_UHS_DDR50)
		return 0;

	return sdhci_execute_tuning(mmc, opcode);
}