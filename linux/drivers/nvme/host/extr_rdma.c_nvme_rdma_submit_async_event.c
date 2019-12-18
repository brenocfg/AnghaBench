#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nvme_rdma_queue {TYPE_1__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  done; } ;
struct nvme_rdma_qe {int /*<<< orphan*/  dma; TYPE_3__ cqe; struct nvme_command* data; } ;
struct nvme_rdma_ctrl {struct nvme_rdma_qe async_event_sqe; struct nvme_rdma_queue* queues; } ;
struct nvme_ctrl {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  command_id; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_2__ common; } ;
struct ib_sge {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {struct ib_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  NVME_AQ_BLK_MQ_DEPTH ; 
 int /*<<< orphan*/  NVME_CMD_SGL_METABUF ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (struct ib_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_admin_async_event ; 
 int /*<<< orphan*/  nvme_rdma_async_done ; 
 int nvme_rdma_post_send (struct nvme_rdma_queue*,struct nvme_rdma_qe*,struct ib_sge*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_rdma_set_sg_null (struct nvme_command*) ; 
 struct nvme_rdma_ctrl* to_rdma_ctrl (struct nvme_ctrl*) ; 

__attribute__((used)) static void nvme_rdma_submit_async_event(struct nvme_ctrl *arg)
{
	struct nvme_rdma_ctrl *ctrl = to_rdma_ctrl(arg);
	struct nvme_rdma_queue *queue = &ctrl->queues[0];
	struct ib_device *dev = queue->device->dev;
	struct nvme_rdma_qe *sqe = &ctrl->async_event_sqe;
	struct nvme_command *cmd = sqe->data;
	struct ib_sge sge;
	int ret;

	ib_dma_sync_single_for_cpu(dev, sqe->dma, sizeof(*cmd), DMA_TO_DEVICE);

	memset(cmd, 0, sizeof(*cmd));
	cmd->common.opcode = nvme_admin_async_event;
	cmd->common.command_id = NVME_AQ_BLK_MQ_DEPTH;
	cmd->common.flags |= NVME_CMD_SGL_METABUF;
	nvme_rdma_set_sg_null(cmd);

	sqe->cqe.done = nvme_rdma_async_done;

	ib_dma_sync_single_for_device(dev, sqe->dma, sizeof(*cmd),
			DMA_TO_DEVICE);

	ret = nvme_rdma_post_send(queue, sqe, &sge, 1, NULL);
	WARN_ON_ONCE(ret);
}