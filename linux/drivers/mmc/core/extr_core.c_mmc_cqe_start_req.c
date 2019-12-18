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
struct mmc_request {int /*<<< orphan*/  tag; TYPE_1__* cmd; struct mmc_host* host; } ;
struct mmc_host {TYPE_2__* cqe_ops; } ;
struct TYPE_4__ {int (* cqe_request ) (struct mmc_host*,struct mmc_request*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_mrq_pr_debug (struct mmc_host*,struct mmc_request*,int) ; 
 int mmc_mrq_prep (struct mmc_host*,struct mmc_request*) ; 
 int mmc_retune (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  trace_mmc_request_start (struct mmc_host*,struct mmc_request*) ; 

int mmc_cqe_start_req(struct mmc_host *host, struct mmc_request *mrq)
{
	int err;

	/*
	 * CQE cannot process re-tuning commands. Caller must hold retuning
	 * while CQE is in use.  Re-tuning can happen here only when CQE has no
	 * active requests i.e. this is the first.  Note, re-tuning will call
	 * ->cqe_off().
	 */
	err = mmc_retune(host);
	if (err)
		goto out_err;

	mrq->host = host;

	mmc_mrq_pr_debug(host, mrq, true);

	err = mmc_mrq_prep(host, mrq);
	if (err)
		goto out_err;

	err = host->cqe_ops->cqe_request(host, mrq);
	if (err)
		goto out_err;

	trace_mmc_request_start(host, mrq);

	return 0;

out_err:
	if (mrq->cmd) {
		pr_debug("%s: failed to start CQE direct CMD%u, error %d\n",
			 mmc_hostname(host), mrq->cmd->opcode, err);
	} else {
		pr_debug("%s: failed to start CQE transfer for tag %d, error %d\n",
			 mmc_hostname(host), mrq->tag, err);
	}
	return err;
}