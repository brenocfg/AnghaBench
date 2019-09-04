#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdhci_host {int /*<<< orphan*/  lock; int /*<<< orphan*/  mmc; TYPE_2__* ops; } ;
struct mmc_host {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* card_event ) (struct sdhci_host*) ;} ;
struct TYPE_3__ {int (* get_cd ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  SDHCI_RESET_CMD ; 
 int /*<<< orphan*/  SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_do_reset (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_error_out_mrqs (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ sdhci_has_requests (struct sdhci_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sdhci_host*) ; 
 int stub2 (struct mmc_host*) ; 

__attribute__((used)) static void sdhci_card_event(struct mmc_host *mmc)
{
	struct sdhci_host *host = mmc_priv(mmc);
	unsigned long flags;
	int present;

	/* First check if client has provided their own card event */
	if (host->ops->card_event)
		host->ops->card_event(host);

	present = mmc->ops->get_cd(mmc);

	spin_lock_irqsave(&host->lock, flags);

	/* Check sdhci_has_requests() first in case we are runtime suspended */
	if (sdhci_has_requests(host) && !present) {
		pr_err("%s: Card removed during transfer!\n",
			mmc_hostname(host->mmc));
		pr_err("%s: Resetting controller.\n",
			mmc_hostname(host->mmc));

		sdhci_do_reset(host, SDHCI_RESET_CMD);
		sdhci_do_reset(host, SDHCI_RESET_DATA);

		sdhci_error_out_mrqs(host, -ENOMEDIUM);
	}

	spin_unlock_irqrestore(&host->lock, flags);
}