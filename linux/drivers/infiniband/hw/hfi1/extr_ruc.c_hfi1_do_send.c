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
struct TYPE_5__ {int qp_type; int /*<<< orphan*/  device; } ;
struct rvt_qp {int timeout_jiffies; int s_flags; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  remote_ah_attr; TYPE_1__ ibqp; int /*<<< orphan*/  port_num; struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {int s_flags; int /*<<< orphan*/  s_iowait; TYPE_2__* s_sde; } ;
struct hfi1_pkt_state {int in_thread; int timeout_int; int pkts_sent; int /*<<< orphan*/  flags; scalar_t__ s_txreq; int /*<<< orphan*/  wait; TYPE_4__* ppd; int /*<<< orphan*/  cpu; scalar_t__ timeout; int /*<<< orphan*/  ibp; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int lmc; int lid; TYPE_3__* dd; } ;
struct TYPE_7__ {int /*<<< orphan*/  node; } ;
struct TYPE_6__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int HFI1_S_ANY_WAIT_IO ; 
 int HFI1_S_TID_BUSY_SET ; 
#define  IB_QPT_RC 129 
#define  IB_QPT_UC 128 
 int /*<<< orphan*/  IOWAIT_PENDING_IB ; 
 int RVT_S_BUSY ; 
 void* SEND_RESCHED_TIMEOUT ; 
 int /*<<< orphan*/  cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of_node (int /*<<< orphan*/ ) ; 
 scalar_t__ get_waiting_verbs_txreq (int /*<<< orphan*/ ) ; 
 int hfi1_make_rc_req (struct rvt_qp*,struct hfi1_pkt_state*) ; 
 int hfi1_make_uc_req (struct rvt_qp*,struct hfi1_pkt_state*) ; 
 int hfi1_make_ud_req (struct rvt_qp*,struct hfi1_pkt_state*) ; 
 scalar_t__ hfi1_schedule_send_yield (struct rvt_qp*,struct hfi1_pkt_state*,int) ; 
 int /*<<< orphan*/  hfi1_send_ok (struct rvt_qp*) ; 
 scalar_t__ hfi1_verbs_send (struct rvt_qp*,struct hfi1_pkt_state*) ; 
 int /*<<< orphan*/  iowait_get_ib_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowait_set_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowait_starve_clear (int,int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  loopback ; 
 TYPE_4__* ppd_from_ibp (int /*<<< orphan*/ ) ; 
 int rdma_ah_get_dlid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_ruc_loopback (struct rvt_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_idev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_rc_do_send (struct rvt_qp*,int) ; 

void hfi1_do_send(struct rvt_qp *qp, bool in_thread)
{
	struct hfi1_pkt_state ps;
	struct hfi1_qp_priv *priv = qp->priv;
	int (*make_req)(struct rvt_qp *qp, struct hfi1_pkt_state *ps);

	ps.dev = to_idev(qp->ibqp.device);
	ps.ibp = to_iport(qp->ibqp.device, qp->port_num);
	ps.ppd = ppd_from_ibp(ps.ibp);
	ps.in_thread = in_thread;
	ps.wait = iowait_get_ib_work(&priv->s_iowait);

	trace_hfi1_rc_do_send(qp, in_thread);

	switch (qp->ibqp.qp_type) {
	case IB_QPT_RC:
		if (!loopback && ((rdma_ah_get_dlid(&qp->remote_ah_attr) &
				   ~((1 << ps.ppd->lmc) - 1)) ==
				  ps.ppd->lid)) {
			rvt_ruc_loopback(qp);
			return;
		}
		make_req = hfi1_make_rc_req;
		ps.timeout_int = qp->timeout_jiffies;
		break;
	case IB_QPT_UC:
		if (!loopback && ((rdma_ah_get_dlid(&qp->remote_ah_attr) &
				   ~((1 << ps.ppd->lmc) - 1)) ==
				  ps.ppd->lid)) {
			rvt_ruc_loopback(qp);
			return;
		}
		make_req = hfi1_make_uc_req;
		ps.timeout_int = SEND_RESCHED_TIMEOUT;
		break;
	default:
		make_req = hfi1_make_ud_req;
		ps.timeout_int = SEND_RESCHED_TIMEOUT;
	}

	spin_lock_irqsave(&qp->s_lock, ps.flags);

	/* Return if we are already busy processing a work request. */
	if (!hfi1_send_ok(qp)) {
		if (qp->s_flags & HFI1_S_ANY_WAIT_IO)
			iowait_set_flag(&priv->s_iowait, IOWAIT_PENDING_IB);
		spin_unlock_irqrestore(&qp->s_lock, ps.flags);
		return;
	}

	qp->s_flags |= RVT_S_BUSY;

	ps.timeout_int = ps.timeout_int / 8;
	ps.timeout = jiffies + ps.timeout_int;
	ps.cpu = priv->s_sde ? priv->s_sde->cpu :
			cpumask_first(cpumask_of_node(ps.ppd->dd->node));
	ps.pkts_sent = false;

	/* insure a pre-built packet is handled  */
	ps.s_txreq = get_waiting_verbs_txreq(ps.wait);
	do {
		/* Check for a constructed packet to be sent. */
		if (ps.s_txreq) {
			if (priv->s_flags & HFI1_S_TID_BUSY_SET)
				qp->s_flags |= RVT_S_BUSY;
			spin_unlock_irqrestore(&qp->s_lock, ps.flags);
			/*
			 * If the packet cannot be sent now, return and
			 * the send engine will be woken up later.
			 */
			if (hfi1_verbs_send(qp, &ps))
				return;

			/* allow other tasks to run */
			if (hfi1_schedule_send_yield(qp, &ps, false))
				return;

			spin_lock_irqsave(&qp->s_lock, ps.flags);
		}
	} while (make_req(qp, &ps));
	iowait_starve_clear(ps.pkts_sent, &priv->s_iowait);
	spin_unlock_irqrestore(&qp->s_lock, ps.flags);
}