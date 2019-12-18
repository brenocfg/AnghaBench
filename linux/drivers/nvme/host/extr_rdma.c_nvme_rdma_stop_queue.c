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
struct nvme_rdma_queue {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_RDMA_Q_LIVE ; 
 int /*<<< orphan*/  __nvme_rdma_stop_queue (struct nvme_rdma_queue*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_rdma_stop_queue(struct nvme_rdma_queue *queue)
{
	if (!test_and_clear_bit(NVME_RDMA_Q_LIVE, &queue->flags))
		return;
	__nvme_rdma_stop_queue(queue);
}