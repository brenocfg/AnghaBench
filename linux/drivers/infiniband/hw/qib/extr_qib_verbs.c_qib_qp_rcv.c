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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int qp_type; } ;
struct rvt_qp {size_t state; int /*<<< orphan*/  r_lock; TYPE_2__ ibqp; } ;
struct TYPE_4__ {int /*<<< orphan*/  n_pkt_drops; } ;
struct qib_ibport {TYPE_1__ rvp; } ;
struct qib_ctxtdata {TYPE_3__* ppd; } ;
struct ib_header {int dummy; } ;
struct TYPE_6__ {struct qib_ibport ibport_data; } ;

/* Variables and functions */
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 int RVT_PROCESS_RECV_OK ; 
 int /*<<< orphan*/  ib_qib_disable_sma ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/  qib_rc_rcv (struct qib_ctxtdata*,struct ib_header*,int,void*,int /*<<< orphan*/ ,struct rvt_qp*) ; 
 int /*<<< orphan*/  qib_uc_rcv (struct qib_ibport*,struct ib_header*,int,void*,int /*<<< orphan*/ ,struct rvt_qp*) ; 
 int /*<<< orphan*/  qib_ud_rcv (struct qib_ibport*,struct ib_header*,int,void*,int /*<<< orphan*/ ,struct rvt_qp*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qib_qp_rcv(struct qib_ctxtdata *rcd, struct ib_header *hdr,
		       int has_grh, void *data, u32 tlen, struct rvt_qp *qp)
{
	struct qib_ibport *ibp = &rcd->ppd->ibport_data;

	spin_lock(&qp->r_lock);

	/* Check for valid receive state. */
	if (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) {
		ibp->rvp.n_pkt_drops++;
		goto unlock;
	}

	switch (qp->ibqp.qp_type) {
	case IB_QPT_SMI:
	case IB_QPT_GSI:
		if (ib_qib_disable_sma)
			break;
		/* FALLTHROUGH */
	case IB_QPT_UD:
		qib_ud_rcv(ibp, hdr, has_grh, data, tlen, qp);
		break;

	case IB_QPT_RC:
		qib_rc_rcv(rcd, hdr, has_grh, data, tlen, qp);
		break;

	case IB_QPT_UC:
		qib_uc_rcv(ibp, hdr, has_grh, data, tlen, qp);
		break;

	default:
		break;
	}

unlock:
	spin_unlock(&qp->r_lock);
}