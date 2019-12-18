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
struct TYPE_2__ {scalar_t__ qp_type; int /*<<< orphan*/  device; } ;
struct rvt_qp {int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_hdrwords; int /*<<< orphan*/  s_cur_size; int /*<<< orphan*/  s_cur_sge; int /*<<< orphan*/  s_flags; TYPE_1__ ibqp; int /*<<< orphan*/  remote_ah_attr; int /*<<< orphan*/  port_num; struct qib_qp_priv* priv; } ;
struct qib_qp_priv {int /*<<< orphan*/  s_hdr; } ;
struct qib_pportdata {int lmc; int lid; } ;
struct qib_ibport {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 int /*<<< orphan*/  RVT_S_BUSY ; 
 struct qib_pportdata* ppd_from_ibp (struct qib_ibport*) ; 
 int qib_make_rc_req (struct rvt_qp*,unsigned long*) ; 
 int qib_make_uc_req (struct rvt_qp*,unsigned long*) ; 
 int qib_make_ud_req (struct rvt_qp*,unsigned long*) ; 
 int /*<<< orphan*/  qib_send_ok (struct rvt_qp*) ; 
 scalar_t__ qib_verbs_send (struct rvt_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_ah_get_dlid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvt_ruc_loopback (struct rvt_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qib_do_send(struct rvt_qp *qp)
{
	struct qib_qp_priv *priv = qp->priv;
	struct qib_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	struct qib_pportdata *ppd = ppd_from_ibp(ibp);
	int (*make_req)(struct rvt_qp *qp, unsigned long *flags);
	unsigned long flags;

	if ((qp->ibqp.qp_type == IB_QPT_RC ||
	     qp->ibqp.qp_type == IB_QPT_UC) &&
	    (rdma_ah_get_dlid(&qp->remote_ah_attr) &
	     ~((1 << ppd->lmc) - 1)) == ppd->lid) {
		rvt_ruc_loopback(qp);
		return;
	}

	if (qp->ibqp.qp_type == IB_QPT_RC)
		make_req = qib_make_rc_req;
	else if (qp->ibqp.qp_type == IB_QPT_UC)
		make_req = qib_make_uc_req;
	else
		make_req = qib_make_ud_req;

	spin_lock_irqsave(&qp->s_lock, flags);

	/* Return if we are already busy processing a work request. */
	if (!qib_send_ok(qp)) {
		spin_unlock_irqrestore(&qp->s_lock, flags);
		return;
	}

	qp->s_flags |= RVT_S_BUSY;

	do {
		/* Check for a constructed packet to be sent. */
		if (qp->s_hdrwords != 0) {
			spin_unlock_irqrestore(&qp->s_lock, flags);
			/*
			 * If the packet cannot be sent now, return and
			 * the send tasklet will be woken up later.
			 */
			if (qib_verbs_send(qp, priv->s_hdr, qp->s_hdrwords,
					   qp->s_cur_sge, qp->s_cur_size))
				return;
			/* Record that s_hdr is empty. */
			qp->s_hdrwords = 0;
			spin_lock_irqsave(&qp->s_lock, flags);
		}
	} while (make_req(qp, &flags));

	spin_unlock_irqrestore(&qp->s_lock, flags);
}