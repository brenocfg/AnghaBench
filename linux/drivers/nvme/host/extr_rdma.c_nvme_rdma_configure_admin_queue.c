#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * data; } ;
struct TYPE_16__ {int max_segments; int max_hw_sectors; void* admin_tagset; void* fabrics_q; void* admin_q; int /*<<< orphan*/  numa_node; } ;
struct nvme_rdma_ctrl {int max_fr_pages; TYPE_2__* queues; TYPE_6__ async_event_sqe; TYPE_1__* device; TYPE_7__ ctrl; int /*<<< orphan*/  admin_tag_set; } ;
struct nvme_command {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  dma_device; } ;
struct TYPE_13__ {TYPE_1__* device; } ;
struct TYPE_12__ {TYPE_3__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  NVME_AQ_DEPTH ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  SZ_4K ; 
 int /*<<< orphan*/  blk_cleanup_queue (void*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (void*) ; 
 void* blk_mq_init_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_unquiesce_queue (void*) ; 
 int /*<<< orphan*/  dev_to_node (int /*<<< orphan*/ ) ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int nvme_enable_ctrl (TYPE_7__*) ; 
 int nvme_init_identify (TYPE_7__*) ; 
 int nvme_rdma_alloc_qe (TYPE_3__*,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int nvme_rdma_alloc_queue (struct nvme_rdma_ctrl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* nvme_rdma_alloc_tagset (TYPE_7__*,int) ; 
 int /*<<< orphan*/  nvme_rdma_free_qe (TYPE_3__*,TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_rdma_free_queue (TYPE_2__*) ; 
 int nvme_rdma_get_max_fr_pages (TYPE_3__*) ; 
 int nvme_rdma_start_queue (struct nvme_rdma_ctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_rdma_stop_queue (TYPE_2__*) ; 

__attribute__((used)) static int nvme_rdma_configure_admin_queue(struct nvme_rdma_ctrl *ctrl,
		bool new)
{
	int error;

	error = nvme_rdma_alloc_queue(ctrl, 0, NVME_AQ_DEPTH);
	if (error)
		return error;

	ctrl->device = ctrl->queues[0].device;
	ctrl->ctrl.numa_node = dev_to_node(ctrl->device->dev->dma_device);

	ctrl->max_fr_pages = nvme_rdma_get_max_fr_pages(ctrl->device->dev);

	/*
	 * Bind the async event SQE DMA mapping to the admin queue lifetime.
	 * It's safe, since any chage in the underlying RDMA device will issue
	 * error recovery and queue re-creation.
	 */
	error = nvme_rdma_alloc_qe(ctrl->device->dev, &ctrl->async_event_sqe,
			sizeof(struct nvme_command), DMA_TO_DEVICE);
	if (error)
		goto out_free_queue;

	if (new) {
		ctrl->ctrl.admin_tagset = nvme_rdma_alloc_tagset(&ctrl->ctrl, true);
		if (IS_ERR(ctrl->ctrl.admin_tagset)) {
			error = PTR_ERR(ctrl->ctrl.admin_tagset);
			goto out_free_async_qe;
		}

		ctrl->ctrl.fabrics_q = blk_mq_init_queue(&ctrl->admin_tag_set);
		if (IS_ERR(ctrl->ctrl.fabrics_q)) {
			error = PTR_ERR(ctrl->ctrl.fabrics_q);
			goto out_free_tagset;
		}

		ctrl->ctrl.admin_q = blk_mq_init_queue(&ctrl->admin_tag_set);
		if (IS_ERR(ctrl->ctrl.admin_q)) {
			error = PTR_ERR(ctrl->ctrl.admin_q);
			goto out_cleanup_fabrics_q;
		}
	}

	error = nvme_rdma_start_queue(ctrl, 0);
	if (error)
		goto out_cleanup_queue;

	error = nvme_enable_ctrl(&ctrl->ctrl);
	if (error)
		goto out_stop_queue;

	ctrl->ctrl.max_segments = ctrl->max_fr_pages;
	ctrl->ctrl.max_hw_sectors = ctrl->max_fr_pages << (ilog2(SZ_4K) - 9);

	blk_mq_unquiesce_queue(ctrl->ctrl.admin_q);

	error = nvme_init_identify(&ctrl->ctrl);
	if (error)
		goto out_stop_queue;

	return 0;

out_stop_queue:
	nvme_rdma_stop_queue(&ctrl->queues[0]);
out_cleanup_queue:
	if (new)
		blk_cleanup_queue(ctrl->ctrl.admin_q);
out_cleanup_fabrics_q:
	if (new)
		blk_cleanup_queue(ctrl->ctrl.fabrics_q);
out_free_tagset:
	if (new)
		blk_mq_free_tag_set(ctrl->ctrl.admin_tagset);
out_free_async_qe:
	nvme_rdma_free_qe(ctrl->device->dev, &ctrl->async_event_sqe,
		sizeof(struct nvme_command), DMA_TO_DEVICE);
	ctrl->async_event_sqe.data = NULL;
out_free_queue:
	nvme_rdma_free_queue(&ctrl->queues[0]);
	return error;
}