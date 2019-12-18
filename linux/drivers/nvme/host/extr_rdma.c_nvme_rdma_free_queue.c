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
struct nvme_rdma_queue {int /*<<< orphan*/  cm_id; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_RDMA_Q_ALLOCATED ; 
 int /*<<< orphan*/  nvme_rdma_destroy_queue_ib (struct nvme_rdma_queue*) ; 
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvme_rdma_free_queue(struct nvme_rdma_queue *queue)
{
	if (!test_and_clear_bit(NVME_RDMA_Q_ALLOCATED, &queue->flags))
		return;

	nvme_rdma_destroy_queue_ib(queue);
	rdma_destroy_id(queue->cm_id);
}