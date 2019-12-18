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
struct rvt_swqe {int length; } ;
struct TYPE_3__ {int qp_type; int /*<<< orphan*/  device; } ;
struct rvt_qp {int pmtu; TYPE_1__ ibqp; int /*<<< orphan*/  port_num; } ;
struct rvt_ah {int log_pmtu; int /*<<< orphan*/  attr; } ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_ibport {int* sl_to_sc; } ;
struct hfi1_devdata {TYPE_2__* vld; } ;
struct TYPE_4__ {int mtu; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 struct hfi1_devdata* dd_from_ppd (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  hfi1_setup_tid_rdma_wqe (struct rvt_qp*,struct rvt_swqe*) ; 
 scalar_t__ piothreshold ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 size_t rdma_ah_get_sl (int /*<<< orphan*/ *) ; 
 struct rvt_ah* rvt_get_swqe_ah (struct rvt_swqe*) ; 
 struct hfi1_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hfi1_setup_wqe(struct rvt_qp *qp, struct rvt_swqe *wqe, bool *call_send)
{
	struct hfi1_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	struct rvt_ah *ah;
	struct hfi1_pportdata *ppd;
	struct hfi1_devdata *dd;

	switch (qp->ibqp.qp_type) {
	case IB_QPT_RC:
		hfi1_setup_tid_rdma_wqe(qp, wqe);
		/* fall through */
	case IB_QPT_UC:
		if (wqe->length > 0x80000000U)
			return -EINVAL;
		if (wqe->length > qp->pmtu)
			*call_send = false;
		break;
	case IB_QPT_SMI:
		/*
		 * SM packets should exclusively use VL15 and their SL is
		 * ignored (IBTA v1.3, Section 3.5.8.2). Therefore, when ah
		 * is created, SL is 0 in most cases and as a result some
		 * fields (vl and pmtu) in ah may not be set correctly,
		 * depending on the SL2SC and SC2VL tables at the time.
		 */
		ppd = ppd_from_ibp(ibp);
		dd = dd_from_ppd(ppd);
		if (wqe->length > dd->vld[15].mtu)
			return -EINVAL;
		break;
	case IB_QPT_GSI:
	case IB_QPT_UD:
		ah = rvt_get_swqe_ah(wqe);
		if (wqe->length > (1 << ah->log_pmtu))
			return -EINVAL;
		if (ibp->sl_to_sc[rdma_ah_get_sl(&ah->attr)] == 0xf)
			return -EINVAL;
	default:
		break;
	}

	/*
	 * System latency between send and schedule is large enough that
	 * forcing call_send to true for piothreshold packets is necessary.
	 */
	if (wqe->length <= piothreshold)
		*call_send = true;
	return 0;
}