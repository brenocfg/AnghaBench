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
typedef  int u32 ;
struct TYPE_2__ {int opcode; } ;
struct rxe_qp {TYPE_1__ req; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_OPCODE_UC_RDMA_WRITE_FIRST ; 
 int IB_OPCODE_UC_RDMA_WRITE_LAST ; 
 int IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE ; 
 int IB_OPCODE_UC_RDMA_WRITE_MIDDLE ; 
 int IB_OPCODE_UC_RDMA_WRITE_ONLY ; 
 int IB_OPCODE_UC_RDMA_WRITE_ONLY_WITH_IMMEDIATE ; 
 int IB_OPCODE_UC_SEND_FIRST ; 
 int IB_OPCODE_UC_SEND_LAST ; 
 int IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE ; 
 int IB_OPCODE_UC_SEND_MIDDLE ; 
 int IB_OPCODE_UC_SEND_ONLY ; 
 int IB_OPCODE_UC_SEND_ONLY_WITH_IMMEDIATE ; 
#define  IB_WR_RDMA_WRITE 131 
#define  IB_WR_RDMA_WRITE_WITH_IMM 130 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_IMM 128 

__attribute__((used)) static int next_opcode_uc(struct rxe_qp *qp, u32 opcode, int fits)
{
	switch (opcode) {
	case IB_WR_RDMA_WRITE:
		if (qp->req.opcode == IB_OPCODE_UC_RDMA_WRITE_FIRST ||
		    qp->req.opcode == IB_OPCODE_UC_RDMA_WRITE_MIDDLE)
			return fits ?
				IB_OPCODE_UC_RDMA_WRITE_LAST :
				IB_OPCODE_UC_RDMA_WRITE_MIDDLE;
		else
			return fits ?
				IB_OPCODE_UC_RDMA_WRITE_ONLY :
				IB_OPCODE_UC_RDMA_WRITE_FIRST;

	case IB_WR_RDMA_WRITE_WITH_IMM:
		if (qp->req.opcode == IB_OPCODE_UC_RDMA_WRITE_FIRST ||
		    qp->req.opcode == IB_OPCODE_UC_RDMA_WRITE_MIDDLE)
			return fits ?
				IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE :
				IB_OPCODE_UC_RDMA_WRITE_MIDDLE;
		else
			return fits ?
				IB_OPCODE_UC_RDMA_WRITE_ONLY_WITH_IMMEDIATE :
				IB_OPCODE_UC_RDMA_WRITE_FIRST;

	case IB_WR_SEND:
		if (qp->req.opcode == IB_OPCODE_UC_SEND_FIRST ||
		    qp->req.opcode == IB_OPCODE_UC_SEND_MIDDLE)
			return fits ?
				IB_OPCODE_UC_SEND_LAST :
				IB_OPCODE_UC_SEND_MIDDLE;
		else
			return fits ?
				IB_OPCODE_UC_SEND_ONLY :
				IB_OPCODE_UC_SEND_FIRST;

	case IB_WR_SEND_WITH_IMM:
		if (qp->req.opcode == IB_OPCODE_UC_SEND_FIRST ||
		    qp->req.opcode == IB_OPCODE_UC_SEND_MIDDLE)
			return fits ?
				IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE :
				IB_OPCODE_UC_SEND_MIDDLE;
		else
			return fits ?
				IB_OPCODE_UC_SEND_ONLY_WITH_IMMEDIATE :
				IB_OPCODE_UC_SEND_FIRST;
	}

	return -EINVAL;
}