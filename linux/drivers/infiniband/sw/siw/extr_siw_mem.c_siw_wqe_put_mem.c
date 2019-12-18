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
struct TYPE_4__ {int num_sge; } ;
struct TYPE_3__ {int flags; int num_sge; } ;
struct siw_wqe {int /*<<< orphan*/  mem; TYPE_2__ rqe; TYPE_1__ sqe; } ;
typedef  enum siw_opcode { ____Placeholder_siw_opcode } siw_opcode ;

/* Variables and functions */
#define  SIW_OP_READ 135 
#define  SIW_OP_READ_LOCAL_INV 134 
#define  SIW_OP_READ_RESPONSE 133 
#define  SIW_OP_RECEIVE 132 
#define  SIW_OP_SEND 131 
#define  SIW_OP_SEND_REMOTE_INV 130 
#define  SIW_OP_SEND_WITH_IMM 129 
#define  SIW_OP_WRITE 128 
 int SIW_WQE_INLINE ; 
 int /*<<< orphan*/  siw_unref_mem_sgl (int /*<<< orphan*/ ,int) ; 

void siw_wqe_put_mem(struct siw_wqe *wqe, enum siw_opcode op)
{
	switch (op) {
	case SIW_OP_SEND:
	case SIW_OP_WRITE:
	case SIW_OP_SEND_WITH_IMM:
	case SIW_OP_SEND_REMOTE_INV:
	case SIW_OP_READ:
	case SIW_OP_READ_LOCAL_INV:
		if (!(wqe->sqe.flags & SIW_WQE_INLINE))
			siw_unref_mem_sgl(wqe->mem, wqe->sqe.num_sge);
		break;

	case SIW_OP_RECEIVE:
		siw_unref_mem_sgl(wqe->mem, wqe->rqe.num_sge);
		break;

	case SIW_OP_READ_RESPONSE:
		siw_unref_mem_sgl(wqe->mem, 1);
		break;

	default:
		/*
		 * SIW_OP_INVAL_STAG and SIW_OP_REG_MR
		 * do not hold memory references
		 */
		break;
	}
}