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
struct hfi1_packet {int opcode; TYPE_1__* qp; } ;
typedef  int /*<<< orphan*/ * opcode_handler ;
struct TYPE_2__ {size_t state; int allowed_ops; } ;

/* Variables and functions */
 int IB_OPCODE_CNP ; 
 int RVT_OPCODE_QP_MASK ; 
 int RVT_PROCESS_RECV_OK ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/ ** opcode_handler_tbl ; 

__attribute__((used)) static inline opcode_handler qp_ok(struct hfi1_packet *packet)
{
	if (!(ib_rvt_state_ops[packet->qp->state] & RVT_PROCESS_RECV_OK))
		return NULL;
	if (((packet->opcode & RVT_OPCODE_QP_MASK) ==
	     packet->qp->allowed_ops) ||
	    (packet->opcode == IB_OPCODE_CNP))
		return opcode_handler_tbl[packet->opcode];

	return NULL;
}