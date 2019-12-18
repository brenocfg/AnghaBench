#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_11__ {int /*<<< orphan*/ * next; } ;
struct TYPE_12__ {TYPE_4__ wr; } ;
struct TYPE_10__ {int /*<<< orphan*/ * next; } ;
struct iser_tx_desc {int mapped; TYPE_6__* tx_sg; int /*<<< orphan*/  dma_addr; TYPE_5__ reg_wr; TYPE_3__ inv_wr; } ;
struct iser_device {TYPE_7__* pd; int /*<<< orphan*/  ib_device; } ;
struct TYPE_9__ {struct iser_device* device; } ;
struct iser_conn {scalar_t__ state; int /*<<< orphan*/  state_mutex; TYPE_2__ ib_conn; } ;
struct iscsi_task {int /*<<< orphan*/  sc; struct iscsi_iser_task* dd_data; TYPE_1__* conn; } ;
struct iscsi_iser_task {struct iser_conn* iser_conn; } ;
struct TYPE_14__ {int /*<<< orphan*/  local_dma_lkey; } ;
struct TYPE_13__ {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {struct iser_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ ISER_CONN_UP ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int const) ; 

int
iser_initialize_task_headers(struct iscsi_task *task,
			     struct iser_tx_desc *tx_desc)
{
	struct iser_conn *iser_conn = task->conn->dd_data;
	struct iser_device *device = iser_conn->ib_conn.device;
	struct iscsi_iser_task *iser_task = task->dd_data;
	u64 dma_addr;
	const bool mgmt_task = !task->sc && !in_interrupt();
	int ret = 0;

	if (unlikely(mgmt_task))
		mutex_lock(&iser_conn->state_mutex);

	if (unlikely(iser_conn->state != ISER_CONN_UP)) {
		ret = -ENODEV;
		goto out;
	}

	dma_addr = ib_dma_map_single(device->ib_device, (void *)tx_desc,
				ISER_HEADERS_LEN, DMA_TO_DEVICE);
	if (ib_dma_mapping_error(device->ib_device, dma_addr)) {
		ret = -ENOMEM;
		goto out;
	}

	tx_desc->inv_wr.next = NULL;
	tx_desc->reg_wr.wr.next = NULL;
	tx_desc->mapped = true;
	tx_desc->dma_addr = dma_addr;
	tx_desc->tx_sg[0].addr   = tx_desc->dma_addr;
	tx_desc->tx_sg[0].length = ISER_HEADERS_LEN;
	tx_desc->tx_sg[0].lkey   = device->pd->local_dma_lkey;

	iser_task->iser_conn = iser_conn;
out:
	if (unlikely(mgmt_task))
		mutex_unlock(&iser_conn->state_mutex);

	return ret;
}