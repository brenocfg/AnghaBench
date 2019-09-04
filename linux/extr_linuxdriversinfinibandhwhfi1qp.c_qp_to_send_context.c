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
typedef  int /*<<< orphan*/  u8 ;
struct send_context {int dummy; } ;
struct TYPE_4__ {int qp_type; int qp_num; int /*<<< orphan*/  device; } ;
struct rvt_qp {TYPE_2__ ibqp; } ;
struct hfi1_devdata {int qos_shift; TYPE_1__* vld; } ;
struct TYPE_3__ {struct send_context* sc; } ;

/* Variables and functions */
#define  IB_QPT_SMI 128 
 struct hfi1_devdata* dd_from_ibdev (int /*<<< orphan*/ ) ; 
 struct send_context* pio_select_send_context_sc (struct hfi1_devdata*,int,int /*<<< orphan*/ ) ; 

struct send_context *qp_to_send_context(struct rvt_qp *qp, u8 sc5)
{
	struct hfi1_devdata *dd = dd_from_ibdev(qp->ibqp.device);

	switch (qp->ibqp.qp_type) {
	case IB_QPT_SMI:
		/* SMA packets to VL15 */
		return dd->vld[15].sc;
	default:
		break;
	}

	return pio_select_send_context_sc(dd, qp->ibqp.qp_num >> dd->qos_shift,
					  sc5);
}