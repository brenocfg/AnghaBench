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
struct tmio_mmc_host {scalar_t__ cmd; int /*<<< orphan*/  mmc; struct mmc_request* mrq; scalar_t__ (* check_scc_error ) (struct tmio_mmc_host*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  delayed_reset_work; int /*<<< orphan*/ * data; } ;
struct mmc_request {scalar_t__ sbc; TYPE_2__* cmd; TYPE_1__* data; } ;
struct TYPE_4__ {scalar_t__ error; } ;
struct TYPE_3__ {scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct mmc_request*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_retune_needed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_mmc_abort_dma (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  tmio_process_mrq (struct tmio_mmc_host*,struct mmc_request*) ; 

__attribute__((used)) static void tmio_mmc_finish_request(struct tmio_mmc_host *host)
{
	struct mmc_request *mrq;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);

	mrq = host->mrq;
	if (IS_ERR_OR_NULL(mrq)) {
		spin_unlock_irqrestore(&host->lock, flags);
		return;
	}

	/* If not SET_BLOCK_COUNT, clear old data */
	if (host->cmd != mrq->sbc) {
		host->cmd = NULL;
		host->data = NULL;
		host->mrq = NULL;
	}

	cancel_delayed_work(&host->delayed_reset_work);

	spin_unlock_irqrestore(&host->lock, flags);

	if (mrq->cmd->error || (mrq->data && mrq->data->error))
		tmio_mmc_abort_dma(host);

	/* SCC error means retune, but executed command was still successful */
	if (host->check_scc_error && host->check_scc_error(host))
		mmc_retune_needed(host->mmc);

	/* If SET_BLOCK_COUNT, continue with main command */
	if (host->mrq && !mrq->cmd->error) {
		tmio_process_mrq(host, mrq);
		return;
	}

	mmc_request_done(host->mmc, mrq);
}