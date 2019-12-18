#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  qp_type; scalar_t__ srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  max_sge; } ;
struct rvt_qp {int r_psn; int s_next_psn; int s_size; int s_flags; int /*<<< orphan*/  port_num; TYPE_5__ ibqp; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  s_rnr_retry_cnt; int /*<<< orphan*/  s_retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  r_min_rnr_timer; int /*<<< orphan*/  r_max_rd_atomic; int /*<<< orphan*/  s_max_rd_atomic; int /*<<< orphan*/  s_draining; int /*<<< orphan*/  s_alt_pkey_index; int /*<<< orphan*/  s_pkey_index; int /*<<< orphan*/  remote_ah_attr; TYPE_3__ r_rq; int /*<<< orphan*/  s_max_sge; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  s_mig_state; int /*<<< orphan*/  pmtu; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int psn_mask; int reserved_operations; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* mtu_to_path_mtu ) (int /*<<< orphan*/ ) ;} ;
struct rvt_dev_info {TYPE_2__ dparms; TYPE_1__ driver_f; } ;
struct TYPE_9__ {int max_send_wr; int max_recv_wr; scalar_t__ max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  port_num; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  sq_sig_type; TYPE_4__ cap; scalar_t__ srq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  event_handler; } ;
struct ib_qp_attr {int rq_psn; int sq_psn; TYPE_4__ cap; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  port_num; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  sq_draining; scalar_t__ en_sqd_async_notify; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  alt_ah_attr; int /*<<< orphan*/  ah_attr; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  cur_qp_state; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SIGNAL_ALL_WR ; 
 int /*<<< orphan*/  IB_SIGNAL_REQ_WR ; 
 int RVT_S_SIGNAL_REQ_WR ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 struct rvt_qp* ibqp_to_rvtqp (struct ib_qp*) ; 
 int /*<<< orphan*/  rdma_ah_get_port_num (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int rvt_query_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
		 int attr_mask, struct ib_qp_init_attr *init_attr)
{
	struct rvt_qp *qp = ibqp_to_rvtqp(ibqp);
	struct rvt_dev_info *rdi = ib_to_rvt(ibqp->device);

	attr->qp_state = qp->state;
	attr->cur_qp_state = attr->qp_state;
	attr->path_mtu = rdi->driver_f.mtu_to_path_mtu(qp->pmtu);
	attr->path_mig_state = qp->s_mig_state;
	attr->qkey = qp->qkey;
	attr->rq_psn = qp->r_psn & rdi->dparms.psn_mask;
	attr->sq_psn = qp->s_next_psn & rdi->dparms.psn_mask;
	attr->dest_qp_num = qp->remote_qpn;
	attr->qp_access_flags = qp->qp_access_flags;
	attr->cap.max_send_wr = qp->s_size - 1 -
		rdi->dparms.reserved_operations;
	attr->cap.max_recv_wr = qp->ibqp.srq ? 0 : qp->r_rq.size - 1;
	attr->cap.max_send_sge = qp->s_max_sge;
	attr->cap.max_recv_sge = qp->r_rq.max_sge;
	attr->cap.max_inline_data = 0;
	attr->ah_attr = qp->remote_ah_attr;
	attr->alt_ah_attr = qp->alt_ah_attr;
	attr->pkey_index = qp->s_pkey_index;
	attr->alt_pkey_index = qp->s_alt_pkey_index;
	attr->en_sqd_async_notify = 0;
	attr->sq_draining = qp->s_draining;
	attr->max_rd_atomic = qp->s_max_rd_atomic;
	attr->max_dest_rd_atomic = qp->r_max_rd_atomic;
	attr->min_rnr_timer = qp->r_min_rnr_timer;
	attr->port_num = qp->port_num;
	attr->timeout = qp->timeout;
	attr->retry_cnt = qp->s_retry_cnt;
	attr->rnr_retry = qp->s_rnr_retry_cnt;
	attr->alt_port_num =
		rdma_ah_get_port_num(&qp->alt_ah_attr);
	attr->alt_timeout = qp->alt_timeout;

	init_attr->event_handler = qp->ibqp.event_handler;
	init_attr->qp_context = qp->ibqp.qp_context;
	init_attr->send_cq = qp->ibqp.send_cq;
	init_attr->recv_cq = qp->ibqp.recv_cq;
	init_attr->srq = qp->ibqp.srq;
	init_attr->cap = attr->cap;
	if (qp->s_flags & RVT_S_SIGNAL_REQ_WR)
		init_attr->sq_sig_type = IB_SIGNAL_REQ_WR;
	else
		init_attr->sq_sig_type = IB_SIGNAL_ALL_WR;
	init_attr->qp_type = qp->ibqp.qp_type;
	init_attr->port_num = qp->port_num;
	return 0;
}