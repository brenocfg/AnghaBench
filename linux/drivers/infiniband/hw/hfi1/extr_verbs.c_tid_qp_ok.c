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
struct hfi1_packet {TYPE_2__* qp; } ;
typedef  int /*<<< orphan*/ * opcode_handler ;
struct TYPE_3__ {scalar_t__ qp_type; } ;
struct TYPE_4__ {size_t state; TYPE_1__ ibqp; } ;

/* Variables and functions */
 int IB_OPCODE_TID_RDMA ; 
 scalar_t__ IB_QPT_RC ; 
 int RVT_OPCODE_QP_MASK ; 
 int RVT_PROCESS_RECV_OK ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/ ** opcode_handler_tbl ; 

__attribute__((used)) static opcode_handler tid_qp_ok(int opcode, struct hfi1_packet *packet)
{
	if (packet->qp->ibqp.qp_type != IB_QPT_RC ||
	    !(ib_rvt_state_ops[packet->qp->state] & RVT_PROCESS_RECV_OK))
		return NULL;
	if ((opcode & RVT_OPCODE_QP_MASK) == IB_OPCODE_TID_RDMA)
		return opcode_handler_tbl[opcode];
	return NULL;
}