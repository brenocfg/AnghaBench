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
struct request {int dummy; } ;
struct mmc_queue {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_blk_mq_complete_prev_req (struct mmc_queue*,struct request**) ; 
 int /*<<< orphan*/  mmc_blk_rw_wait_cond (struct mmc_queue*,int*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_blk_rw_wait(struct mmc_queue *mq, struct request **prev_req)
{
	int err = 0;

	wait_event(mq->wait, mmc_blk_rw_wait_cond(mq, &err));

	/* Always complete the previous request if there is one */
	mmc_blk_mq_complete_prev_req(mq, prev_req);

	return err;
}