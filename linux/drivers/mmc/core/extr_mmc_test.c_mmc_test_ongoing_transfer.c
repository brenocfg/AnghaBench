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
typedef  int u32 ;
struct TYPE_6__ {int* resp; } ;
struct mmc_request {int cap_cmd_during_tfr; TYPE_1__* data; int /*<<< orphan*/ * sbc; } ;
struct mmc_test_req {TYPE_3__ status; int /*<<< orphan*/  sbc; struct mmc_request mrq; } ;
struct mmc_test_area {int blocks; int max_tfr; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct mmc_test_card {TYPE_2__* card; struct mmc_test_area area; } ;
struct mmc_host {int dummy; } ;
struct TYPE_5__ {struct mmc_host* host; } ;
struct TYPE_4__ {scalar_t__ stop; scalar_t__ error; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 scalar_t__ R1_CURRENT_STATE (int) ; 
 int R1_ERROR ; 
 scalar_t__ R1_STATE_TRAN ; 
 int RESULT_UNSUP_CARD ; 
 int RESULT_UNSUP_HOST ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (struct mmc_test_req*) ; 
 scalar_t__ mmc_host_cmd23 (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 scalar_t__ mmc_is_req_done (struct mmc_host*,struct mmc_request*) ; 
 int mmc_test_check_result (struct mmc_test_card*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_test_prepare_mrq (struct mmc_test_card*,struct mmc_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 
 struct mmc_test_req* mmc_test_req_alloc () ; 
 int mmc_test_send_status (struct mmc_test_card*,TYPE_3__*) ; 
 int mmc_test_start_areq (struct mmc_test_card*,struct mmc_request*,struct mmc_request*) ; 
 int mmc_test_wait_busy (struct mmc_test_card*) ; 
 int mmc_wait_for_cmd (struct mmc_host*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_wait_for_req (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mmc_wait_for_req_done (struct mmc_host*,struct mmc_request*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,...) ; 
 int time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int mmc_test_ongoing_transfer(struct mmc_test_card *test,
				     unsigned int dev_addr, int use_sbc,
				     int repeat_cmd, int write, int use_areq)
{
	struct mmc_test_req *rq = mmc_test_req_alloc();
	struct mmc_host *host = test->card->host;
	struct mmc_test_area *t = &test->area;
	struct mmc_request *mrq;
	unsigned long timeout;
	bool expired = false;
	int ret = 0, cmd_ret;
	u32 status = 0;
	int count = 0;

	if (!rq)
		return -ENOMEM;

	mrq = &rq->mrq;
	if (use_sbc)
		mrq->sbc = &rq->sbc;
	mrq->cap_cmd_during_tfr = true;

	mmc_test_prepare_mrq(test, mrq, t->sg, t->sg_len, dev_addr, t->blocks,
			     512, write);

	if (use_sbc && t->blocks > 1 && !mrq->sbc) {
		ret =  mmc_host_cmd23(host) ?
		       RESULT_UNSUP_CARD :
		       RESULT_UNSUP_HOST;
		goto out_free;
	}

	/* Start ongoing data request */
	if (use_areq) {
		ret = mmc_test_start_areq(test, mrq, NULL);
		if (ret)
			goto out_free;
	} else {
		mmc_wait_for_req(host, mrq);
	}

	timeout = jiffies + msecs_to_jiffies(3000);
	do {
		count += 1;

		/* Send status command while data transfer in progress */
		cmd_ret = mmc_test_send_status(test, &rq->status);
		if (cmd_ret)
			break;

		status = rq->status.resp[0];
		if (status & R1_ERROR) {
			cmd_ret = -EIO;
			break;
		}

		if (mmc_is_req_done(host, mrq))
			break;

		expired = time_after(jiffies, timeout);
		if (expired) {
			pr_info("%s: timeout waiting for Tran state status %#x\n",
				mmc_hostname(host), status);
			cmd_ret = -ETIMEDOUT;
			break;
		}
	} while (repeat_cmd && R1_CURRENT_STATE(status) != R1_STATE_TRAN);

	/* Wait for data request to complete */
	if (use_areq) {
		ret = mmc_test_start_areq(test, NULL, mrq);
	} else {
		mmc_wait_for_req_done(test->card->host, mrq);
	}

	/*
	 * For cap_cmd_during_tfr request, upper layer must send stop if
	 * required.
	 */
	if (mrq->data->stop && (mrq->data->error || !mrq->sbc)) {
		if (ret)
			mmc_wait_for_cmd(host, mrq->data->stop, 0);
		else
			ret = mmc_wait_for_cmd(host, mrq->data->stop, 0);
	}

	if (ret)
		goto out_free;

	if (cmd_ret) {
		pr_info("%s: Send Status failed: status %#x, error %d\n",
			mmc_hostname(test->card->host), status, cmd_ret);
	}

	ret = mmc_test_check_result(test, mrq);
	if (ret)
		goto out_free;

	ret = mmc_test_wait_busy(test);
	if (ret)
		goto out_free;

	if (repeat_cmd && (t->blocks + 1) << 9 > t->max_tfr)
		pr_info("%s: %d commands completed during transfer of %u blocks\n",
			mmc_hostname(test->card->host), count, t->blocks);

	if (cmd_ret)
		ret = cmd_ret;
out_free:
	kfree(rq);

	return ret;
}