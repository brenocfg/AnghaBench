#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* max_recv_sge; void* max_send_sge; int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_wr; int /*<<< orphan*/  max_send_wr; } ;
struct ib_qp_init_attr {int port_num; TYPE_3__ cap; int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;
struct ib_qp_attr {int port_num; TYPE_3__ cap; scalar_t__ qp_access_flags; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  cur_qp_state; } ;
struct ib_qp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rq_size; int /*<<< orphan*/  sq_size; } ;
struct i40iw_sc_qp {TYPE_1__ qp_uk; } ;
struct TYPE_5__ {int /*<<< orphan*/  srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;
struct i40iw_qp {TYPE_2__ ibqp; int /*<<< orphan*/  ibqp_state; struct i40iw_sc_qp sc_qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40IW_MAX_INLINE_DATA_SIZE ; 
 void* I40IW_MAX_WQ_FRAGMENT_COUNT ; 
 struct i40iw_qp* to_iwqp (struct ib_qp*) ; 

__attribute__((used)) static int i40iw_query_qp(struct ib_qp *ibqp,
			  struct ib_qp_attr *attr,
			  int attr_mask,
			  struct ib_qp_init_attr *init_attr)
{
	struct i40iw_qp *iwqp = to_iwqp(ibqp);
	struct i40iw_sc_qp *qp = &iwqp->sc_qp;

	attr->qp_state = iwqp->ibqp_state;
	attr->cur_qp_state = attr->qp_state;
	attr->qp_access_flags = 0;
	attr->cap.max_send_wr = qp->qp_uk.sq_size;
	attr->cap.max_recv_wr = qp->qp_uk.rq_size;
	attr->cap.max_inline_data = I40IW_MAX_INLINE_DATA_SIZE;
	attr->cap.max_send_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;
	attr->cap.max_recv_sge = I40IW_MAX_WQ_FRAGMENT_COUNT;
	attr->port_num = 1;
	init_attr->event_handler = iwqp->ibqp.event_handler;
	init_attr->qp_context = iwqp->ibqp.qp_context;
	init_attr->send_cq = iwqp->ibqp.send_cq;
	init_attr->recv_cq = iwqp->ibqp.recv_cq;
	init_attr->srq = iwqp->ibqp.srq;
	init_attr->cap = attr->cap;
	init_attr->port_num = 1;
	return 0;
}