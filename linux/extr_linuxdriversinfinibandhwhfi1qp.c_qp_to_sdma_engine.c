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
typedef  int /*<<< orphan*/  u8 ;
struct sdma_engine {int dummy; } ;
struct TYPE_2__ {int qp_type; int qp_num; int /*<<< orphan*/  device; } ;
struct rvt_qp {TYPE_1__ ibqp; } ;
struct hfi1_devdata {int flags; int qos_shift; } ;

/* Variables and functions */
 int HFI1_HAS_SEND_DMA ; 
#define  IB_QPT_SMI 128 
 struct hfi1_devdata* dd_from_ibdev (int /*<<< orphan*/ ) ; 
 struct sdma_engine* sdma_select_engine_sc (struct hfi1_devdata*,int,int /*<<< orphan*/ ) ; 

struct sdma_engine *qp_to_sdma_engine(struct rvt_qp *qp, u8 sc5)
{
	struct hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);
	struct sdma_engine *sde;

	if (!(dd->flags & HFI1_HAS_SEND_DMA))
		return NULL;
	switch (qp->ibqp.qp_type) {
	case IB_QPT_SMI:
		return NULL;
	default:
		break;
	}
	sde = sdma_select_engine_sc(dd, qp->ibqp.qp_num >> dd->qos_shift, sc5);
	return sde;
}