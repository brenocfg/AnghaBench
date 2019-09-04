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
struct request {int dummy; } ;
struct mmc_queue {int /*<<< orphan*/  complete_lock; struct request* complete_req; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_blk_mq_poll_completion (struct mmc_queue*,struct request*) ; 
 int /*<<< orphan*/  mmc_blk_mq_post_req (struct mmc_queue*,struct request*) ; 
 scalar_t__ mmc_host_done_complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mmc_blk_mq_complete_prev_req(struct mmc_queue *mq,
					 struct request **prev_req)
{
	if (mmc_host_done_complete(mq->card->host))
		return;

	mutex_lock(&mq->complete_lock);

	if (!mq->complete_req)
		goto out_unlock;

	mmc_blk_mq_poll_completion(mq, mq->complete_req);

	if (prev_req)
		*prev_req = mq->complete_req;
	else
		mmc_blk_mq_post_req(mq, mq->complete_req);

	mq->complete_req = NULL;

out_unlock:
	mutex_unlock(&mq->complete_lock);
}