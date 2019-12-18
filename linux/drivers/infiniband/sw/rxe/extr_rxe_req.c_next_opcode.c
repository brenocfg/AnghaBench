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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ resid; } ;
struct rxe_send_wqe {TYPE_1__ dma; } ;
struct rxe_qp {scalar_t__ mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_OPCODE_UD_SEND_ONLY ; 
 int IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE ; 
#define  IB_QPT_GSI 134 
#define  IB_QPT_RC 133 
#define  IB_QPT_SMI 132 
#define  IB_QPT_UC 131 
#define  IB_QPT_UD 130 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_IMM 128 
 int next_opcode_rc (struct rxe_qp*,int /*<<< orphan*/ ,int) ; 
 int next_opcode_uc (struct rxe_qp*,int /*<<< orphan*/ ,int) ; 
 int qp_type (struct rxe_qp*) ; 

__attribute__((used)) static int next_opcode(struct rxe_qp *qp, struct rxe_send_wqe *wqe,
		       u32 opcode)
{
	int fits = (wqe->dma.resid <= qp->mtu);

	switch (qp_type(qp)) {
	case IB_QPT_RC:
		return next_opcode_rc(qp, opcode, fits);

	case IB_QPT_UC:
		return next_opcode_uc(qp, opcode, fits);

	case IB_QPT_SMI:
	case IB_QPT_UD:
	case IB_QPT_GSI:
		switch (opcode) {
		case IB_WR_SEND:
			return IB_OPCODE_UD_SEND_ONLY;

		case IB_WR_SEND_WITH_IMM:
			return IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE;
		}
		break;

	default:
		break;
	}

	return -EINVAL;
}