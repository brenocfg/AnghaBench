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
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct tid_rdma_params {unsigned long timeout; int /*<<< orphan*/  max_len; } ;
struct rvt_qp {struct hfi1_qp_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  remote; struct tid_rdma_params local; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct hfi1_qp_priv {scalar_t__ timeout_shift; TYPE_2__ tid_rdma; scalar_t__ pkts_ps; int /*<<< orphan*/  tid_timer_timeout_jiffies; TYPE_1__ opfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HFI1_CAP_IS_KSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TID_RDMA ; 
 scalar_t__ ilog2 (scalar_t__) ; 
 int /*<<< orphan*/  kfree_rcu (struct tid_rdma_params*,int /*<<< orphan*/ ) ; 
 struct tid_rdma_params* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct tid_rdma_params*) ; 
 struct tid_rdma_params* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 scalar_t__ rvt_div_mtu (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tid_rdma_opfn_decode (struct tid_rdma_params*,int) ; 
 int /*<<< orphan*/  trace_hfi1_opfn_param (struct rvt_qp*,int,struct tid_rdma_params*) ; 
 int /*<<< orphan*/  usecs_to_jiffies (unsigned long) ; 

bool tid_rdma_conn_reply(struct rvt_qp *qp, u64 data)
{
	struct hfi1_qp_priv *priv = qp->priv;
	struct tid_rdma_params *remote, *old;
	bool ret = true;

	old = rcu_dereference_protected(priv->tid_rdma.remote,
					lockdep_is_held(&priv->opfn.lock));
	data &= ~0xfULL;
	/*
	 * If data passed in is zero, return true so as not to continue the
	 * negotiation process
	 */
	if (!data || !HFI1_CAP_IS_KSET(TID_RDMA))
		goto null;
	/*
	 * If kzalloc fails, return false. This will result in:
	 * * at the requester a new OPFN request being generated to retry
	 *   the negotiation
	 * * at the responder, 0 being returned to the requester so as to
	 *   disable TID RDMA at both the requester and the responder
	 */
	remote = kzalloc(sizeof(*remote), GFP_ATOMIC);
	if (!remote) {
		ret = false;
		goto null;
	}

	tid_rdma_opfn_decode(remote, data);
	priv->tid_timer_timeout_jiffies =
		usecs_to_jiffies((((4096UL * (1UL << remote->timeout)) /
				   1000UL) << 3) * 7);
	trace_hfi1_opfn_param(qp, 0, &priv->tid_rdma.local);
	trace_hfi1_opfn_param(qp, 1, remote);
	rcu_assign_pointer(priv->tid_rdma.remote, remote);
	/*
	 * A TID RDMA READ request's segment size is not equal to
	 * remote->max_len only when the request's data length is smaller
	 * than remote->max_len. In that case, there will be only one segment.
	 * Therefore, when priv->pkts_ps is used to calculate req->cur_seg
	 * during retry, it will lead to req->cur_seg = 0, which is exactly
	 * what is expected.
	 */
	priv->pkts_ps = (u16)rvt_div_mtu(qp, remote->max_len);
	priv->timeout_shift = ilog2(priv->pkts_ps - 1) + 1;
	goto free;
null:
	RCU_INIT_POINTER(priv->tid_rdma.remote, NULL);
	priv->timeout_shift = 0;
free:
	if (old)
		kfree_rcu(old, rcu_head);
	return ret;
}