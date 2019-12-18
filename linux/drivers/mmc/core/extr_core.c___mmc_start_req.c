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
struct mmc_request {int /*<<< orphan*/  completion; TYPE_1__* cmd; int /*<<< orphan*/  done; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int error; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_complete_cmd (struct mmc_request*) ; 
 int mmc_start_request (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_wait_done ; 
 int /*<<< orphan*/  mmc_wait_ongoing_tfr_cmd (struct mmc_host*) ; 

__attribute__((used)) static int __mmc_start_req(struct mmc_host *host, struct mmc_request *mrq)
{
	int err;

	mmc_wait_ongoing_tfr_cmd(host);

	init_completion(&mrq->completion);
	mrq->done = mmc_wait_done;

	err = mmc_start_request(host, mrq);
	if (err) {
		mrq->cmd->error = err;
		mmc_complete_cmd(mrq);
		complete(&mrq->completion);
	}

	return err;
}