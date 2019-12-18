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
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {TYPE_1__ ibqp; } ;
struct hfi1_ibdev {TYPE_2__* fault; } ;
struct TYPE_4__ {int /*<<< orphan*/ * n_txfaults; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_FAULT_DIR_TX ; 
 scalar_t__ __hfi1_should_fault (struct hfi1_ibdev*,size_t,int /*<<< orphan*/ ) ; 
 struct hfi1_ibdev* to_idev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_fault_opcode (struct rvt_qp*,size_t) ; 

bool hfi1_dbg_should_fault_tx(struct rvt_qp *qp, u32 opcode)
{
	struct hfi1_ibdev *ibd = to_idev(qp->ibqp.device);

	if (__hfi1_should_fault(ibd, opcode, HFI1_FAULT_DIR_TX)) {
		trace_hfi1_fault_opcode(qp, opcode);
		ibd->fault->n_txfaults[opcode]++;
		return true;
	}
	return false;
}