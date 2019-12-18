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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  done; } ;
struct srp_request {TYPE_2__ reg_cqe; } ;
struct srp_rdma_ch {int /*<<< orphan*/  qp; } ;
struct TYPE_3__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct ib_send_wr {TYPE_2__* wr_cqe; TYPE_1__ ex; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  num_sge; int /*<<< orphan*/ * next; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_LOCAL_INV ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_inv_rkey_err_done ; 

__attribute__((used)) static int srp_inv_rkey(struct srp_request *req, struct srp_rdma_ch *ch,
		u32 rkey)
{
	struct ib_send_wr wr = {
		.opcode		    = IB_WR_LOCAL_INV,
		.next		    = NULL,
		.num_sge	    = 0,
		.send_flags	    = 0,
		.ex.invalidate_rkey = rkey,
	};

	wr.wr_cqe = &req->reg_cqe;
	req->reg_cqe.done = srp_inv_rkey_err_done;
	return ib_post_send(ch->qp, &wr, NULL);
}