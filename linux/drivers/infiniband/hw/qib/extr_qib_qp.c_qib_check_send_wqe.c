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
struct rvt_swqe {int length; } ;
struct TYPE_2__ {int qp_type; } ;
struct rvt_qp {int pmtu; TYPE_1__ ibqp; } ;
struct rvt_ah {int log_pmtu; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 struct rvt_ah* rvt_get_swqe_ah (struct rvt_swqe*) ; 

int qib_check_send_wqe(struct rvt_qp *qp,
		       struct rvt_swqe *wqe, bool *call_send)
{
	struct rvt_ah *ah;

	switch (qp->ibqp.qp_type) {
	case IB_QPT_RC:
	case IB_QPT_UC:
		if (wqe->length > 0x80000000U)
			return -EINVAL;
		if (wqe->length > qp->pmtu)
			*call_send = false;
		break;
	case IB_QPT_SMI:
	case IB_QPT_GSI:
	case IB_QPT_UD:
		ah = rvt_get_swqe_ah(wqe);
		if (wqe->length > (1 << ah->log_pmtu))
			return -EINVAL;
		/* progress hint */
		*call_send = true;
		break;
	default:
		break;
	}
	return 0;
}