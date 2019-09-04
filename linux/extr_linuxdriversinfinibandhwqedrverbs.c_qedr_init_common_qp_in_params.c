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
struct qedr_qp {TYPE_2__* srq; } ;
struct qedr_pd {TYPE_1__* uctx; int /*<<< orphan*/  pd_id; } ;
struct qedr_dev {int /*<<< orphan*/  dpi; } ;
struct qed_rdma_create_qp_in_params {int signal_all; int fmr_and_reserved_lkey; int use_srq; scalar_t__ srq_id; int /*<<< orphan*/  rq_cq_id; scalar_t__ stats_queue; int /*<<< orphan*/  sq_cq_id; int /*<<< orphan*/  dpi; int /*<<< orphan*/  pd; int /*<<< orphan*/  qp_handle_async_hi; int /*<<< orphan*/  qp_handle_async_lo; } ;
struct ib_qp_init_attr {scalar_t__ sq_sig_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct TYPE_6__ {int /*<<< orphan*/  icid; } ;
struct TYPE_5__ {scalar_t__ srq_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  dpi; } ;

/* Variables and functions */
 scalar_t__ IB_SIGNAL_ALL_WR ; 
 TYPE_3__* get_qedr_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (uintptr_t) ; 
 int /*<<< orphan*/  upper_32_bits (uintptr_t) ; 

__attribute__((used)) static inline void
qedr_init_common_qp_in_params(struct qedr_dev *dev,
			      struct qedr_pd *pd,
			      struct qedr_qp *qp,
			      struct ib_qp_init_attr *attrs,
			      bool fmr_and_reserved_lkey,
			      struct qed_rdma_create_qp_in_params *params)
{
	/* QP handle to be written in an async event */
	params->qp_handle_async_lo = lower_32_bits((uintptr_t) qp);
	params->qp_handle_async_hi = upper_32_bits((uintptr_t) qp);

	params->signal_all = (attrs->sq_sig_type == IB_SIGNAL_ALL_WR);
	params->fmr_and_reserved_lkey = fmr_and_reserved_lkey;
	params->pd = pd->pd_id;
	params->dpi = pd->uctx ? pd->uctx->dpi : dev->dpi;
	params->sq_cq_id = get_qedr_cq(attrs->send_cq)->icid;
	params->stats_queue = 0;
	params->srq_id = 0;
	params->use_srq = false;

	if (!qp->srq) {
		params->rq_cq_id = get_qedr_cq(attrs->recv_cq)->icid;

	} else {
		params->rq_cq_id = get_qedr_cq(attrs->recv_cq)->icid;
		params->srq_id = qp->srq->srq_id;
		params->use_srq = true;
	}
}