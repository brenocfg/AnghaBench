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
struct TYPE_3__ {int /*<<< orphan*/  ah; } ;
struct rvt_swqe {int length; TYPE_1__ ud_wr; } ;
struct TYPE_4__ {int qp_type; int /*<<< orphan*/  device; } ;
struct rvt_qp {TYPE_2__ ibqp; int /*<<< orphan*/  port_num; } ;
struct rvt_ah {int log_pmtu; int /*<<< orphan*/  attr; } ;
struct hfi1_ibport {int* sl_to_sc; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 struct rvt_ah* ibah_to_rvtah (int /*<<< orphan*/ ) ; 
 scalar_t__ piothreshold ; 
 size_t rdma_ah_get_sl (int /*<<< orphan*/ *) ; 
 struct hfi1_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hfi1_check_send_wqe(struct rvt_qp *qp,
			struct rvt_swqe *wqe)
{
	struct hfi1_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	struct rvt_ah *ah;

	switch (qp->ibqp.qp_type) {
	case IB_QPT_RC:
	case IB_QPT_UC:
		if (wqe->length > 0x80000000U)
			return -EINVAL;
		break;
	case IB_QPT_SMI:
		ah = ibah_to_rvtah(wqe->ud_wr.ah);
		if (wqe->length > (1 << ah->log_pmtu))
			return -EINVAL;
		break;
	case IB_QPT_GSI:
	case IB_QPT_UD:
		ah = ibah_to_rvtah(wqe->ud_wr.ah);
		if (wqe->length > (1 << ah->log_pmtu))
			return -EINVAL;
		if (ibp->sl_to_sc[rdma_ah_get_sl(&ah->attr)] == 0xf)
			return -EINVAL;
	default:
		break;
	}
	return wqe->length <= piothreshold;
}