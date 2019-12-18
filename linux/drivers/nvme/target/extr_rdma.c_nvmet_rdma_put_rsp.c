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
struct nvmet_rdma_rsp {TYPE_1__* queue; int /*<<< orphan*/  free_list; int /*<<< orphan*/  allocated; } ;
struct TYPE_2__ {int /*<<< orphan*/  rsps_lock; int /*<<< orphan*/  free_rsps; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvmet_rdma_rsp*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmet_rdma_free_rsp (int /*<<< orphan*/ ,struct nvmet_rdma_rsp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
nvmet_rdma_put_rsp(struct nvmet_rdma_rsp *rsp)
{
	unsigned long flags;

	if (unlikely(rsp->allocated)) {
		nvmet_rdma_free_rsp(rsp->queue->dev, rsp);
		kfree(rsp);
		return;
	}

	spin_lock_irqsave(&rsp->queue->rsps_lock, flags);
	list_add_tail(&rsp->free_list, &rsp->queue->free_rsps);
	spin_unlock_irqrestore(&rsp->queue->rsps_lock, flags);
}