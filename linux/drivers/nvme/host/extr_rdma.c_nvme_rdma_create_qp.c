#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvme_rdma_queue {int const queue_size; TYPE_2__* cm_id; int /*<<< orphan*/  qp; int /*<<< orphan*/  ib_cq; struct nvme_rdma_device* device; } ;
struct nvme_rdma_device {int /*<<< orphan*/  pd; scalar_t__ num_inline_segments; } ;
struct TYPE_3__ {int max_send_wr; int max_recv_wr; int max_recv_sge; scalar_t__ max_send_sge; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_type; TYPE_1__ cap; int /*<<< orphan*/  event_handler; } ;
typedef  int /*<<< orphan*/  init_attr ;
struct TYPE_4__ {int /*<<< orphan*/  qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPT_RC ; 
 int /*<<< orphan*/  IB_SIGNAL_REQ_WR ; 
 int /*<<< orphan*/  memset (struct ib_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_rdma_qp_event ; 
 int rdma_create_qp (TYPE_2__*,int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 

__attribute__((used)) static int nvme_rdma_create_qp(struct nvme_rdma_queue *queue, const int factor)
{
	struct nvme_rdma_device *dev = queue->device;
	struct ib_qp_init_attr init_attr;
	int ret;

	memset(&init_attr, 0, sizeof(init_attr));
	init_attr.event_handler = nvme_rdma_qp_event;
	/* +1 for drain */
	init_attr.cap.max_send_wr = factor * queue->queue_size + 1;
	/* +1 for drain */
	init_attr.cap.max_recv_wr = queue->queue_size + 1;
	init_attr.cap.max_recv_sge = 1;
	init_attr.cap.max_send_sge = 1 + dev->num_inline_segments;
	init_attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	init_attr.qp_type = IB_QPT_RC;
	init_attr.send_cq = queue->ib_cq;
	init_attr.recv_cq = queue->ib_cq;

	ret = rdma_create_qp(queue->cm_id, dev->pd, &init_attr);

	queue->qp = queue->cm_id->qp;
	return ret;
}