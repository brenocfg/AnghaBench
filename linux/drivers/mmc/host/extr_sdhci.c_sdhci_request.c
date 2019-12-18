#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sdhci_host {int flags; int /*<<< orphan*/  lock; } ;
struct mmc_request {TYPE_3__* cmd; TYPE_3__* sbc; int /*<<< orphan*/ * stop; TYPE_2__* data; } ;
struct mmc_host {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  error; } ;
struct TYPE_5__ {int /*<<< orphan*/ * stop; } ;
struct TYPE_4__ {int (* get_cd ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEDIUM ; 
 int SDHCI_AUTO_CMD23 ; 
 int SDHCI_DEVICE_DEAD ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 scalar_t__ sdhci_auto_cmd12 (struct sdhci_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  sdhci_finish_mrq (struct sdhci_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  sdhci_led_activate (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_send_command (struct sdhci_host*,TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct mmc_host*) ; 

void sdhci_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct sdhci_host *host;
	int present;
	unsigned long flags;

	host = mmc_priv(mmc);

	/* Firstly check card presence */
	present = mmc->ops->get_cd(mmc);

	spin_lock_irqsave(&host->lock, flags);

	sdhci_led_activate(host);

	/*
	 * Ensure we don't send the STOP for non-SET_BLOCK_COUNTED
	 * requests if Auto-CMD12 is enabled.
	 */
	if (sdhci_auto_cmd12(host, mrq)) {
		if (mrq->stop) {
			mrq->data->stop = NULL;
			mrq->stop = NULL;
		}
	}

	if (!present || host->flags & SDHCI_DEVICE_DEAD) {
		mrq->cmd->error = -ENOMEDIUM;
		sdhci_finish_mrq(host, mrq);
	} else {
		if (mrq->sbc && !(host->flags & SDHCI_AUTO_CMD23))
			sdhci_send_command(host, mrq->sbc);
		else
			sdhci_send_command(host, mrq->cmd);
	}

	spin_unlock_irqrestore(&host->lock, flags);
}