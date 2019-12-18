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
struct TYPE_3__ {int /*<<< orphan*/  done; } ;
struct TYPE_4__ {TYPE_1__ cqe; scalar_t__ offset; scalar_t__ dma; } ;
struct srpt_recv_ioctx {TYPE_2__ ioctx; } ;
struct srpt_rdma_ch {int /*<<< orphan*/  qp; } ;
struct srpt_device {int /*<<< orphan*/  srq; scalar_t__ use_srq; int /*<<< orphan*/  lkey; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; scalar_t__ addr; } ;
struct ib_recv_wr {int num_sge; struct ib_sge* sg_list; int /*<<< orphan*/ * next; TYPE_1__* wr_cqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int ib_post_srq_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_max_req_size ; 
 int /*<<< orphan*/  srpt_recv_done ; 

__attribute__((used)) static int srpt_post_recv(struct srpt_device *sdev, struct srpt_rdma_ch *ch,
			  struct srpt_recv_ioctx *ioctx)
{
	struct ib_sge list;
	struct ib_recv_wr wr;

	BUG_ON(!sdev);
	list.addr = ioctx->ioctx.dma + ioctx->ioctx.offset;
	list.length = srp_max_req_size;
	list.lkey = sdev->lkey;

	ioctx->ioctx.cqe.done = srpt_recv_done;
	wr.wr_cqe = &ioctx->ioctx.cqe;
	wr.next = NULL;
	wr.sg_list = &list;
	wr.num_sge = 1;

	if (sdev->use_srq)
		return ib_post_srq_recv(sdev->srq, &wr, NULL);
	else
		return ib_post_recv(ch->qp, &wr, NULL);
}