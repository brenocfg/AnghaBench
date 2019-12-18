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
struct sdhci_host {int /*<<< orphan*/  tuning_err; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int sdhci_execute_tuning (struct mmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sdhci_post_tuning (struct sdhci_host*) ; 

__attribute__((used)) static int tegra_sdhci_execute_hw_tuning(struct mmc_host *mmc, u32 opcode)
{
	struct sdhci_host *host = mmc_priv(mmc);
	int err;

	err = sdhci_execute_tuning(mmc, opcode);
	if (!err && !host->tuning_err)
		tegra_sdhci_post_tuning(host);

	return err;
}