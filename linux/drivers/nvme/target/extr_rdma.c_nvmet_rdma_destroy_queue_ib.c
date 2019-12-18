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
struct nvmet_rdma_queue {int /*<<< orphan*/  cq; TYPE_1__* cm_id; } ;
struct ib_qp {int dummy; } ;
struct TYPE_2__ {struct ib_qp* qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_destroy_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  ib_drain_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  ib_free_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_1__*) ; 

__attribute__((used)) static void nvmet_rdma_destroy_queue_ib(struct nvmet_rdma_queue *queue)
{
	struct ib_qp *qp = queue->cm_id->qp;

	ib_drain_qp(qp);
	rdma_destroy_id(queue->cm_id);
	ib_destroy_qp(qp);
	ib_free_cq(queue->cq);
}