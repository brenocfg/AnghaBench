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
struct TYPE_4__ {int /*<<< orphan*/  ah; } ;
struct rvt_swqe {int length; TYPE_2__ ud_wr; } ;
struct TYPE_3__ {int qp_type; } ;
struct rvt_qp {TYPE_1__ ibqp; } ;
struct rvt_ah {int log_pmtu; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 struct rvt_ah* ibah_to_rvtah (int /*<<< orphan*/ ) ; 

int qib_check_send_wqe(struct rvt_qp *qp,
		       struct rvt_swqe *wqe)
{
	struct rvt_ah *ah;
	int ret = 0;

	switch (qp->ibqp.qp_type) {
	case IB_QPT_RC:
	case IB_QPT_UC:
		if (wqe->length > 0x80000000U)
			return -EINVAL;
		break;
	case IB_QPT_SMI:
	case IB_QPT_GSI:
	case IB_QPT_UD:
		ah = ibah_to_rvtah(wqe->ud_wr.ah);
		if (wqe->length > (1 << ah->log_pmtu))
			return -EINVAL;
		/* progress hint */
		ret = 1;
		break;
	default:
		break;
	}
	return ret;
}