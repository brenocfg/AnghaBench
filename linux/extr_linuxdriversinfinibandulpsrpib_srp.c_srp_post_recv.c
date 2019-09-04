#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct srp_target_port {int /*<<< orphan*/  lkey; } ;
struct srp_rdma_ch {int /*<<< orphan*/  qp; struct srp_target_port* target; } ;
struct TYPE_2__ {int /*<<< orphan*/  done; } ;
struct srp_iu {TYPE_1__ cqe; int /*<<< orphan*/  size; int /*<<< orphan*/  dma; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct ib_recv_wr {int num_sge; struct ib_sge* sg_list; TYPE_1__* wr_cqe; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_recv_done ; 

__attribute__((used)) static int srp_post_recv(struct srp_rdma_ch *ch, struct srp_iu *iu)
{
	struct srp_target_port *target = ch->target;
	struct ib_recv_wr wr;
	struct ib_sge list;

	list.addr   = iu->dma;
	list.length = iu->size;
	list.lkey   = target->lkey;

	iu->cqe.done = srp_recv_done;

	wr.next     = NULL;
	wr.wr_cqe   = &iu->cqe;
	wr.sg_list  = &list;
	wr.num_sge  = 1;

	return ib_post_recv(ch->qp, &wr, NULL);
}