#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  done; } ;
struct iser_tx_desc {int num_sge; struct ib_sge* tx_sg; TYPE_1__ cqe; int /*<<< orphan*/  type; } ;
struct iser_login_desc {int /*<<< orphan*/  req_dma; int /*<<< orphan*/  req; } ;
struct iser_device {TYPE_2__* pd; int /*<<< orphan*/  ib_device; } ;
struct TYPE_7__ {struct iser_device* device; } ;
struct iser_conn {TYPE_3__ ib_conn; struct iser_login_desc login_desc; } ;
struct iscsi_task {TYPE_4__* hdr; int /*<<< orphan*/  data_count; int /*<<< orphan*/  data; struct iscsi_iser_task* dd_data; } ;
struct iscsi_iser_task {struct iser_tx_desc desc; } ;
struct iscsi_conn {struct iscsi_task* login_task; struct iser_conn* dd_data; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  opcode; int /*<<< orphan*/  dlength; } ;
struct TYPE_6__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ISCSI_TX_CONTROL ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_create_send_desc (struct iser_conn*,struct iser_tx_desc*) ; 
 int /*<<< orphan*/  iser_ctrl_comp ; 
 int /*<<< orphan*/  iser_dbg (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  iser_err (char*,...) ; 
 int iser_post_recvl (struct iser_conn*) ; 
 int iser_post_rx_bufs (struct iscsi_conn*,TYPE_4__*) ; 
 int iser_post_send (TYPE_3__*,struct iser_tx_desc*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long ntoh24 (int /*<<< orphan*/ ) ; 

int iser_send_control(struct iscsi_conn *conn,
		      struct iscsi_task *task)
{
	struct iser_conn *iser_conn = conn->dd_data;
	struct iscsi_iser_task *iser_task = task->dd_data;
	struct iser_tx_desc *mdesc = &iser_task->desc;
	unsigned long data_seg_len;
	int err = 0;
	struct iser_device *device;

	/* build the tx desc regd header and add it to the tx desc dto */
	mdesc->type = ISCSI_TX_CONTROL;
	mdesc->cqe.done = iser_ctrl_comp;
	iser_create_send_desc(iser_conn, mdesc);

	device = iser_conn->ib_conn.device;

	data_seg_len = ntoh24(task->hdr->dlength);

	if (data_seg_len > 0) {
		struct iser_login_desc *desc = &iser_conn->login_desc;
		struct ib_sge *tx_dsg = &mdesc->tx_sg[1];

		if (task != conn->login_task) {
			iser_err("data present on non login task!!!\n");
			goto send_control_error;
		}

		ib_dma_sync_single_for_cpu(device->ib_device, desc->req_dma,
					   task->data_count, DMA_TO_DEVICE);

		memcpy(desc->req, task->data, task->data_count);

		ib_dma_sync_single_for_device(device->ib_device, desc->req_dma,
					      task->data_count, DMA_TO_DEVICE);

		tx_dsg->addr = desc->req_dma;
		tx_dsg->length = task->data_count;
		tx_dsg->lkey = device->pd->local_dma_lkey;
		mdesc->num_sge = 2;
	}

	if (task == conn->login_task) {
		iser_dbg("op %x dsl %lx, posting login rx buffer\n",
			 task->hdr->opcode, data_seg_len);
		err = iser_post_recvl(iser_conn);
		if (err)
			goto send_control_error;
		err = iser_post_rx_bufs(conn, task->hdr);
		if (err)
			goto send_control_error;
	}

	err = iser_post_send(&iser_conn->ib_conn, mdesc, true);
	if (!err)
		return 0;

send_control_error:
	iser_err("conn %p failed err %d\n",conn, err);
	return err;
}