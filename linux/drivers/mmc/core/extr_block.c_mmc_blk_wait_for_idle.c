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
struct mmc_queue {scalar_t__ use_cqe; } ;
struct mmc_host {TYPE_1__* cqe_ops; } ;
struct TYPE_2__ {int (* cqe_wait_for_idle ) (struct mmc_host*) ;} ;

/* Variables and functions */
 int mmc_blk_rw_wait (struct mmc_queue*,int /*<<< orphan*/ *) ; 
 int stub1 (struct mmc_host*) ; 

__attribute__((used)) static int mmc_blk_wait_for_idle(struct mmc_queue *mq, struct mmc_host *host)
{
	if (mq->use_cqe)
		return host->cqe_ops->cqe_wait_for_idle(host);

	return mmc_blk_rw_wait(mq, NULL);
}