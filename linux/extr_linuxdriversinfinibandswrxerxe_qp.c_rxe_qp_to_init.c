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
struct TYPE_8__ {int /*<<< orphan*/  qp_type; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;
struct TYPE_7__ {int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_inline; int /*<<< orphan*/  max_sge; int /*<<< orphan*/  max_wr; } ;
struct rxe_qp {TYPE_4__ ibqp; int /*<<< orphan*/  sq_sig_type; TYPE_3__ rq; int /*<<< orphan*/  srq; TYPE_1__ sq; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_init_attr {int port_num; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_type; TYPE_2__ cap; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;

/* Variables and functions */

int rxe_qp_to_init(struct rxe_qp *qp, struct ib_qp_init_attr *init)
{
	init->event_handler		= qp->ibqp.event_handler;
	init->qp_context		= qp->ibqp.qp_context;
	init->send_cq			= qp->ibqp.send_cq;
	init->recv_cq			= qp->ibqp.recv_cq;
	init->srq			= qp->ibqp.srq;

	init->cap.max_send_wr		= qp->sq.max_wr;
	init->cap.max_send_sge		= qp->sq.max_sge;
	init->cap.max_inline_data	= qp->sq.max_inline;

	if (!qp->srq) {
		init->cap.max_recv_wr		= qp->rq.max_wr;
		init->cap.max_recv_sge		= qp->rq.max_sge;
	}

	init->sq_sig_type		= qp->sq_sig_type;

	init->qp_type			= qp->ibqp.qp_type;
	init->port_num			= 1;

	return 0;
}