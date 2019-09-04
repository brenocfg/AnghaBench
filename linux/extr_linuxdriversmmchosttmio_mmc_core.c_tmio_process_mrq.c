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
struct tmio_mmc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/ * mrq; int /*<<< orphan*/  delayed_reset_work; struct mmc_command* cmd; } ;
struct mmc_request {struct mmc_command* cmd; scalar_t__ data; struct mmc_command* sbc; } ;
struct mmc_command {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDREQ_TIMEOUT ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tmio_mmc_start_command (struct tmio_mmc_host*,struct mmc_command*) ; 
 int tmio_mmc_start_data (struct tmio_mmc_host*,scalar_t__) ; 

__attribute__((used)) static void tmio_process_mrq(struct tmio_mmc_host *host,
			     struct mmc_request *mrq)
{
	struct mmc_command *cmd;
	int ret;

	if (mrq->sbc && host->cmd != mrq->sbc) {
		cmd = mrq->sbc;
	} else {
		cmd = mrq->cmd;
		if (mrq->data) {
			ret = tmio_mmc_start_data(host, mrq->data);
			if (ret)
				goto fail;
		}
	}

	ret = tmio_mmc_start_command(host, cmd);
	if (ret)
		goto fail;

	schedule_delayed_work(&host->delayed_reset_work,
			      msecs_to_jiffies(CMDREQ_TIMEOUT));
	return;

fail:
	host->mrq = NULL;
	mrq->cmd->error = ret;
	mmc_request_done(host->mmc, mrq);
}