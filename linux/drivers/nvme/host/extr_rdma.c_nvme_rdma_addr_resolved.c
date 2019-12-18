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
struct nvme_rdma_queue {int /*<<< orphan*/  cm_error; int /*<<< orphan*/  cm_id; TYPE_1__* ctrl; } ;
struct nvme_ctrl {int /*<<< orphan*/  device; TYPE_2__* opts; } ;
struct TYPE_4__ {scalar_t__ tos; } ;
struct TYPE_3__ {struct nvme_ctrl ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_RDMA_CONNECT_TIMEOUT_MS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int nvme_rdma_create_queue_ib (struct nvme_rdma_queue*) ; 
 int /*<<< orphan*/  nvme_rdma_destroy_queue_ib (struct nvme_rdma_queue*) ; 
 int rdma_resolve_route (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_set_service_type (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nvme_rdma_addr_resolved(struct nvme_rdma_queue *queue)
{
	struct nvme_ctrl *ctrl = &queue->ctrl->ctrl;
	int ret;

	ret = nvme_rdma_create_queue_ib(queue);
	if (ret)
		return ret;

	if (ctrl->opts->tos >= 0)
		rdma_set_service_type(queue->cm_id, ctrl->opts->tos);
	ret = rdma_resolve_route(queue->cm_id, NVME_RDMA_CONNECT_TIMEOUT_MS);
	if (ret) {
		dev_err(ctrl->device, "rdma_resolve_route failed (%d).\n",
			queue->cm_error);
		goto out_destroy_queue;
	}

	return 0;

out_destroy_queue:
	nvme_rdma_destroy_queue_ib(queue);
	return ret;
}