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
struct sdhci_host {TYPE_1__* ops; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hw_reset ) (struct sdhci_host*) ;} ;

/* Variables and functions */
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (struct sdhci_host*) ; 

__attribute__((used)) static void sdhci_hw_reset(struct mmc_host *mmc)
{
	struct sdhci_host *host = mmc_priv(mmc);

	if (host->ops && host->ops->hw_reset)
		host->ops->hw_reset(host);
}