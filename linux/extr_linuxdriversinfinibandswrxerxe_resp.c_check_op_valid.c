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
struct TYPE_3__ {int drop_msg; } ;
struct TYPE_4__ {int qp_access_flags; } ;
struct rxe_qp {TYPE_1__ resp; TYPE_2__ attr; } ;
struct rxe_pkt_info {int mask; } ;
typedef  enum resp_states { ____Placeholder_resp_states } resp_states ;

/* Variables and functions */
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
#define  IB_QPT_GSI 132 
#define  IB_QPT_RC 131 
#define  IB_QPT_SMI 130 
#define  IB_QPT_UC 129 
#define  IB_QPT_UD 128 
 int RESPST_CHK_RESOURCE ; 
 int RESPST_CLEANUP ; 
 int RESPST_ERR_UNSUPPORTED_OPCODE ; 
 int RXE_ATOMIC_MASK ; 
 int RXE_READ_MASK ; 
 int RXE_WRITE_MASK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int qp_type (struct rxe_qp*) ; 

__attribute__((used)) static enum resp_states check_op_valid(struct rxe_qp *qp,
				       struct rxe_pkt_info *pkt)
{
	switch (qp_type(qp)) {
	case IB_QPT_RC:
		if (((pkt->mask & RXE_READ_MASK) &&
		     !(qp->attr.qp_access_flags & IB_ACCESS_REMOTE_READ)) ||
		    ((pkt->mask & RXE_WRITE_MASK) &&
		     !(qp->attr.qp_access_flags & IB_ACCESS_REMOTE_WRITE)) ||
		    ((pkt->mask & RXE_ATOMIC_MASK) &&
		     !(qp->attr.qp_access_flags & IB_ACCESS_REMOTE_ATOMIC))) {
			return RESPST_ERR_UNSUPPORTED_OPCODE;
		}

		break;

	case IB_QPT_UC:
		if ((pkt->mask & RXE_WRITE_MASK) &&
		    !(qp->attr.qp_access_flags & IB_ACCESS_REMOTE_WRITE)) {
			qp->resp.drop_msg = 1;
			return RESPST_CLEANUP;
		}

		break;

	case IB_QPT_UD:
	case IB_QPT_SMI:
	case IB_QPT_GSI:
		break;

	default:
		WARN_ON_ONCE(1);
		break;
	}

	return RESPST_CHK_RESOURCE;
}