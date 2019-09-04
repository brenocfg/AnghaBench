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
struct isert_conn {int /*<<< orphan*/  qp; TYPE_2__* cm_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  done; } ;
struct iser_tx_desc {int /*<<< orphan*/  num_sge; int /*<<< orphan*/  tx_sg; TYPE_1__ tx_cqe; int /*<<< orphan*/  dma_addr; } ;
struct ib_send_wr {int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; int /*<<< orphan*/  num_sge; int /*<<< orphan*/  sg_list; TYPE_1__* wr_cqe; int /*<<< orphan*/ * next; } ;
struct ib_device {int dummy; } ;
struct TYPE_4__ {struct ib_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  ISER_HEADERS_LEN ; 
 int /*<<< orphan*/  ib_dma_sync_single_for_device (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isert_err (char*,int) ; 
 int /*<<< orphan*/  isert_login_send_done ; 

__attribute__((used)) static int
isert_login_post_send(struct isert_conn *isert_conn, struct iser_tx_desc *tx_desc)
{
	struct ib_device *ib_dev = isert_conn->cm_id->device;
	struct ib_send_wr send_wr;
	int ret;

	ib_dma_sync_single_for_device(ib_dev, tx_desc->dma_addr,
				      ISER_HEADERS_LEN, DMA_TO_DEVICE);

	tx_desc->tx_cqe.done = isert_login_send_done;

	send_wr.next	= NULL;
	send_wr.wr_cqe	= &tx_desc->tx_cqe;
	send_wr.sg_list	= tx_desc->tx_sg;
	send_wr.num_sge	= tx_desc->num_sge;
	send_wr.opcode	= IB_WR_SEND;
	send_wr.send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(isert_conn->qp, &send_wr, NULL);
	if (ret)
		isert_err("ib_post_send() failed, ret: %d\n", ret);

	return ret;
}