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
struct nvme_queue {scalar_t__ sq_tail; scalar_t__ last_sq_tail; int /*<<< orphan*/  sq_lock; } ;
struct blk_mq_hw_ctx {struct nvme_queue* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvme_write_sq_db (struct nvme_queue*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_commit_rqs(struct blk_mq_hw_ctx *hctx)
{
	struct nvme_queue *nvmeq = hctx->driver_data;

	spin_lock(&nvmeq->sq_lock);
	if (nvmeq->sq_tail != nvmeq->last_sq_tail)
		nvme_write_sq_db(nvmeq, true);
	spin_unlock(&nvmeq->sq_lock);
}