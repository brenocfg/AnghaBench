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
struct ib_send_wr {int /*<<< orphan*/  opcode; int /*<<< orphan*/ * next; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  num_sge; int /*<<< orphan*/  sg_list; int /*<<< orphan*/ * wr_cqe; } ;
struct TYPE_4__ {struct ib_send_wr wr; } ;
struct iser_tx_desc {TYPE_2__ reg_wr; struct ib_send_wr inv_wr; int /*<<< orphan*/  num_sge; int /*<<< orphan*/  tx_sg; int /*<<< orphan*/  cqe; int /*<<< orphan*/  dma_addr; struct ib_send_wr send_wr; } ;
struct ib_conn {int /*<<< orphan*/  qp; TYPE_1__* device; } ;
struct TYPE_3__ {int /*<<< orphan*/  ib_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iser_err (char*,int,int /*<<< orphan*/ ) ; 

int iser_post_send(struct ib_conn *ib_conn, struct iser_tx_desc *tx_desc,
		   bool signal)
{
	struct ib_send_wr *wr = &tx_desc->send_wr;
	struct ib_send_wr *first_wr;
	int ib_ret;

	ib_dma_sync_single_for_device(ib_conn->device->ib_device,
				      tx_desc->dma_addr, ISER_HEADERS_LEN,
				      DMA_TO_DEVICE);

	wr->next = NULL;
	wr->wr_cqe = &tx_desc->cqe;
	wr->sg_list = tx_desc->tx_sg;
	wr->num_sge = tx_desc->num_sge;
	wr->opcode = IB_WR_SEND;
	wr->send_flags = signal ? IB_SEND_SIGNALED : 0;

	if (tx_desc->inv_wr.next)
		first_wr = &tx_desc->inv_wr;
	else if (tx_desc->reg_wr.wr.next)
		first_wr = &tx_desc->reg_wr.wr;
	else
		first_wr = wr;

	ib_ret = ib_post_send(ib_conn->qp, first_wr, NULL);
	if (ib_ret)
		iser_err("ib_post_send failed, ret:%d opcode:%d\n",
			 ib_ret, wr->opcode);

	return ib_ret;
}