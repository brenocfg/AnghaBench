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
struct mmc_request {int /*<<< orphan*/  cmd_completion; scalar_t__ cap_cmd_during_tfr; TYPE_1__* cmd; } ;
struct mmc_host {TYPE_3__* ops; TYPE_2__* cqe_ops; scalar_t__ cqe_on; struct mmc_request* ongoing_mrq; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* request ) (struct mmc_host*,struct mmc_request*) ;scalar_t__ (* card_busy ) (struct mmc_host*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* cqe_off ) (struct mmc_host*) ;} ;
struct TYPE_4__ {int error; int /*<<< orphan*/  arg; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mmc_delay (int) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int mmc_retune (struct mmc_host*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ sdio_is_io_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct mmc_host*) ; 
 int /*<<< orphan*/  stub2 (struct mmc_host*) ; 
 int /*<<< orphan*/  stub3 (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  trace_mmc_request_start (struct mmc_host*,struct mmc_request*) ; 

__attribute__((used)) static void __mmc_start_request(struct mmc_host *host, struct mmc_request *mrq)
{
	int err;

	/* Assumes host controller has been runtime resumed by mmc_claim_host */
	err = mmc_retune(host);
	if (err) {
		mrq->cmd->error = err;
		mmc_request_done(host, mrq);
		return;
	}

	/*
	 * For sdio rw commands we must wait for card busy otherwise some
	 * sdio devices won't work properly.
	 * And bypass I/O abort, reset and bus suspend operations.
	 */
	if (sdio_is_io_busy(mrq->cmd->opcode, mrq->cmd->arg) &&
	    host->ops->card_busy) {
		int tries = 500; /* Wait aprox 500ms at maximum */

		while (host->ops->card_busy(host) && --tries)
			mmc_delay(1);

		if (tries == 0) {
			mrq->cmd->error = -EBUSY;
			mmc_request_done(host, mrq);
			return;
		}
	}

	if (mrq->cap_cmd_during_tfr) {
		host->ongoing_mrq = mrq;
		/*
		 * Retry path could come through here without having waiting on
		 * cmd_completion, so ensure it is reinitialised.
		 */
		reinit_completion(&mrq->cmd_completion);
	}

	trace_mmc_request_start(host, mrq);

	if (host->cqe_on)
		host->cqe_ops->cqe_off(host);

	host->ops->request(host, mrq);
}