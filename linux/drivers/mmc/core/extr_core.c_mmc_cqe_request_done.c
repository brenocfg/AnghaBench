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
struct mmc_request {int /*<<< orphan*/  (* done ) (struct mmc_request*) ;TYPE_2__* data; int /*<<< orphan*/  tag; TYPE_1__* cmd; } ;
struct mmc_host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; int /*<<< orphan*/  bytes_xfered; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_retune_needed (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_should_fail_request (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  stub1 (struct mmc_request*) ; 
 int /*<<< orphan*/  trace_mmc_request_done (struct mmc_host*,struct mmc_request*) ; 

void mmc_cqe_request_done(struct mmc_host *host, struct mmc_request *mrq)
{
	mmc_should_fail_request(host, mrq);

	/* Flag re-tuning needed on CRC errors */
	if ((mrq->cmd && mrq->cmd->error == -EILSEQ) ||
	    (mrq->data && mrq->data->error == -EILSEQ))
		mmc_retune_needed(host);

	trace_mmc_request_done(host, mrq);

	if (mrq->cmd) {
		pr_debug("%s: CQE req done (direct CMD%u): %d\n",
			 mmc_hostname(host), mrq->cmd->opcode, mrq->cmd->error);
	} else {
		pr_debug("%s: CQE transfer done tag %d\n",
			 mmc_hostname(host), mrq->tag);
	}

	if (mrq->data) {
		pr_debug("%s:     %d bytes transferred: %d\n",
			 mmc_hostname(host),
			 mrq->data->bytes_xfered, mrq->data->error);
	}

	mrq->done(mrq);
}