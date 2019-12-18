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
struct nvmet_rdma_queue {int state; int /*<<< orphan*/  release_work; int /*<<< orphan*/  cm_id; int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
#define  NVMET_RDMA_Q_CONNECTING 130 
#define  NVMET_RDMA_Q_DISCONNECTING 129 
#define  NVMET_RDMA_Q_LIVE 128 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __nvmet_rdma_queue_disconnect(struct nvmet_rdma_queue *queue)
{
	bool disconnect = false;
	unsigned long flags;

	pr_debug("cm_id= %p queue->state= %d\n", queue->cm_id, queue->state);

	spin_lock_irqsave(&queue->state_lock, flags);
	switch (queue->state) {
	case NVMET_RDMA_Q_CONNECTING:
	case NVMET_RDMA_Q_LIVE:
		queue->state = NVMET_RDMA_Q_DISCONNECTING;
		disconnect = true;
		break;
	case NVMET_RDMA_Q_DISCONNECTING:
		break;
	}
	spin_unlock_irqrestore(&queue->state_lock, flags);

	if (disconnect) {
		rdma_disconnect(queue->cm_id);
		schedule_work(&queue->release_work);
	}
}