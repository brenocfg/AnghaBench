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
struct mmc_test_card {TYPE_1__* card; } ;
struct mmc_request {int /*<<< orphan*/  completion; int /*<<< orphan*/  done; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {struct mmc_host* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_post_req (struct mmc_host*,struct mmc_request*,int) ; 
 int /*<<< orphan*/  mmc_pre_req (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_retune_release (struct mmc_host*) ; 
 int mmc_start_request (struct mmc_host*,struct mmc_request*) ; 
 int mmc_test_check_result (struct mmc_test_card*,struct mmc_request*) ; 
 int mmc_test_wait_busy (struct mmc_test_card*) ; 
 int /*<<< orphan*/  mmc_test_wait_done ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmc_test_start_areq(struct mmc_test_card *test,
			       struct mmc_request *mrq,
			       struct mmc_request *prev_mrq)
{
	struct mmc_host *host = test->card->host;
	int err = 0;

	if (mrq) {
		init_completion(&mrq->completion);
		mrq->done = mmc_test_wait_done;
		mmc_pre_req(host, mrq);
	}

	if (prev_mrq) {
		wait_for_completion(&prev_mrq->completion);
		err = mmc_test_wait_busy(test);
		if (!err)
			err = mmc_test_check_result(test, prev_mrq);
	}

	if (!err && mrq) {
		err = mmc_start_request(host, mrq);
		if (err)
			mmc_retune_release(host);
	}

	if (prev_mrq)
		mmc_post_req(host, prev_mrq, 0);

	if (err && mrq)
		mmc_post_req(host, mrq, err);

	return err;
}