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
struct iser_tx_desc {int mapped; int /*<<< orphan*/  dma_addr; } ;
struct iser_device {int /*<<< orphan*/  ib_device; } ;
struct TYPE_3__ {struct iser_device* device; } ;
struct iser_conn {TYPE_1__ ib_conn; } ;
struct iscsi_task {int /*<<< orphan*/  sc; TYPE_2__* conn; struct iscsi_iser_task* dd_data; } ;
struct iscsi_iser_task {scalar_t__ status; struct iser_tx_desc desc; } ;
struct TYPE_4__ {struct iser_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 scalar_t__ ISER_TASK_STATUS_COMPLETED ; 
 scalar_t__ ISER_TASK_STATUS_STARTED ; 
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_task_rdma_finalize (struct iscsi_iser_task*) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void iscsi_iser_cleanup_task(struct iscsi_task *task)
{
	struct iscsi_iser_task *iser_task = task->dd_data;
	struct iser_tx_desc *tx_desc = &iser_task->desc;
	struct iser_conn *iser_conn = task->conn->dd_data;
	struct iser_device *device = iser_conn->ib_conn.device;

	/* DEVICE_REMOVAL event might have already released the device */
	if (!device)
		return;

	if (likely(tx_desc->mapped)) {
		ib_dma_unmap_single(device->ib_device, tx_desc->dma_addr,
				    ISER_HEADERS_LEN, DMA_TO_DEVICE);
		tx_desc->mapped = false;
	}

	/* mgmt tasks do not need special cleanup */
	if (!task->sc)
		return;

	if (iser_task->status == ISER_TASK_STATUS_STARTED) {
		iser_task->status = ISER_TASK_STATUS_COMPLETED;
		iser_task_rdma_finalize(iser_task);
	}
}