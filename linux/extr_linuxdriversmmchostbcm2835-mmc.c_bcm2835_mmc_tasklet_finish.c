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
struct mmc_request {TYPE_3__* data; TYPE_1__* cmd; } ;
struct bcm2835_host {int flags; int /*<<< orphan*/  mmc; int /*<<< orphan*/  lock; int /*<<< orphan*/ * data; int /*<<< orphan*/ * cmd; struct mmc_request* mrq; int /*<<< orphan*/  timer; } ;
struct TYPE_6__ {TYPE_2__* stop; scalar_t__ error; } ;
struct TYPE_5__ {scalar_t__ error; } ;
struct TYPE_4__ {scalar_t__ error; } ;

/* Variables and functions */
 int SDHCI_DEVICE_DEAD ; 
 int /*<<< orphan*/  SDHCI_RESET_CMD ; 
 int /*<<< orphan*/  SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  bcm2835_mmc_reset (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_mmc_tasklet_finish(unsigned long param)
{
	struct bcm2835_host *host;
	unsigned long flags;
	struct mmc_request *mrq;

	host = (struct bcm2835_host *)param;

	spin_lock_irqsave(&host->lock, flags);

	/*
	 * If this tasklet gets rescheduled while running, it will
	 * be run again afterwards but without any active request.
	 */
	if (!host->mrq) {
		spin_unlock_irqrestore(&host->lock, flags);
		return;
	}

	del_timer(&host->timer);

	mrq = host->mrq;

	/*
	 * The controller needs a reset of internal state machines
	 * upon error conditions.
	 */
	if (!(host->flags & SDHCI_DEVICE_DEAD) &&
	    ((mrq->cmd && mrq->cmd->error) ||
		 (mrq->data && (mrq->data->error ||
		  (mrq->data->stop && mrq->data->stop->error))))) {

		spin_unlock_irqrestore(&host->lock, flags);
		bcm2835_mmc_reset(host, SDHCI_RESET_CMD);
		bcm2835_mmc_reset(host, SDHCI_RESET_DATA);
		spin_lock_irqsave(&host->lock, flags);
	}

	host->mrq = NULL;
	host->cmd = NULL;
	host->data = NULL;

	mmiowb();

	spin_unlock_irqrestore(&host->lock, flags);
	mmc_request_done(host->mmc, mrq);
}