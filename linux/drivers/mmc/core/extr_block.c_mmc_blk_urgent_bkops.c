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
struct mmc_queue_req {int dummy; } ;
struct mmc_queue {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 scalar_t__ mmc_blk_urgent_bkops_needed (struct mmc_queue*,struct mmc_queue_req*) ; 
 int /*<<< orphan*/  mmc_run_bkops (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_blk_urgent_bkops(struct mmc_queue *mq,
				 struct mmc_queue_req *mqrq)
{
	if (mmc_blk_urgent_bkops_needed(mq, mqrq))
		mmc_run_bkops(mq->card);
}