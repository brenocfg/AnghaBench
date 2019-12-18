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
struct srp_target_port {int /*<<< orphan*/  lkey; } ;
struct srp_rdma_ch {int /*<<< orphan*/  qp; struct srp_target_port* target; } ;
struct TYPE_3__ {int /*<<< orphan*/  done; } ;
struct srp_iu {scalar_t__ num_sge; TYPE_2__* sge; TYPE_1__ cqe; int /*<<< orphan*/  dma; } ;
struct ib_send_wr {scalar_t__ num_sge; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  opcode; TYPE_2__* sg_list; TYPE_1__* wr_cqe; int /*<<< orphan*/ * next; } ;
struct TYPE_4__ {int length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_SEND_SIGNALED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 scalar_t__ SRP_MAX_SGE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_send_done ; 

__attribute__((used)) static int srp_post_send(struct srp_rdma_ch *ch, struct srp_iu *iu, int len)
{
	struct srp_target_port *target = ch->target;
	struct ib_send_wr wr;

	if (WARN_ON_ONCE(iu->num_sge > SRP_MAX_SGE))
		return -EINVAL;

	iu->sge[0].addr   = iu->dma;
	iu->sge[0].length = len;
	iu->sge[0].lkey   = target->lkey;

	iu->cqe.done = srp_send_done;

	wr.next       = NULL;
	wr.wr_cqe     = &iu->cqe;
	wr.sg_list    = &iu->sge[0];
	wr.num_sge    = iu->num_sge;
	wr.opcode     = IB_WR_SEND;
	wr.send_flags = IB_SEND_SIGNALED;

	return ib_post_send(ch->qp, &wr, NULL);
}