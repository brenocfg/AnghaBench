#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  access; int /*<<< orphan*/  key; int /*<<< orphan*/  mr; } ;
struct TYPE_16__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  swap; int /*<<< orphan*/  compare_add; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_15__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_14__ {int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; } ;
struct TYPE_20__ {TYPE_6__ reg; TYPE_3__ atomic; TYPE_2__ rdma; TYPE_1__ ud; } ;
struct TYPE_17__ {int /*<<< orphan*/  invalidate_rkey; int /*<<< orphan*/  imm_data; } ;
struct rxe_send_wr {int opcode; TYPE_7__ wr; TYPE_4__ ex; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  num_sge; int /*<<< orphan*/  wr_id; } ;
struct rxe_qp {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  invalidate_rkey; int /*<<< orphan*/  imm_data; } ;
struct ib_send_wr {int opcode; TYPE_5__ ex; int /*<<< orphan*/  send_flags; int /*<<< orphan*/  num_sge; int /*<<< orphan*/  wr_id; } ;
struct TYPE_22__ {int /*<<< orphan*/  access; int /*<<< orphan*/  key; int /*<<< orphan*/  mr; } ;
struct TYPE_21__ {int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; } ;
struct TYPE_13__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  swap; int /*<<< orphan*/  compare_add; int /*<<< orphan*/  remote_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  rkey; int /*<<< orphan*/  remote_addr; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_SMI ; 
 scalar_t__ IB_QPT_UD ; 
#define  IB_WR_ATOMIC_CMP_AND_SWP 136 
#define  IB_WR_ATOMIC_FETCH_AND_ADD 135 
#define  IB_WR_LOCAL_INV 134 
#define  IB_WR_RDMA_READ 133 
#define  IB_WR_RDMA_WRITE 132 
#define  IB_WR_RDMA_WRITE_WITH_IMM 131 
#define  IB_WR_REG_MR 130 
#define  IB_WR_SEND_WITH_IMM 129 
#define  IB_WR_SEND_WITH_INV 128 
 TYPE_11__* atomic_wr (struct ib_send_wr const*) ; 
 scalar_t__ qp_type (struct rxe_qp*) ; 
 TYPE_10__* rdma_wr (struct ib_send_wr const*) ; 
 TYPE_9__* reg_wr (struct ib_send_wr const*) ; 
 TYPE_8__* ud_wr (struct ib_send_wr const*) ; 

__attribute__((used)) static void init_send_wr(struct rxe_qp *qp, struct rxe_send_wr *wr,
			 const struct ib_send_wr *ibwr)
{
	wr->wr_id = ibwr->wr_id;
	wr->num_sge = ibwr->num_sge;
	wr->opcode = ibwr->opcode;
	wr->send_flags = ibwr->send_flags;

	if (qp_type(qp) == IB_QPT_UD ||
	    qp_type(qp) == IB_QPT_SMI ||
	    qp_type(qp) == IB_QPT_GSI) {
		wr->wr.ud.remote_qpn = ud_wr(ibwr)->remote_qpn;
		wr->wr.ud.remote_qkey = ud_wr(ibwr)->remote_qkey;
		if (qp_type(qp) == IB_QPT_GSI)
			wr->wr.ud.pkey_index = ud_wr(ibwr)->pkey_index;
		if (wr->opcode == IB_WR_SEND_WITH_IMM)
			wr->ex.imm_data = ibwr->ex.imm_data;
	} else {
		switch (wr->opcode) {
		case IB_WR_RDMA_WRITE_WITH_IMM:
			wr->ex.imm_data = ibwr->ex.imm_data;
			/* fall through */
		case IB_WR_RDMA_READ:
		case IB_WR_RDMA_WRITE:
			wr->wr.rdma.remote_addr = rdma_wr(ibwr)->remote_addr;
			wr->wr.rdma.rkey	= rdma_wr(ibwr)->rkey;
			break;
		case IB_WR_SEND_WITH_IMM:
			wr->ex.imm_data = ibwr->ex.imm_data;
			break;
		case IB_WR_SEND_WITH_INV:
			wr->ex.invalidate_rkey = ibwr->ex.invalidate_rkey;
			break;
		case IB_WR_ATOMIC_CMP_AND_SWP:
		case IB_WR_ATOMIC_FETCH_AND_ADD:
			wr->wr.atomic.remote_addr =
				atomic_wr(ibwr)->remote_addr;
			wr->wr.atomic.compare_add =
				atomic_wr(ibwr)->compare_add;
			wr->wr.atomic.swap = atomic_wr(ibwr)->swap;
			wr->wr.atomic.rkey = atomic_wr(ibwr)->rkey;
			break;
		case IB_WR_LOCAL_INV:
			wr->ex.invalidate_rkey = ibwr->ex.invalidate_rkey;
		break;
		case IB_WR_REG_MR:
			wr->wr.reg.mr = reg_wr(ibwr)->mr;
			wr->wr.reg.key = reg_wr(ibwr)->key;
			wr->wr.reg.access = reg_wr(ibwr)->access;
		break;
		default:
			break;
		}
	}
}