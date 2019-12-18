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
struct sdhci_host {int cqe_on; scalar_t__ clock; scalar_t__ v4_mode; struct mmc_host* mmc; } ;
struct mmc_host {int /*<<< orphan*/  ios; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_ios ) (struct mmc_host*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int SDHCI_RESET_ALL ; 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  sdhci_do_enable_v4_mode (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_do_reset (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_set_default_irqs (struct sdhci_host*) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdhci_init(struct sdhci_host *host, int soft)
{
	struct mmc_host *mmc = host->mmc;

	if (soft)
		sdhci_do_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
	else
		sdhci_do_reset(host, SDHCI_RESET_ALL);

	if (host->v4_mode)
		sdhci_do_enable_v4_mode(host);

	sdhci_set_default_irqs(host);

	host->cqe_on = false;

	if (soft) {
		/* force clock reconfiguration */
		host->clock = 0;
		mmc->ops->set_ios(mmc, &mmc->ios);
	}
}