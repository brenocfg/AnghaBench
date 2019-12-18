#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u16 ;

/* Variables and functions */
 void* MLX5_ADDR_OF (void*,void const*,void*) ; 
#define  MLX5_CMD_OP_CREATE_CQ 136 
#define  MLX5_CMD_OP_CREATE_MKEY 135 
#define  MLX5_CMD_OP_CREATE_QP 134 
#define  MLX5_CMD_OP_CREATE_RMP 133 
#define  MLX5_CMD_OP_CREATE_RQ 132 
#define  MLX5_CMD_OP_CREATE_SQ 131 
#define  MLX5_CMD_OP_CREATE_XRC_SRQ 130 
#define  MLX5_CMD_OP_CREATE_XRQ 129 
#define  MLX5_CMD_OP_MODIFY_CQ 128 
 int MLX5_GET (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 void* cq_context ; 
 int /*<<< orphan*/  cq_umem_valid ; 
 void* create_cq_in ; 
 void* create_mkey_in ; 
 void* create_qp_in ; 
 void* create_rmp_in ; 
 void* create_rq_in ; 
 void* create_sq_in ; 
 void* create_xrc_srq_in ; 
 void* create_xrq_in ; 
 void* ctx ; 
 int /*<<< orphan*/  dbr_umem_valid ; 
 int /*<<< orphan*/  general_obj_in_cmd_hdr ; 
 int /*<<< orphan*/  mkey_umem_valid ; 
 void* modify_cq_in ; 
 int opcode ; 
 int /*<<< orphan*/  wq_umem_valid ; 
 void* xrc_srq_context_entry ; 
 int /*<<< orphan*/  xrc_srq_umem_valid ; 
 void* xrq_context ; 

__attribute__((used)) static void devx_set_umem_valid(const void *in)
{
	u16 opcode = MLX5_GET(general_obj_in_cmd_hdr, in, opcode);

	switch (opcode) {
	case MLX5_CMD_OP_CREATE_MKEY:
		MLX5_SET(create_mkey_in, in, mkey_umem_valid, 1);
		break;
	case MLX5_CMD_OP_CREATE_CQ:
	{
		void *cqc;

		MLX5_SET(create_cq_in, in, cq_umem_valid, 1);
		cqc = MLX5_ADDR_OF(create_cq_in, in, cq_context);
		MLX5_SET(cqc, cqc, dbr_umem_valid, 1);
		break;
	}
	case MLX5_CMD_OP_CREATE_QP:
	{
		void *qpc;

		qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);
		MLX5_SET(qpc, qpc, dbr_umem_valid, 1);
		MLX5_SET(create_qp_in, in, wq_umem_valid, 1);
		break;
	}

	case MLX5_CMD_OP_CREATE_RQ:
	{
		void *rqc, *wq;

		rqc = MLX5_ADDR_OF(create_rq_in, in, ctx);
		wq  = MLX5_ADDR_OF(rqc, rqc, wq);
		MLX5_SET(wq, wq, dbr_umem_valid, 1);
		MLX5_SET(wq, wq, wq_umem_valid, 1);
		break;
	}

	case MLX5_CMD_OP_CREATE_SQ:
	{
		void *sqc, *wq;

		sqc = MLX5_ADDR_OF(create_sq_in, in, ctx);
		wq = MLX5_ADDR_OF(sqc, sqc, wq);
		MLX5_SET(wq, wq, dbr_umem_valid, 1);
		MLX5_SET(wq, wq, wq_umem_valid, 1);
		break;
	}

	case MLX5_CMD_OP_MODIFY_CQ:
		MLX5_SET(modify_cq_in, in, cq_umem_valid, 1);
		break;

	case MLX5_CMD_OP_CREATE_RMP:
	{
		void *rmpc, *wq;

		rmpc = MLX5_ADDR_OF(create_rmp_in, in, ctx);
		wq = MLX5_ADDR_OF(rmpc, rmpc, wq);
		MLX5_SET(wq, wq, dbr_umem_valid, 1);
		MLX5_SET(wq, wq, wq_umem_valid, 1);
		break;
	}

	case MLX5_CMD_OP_CREATE_XRQ:
	{
		void *xrqc, *wq;

		xrqc = MLX5_ADDR_OF(create_xrq_in, in, xrq_context);
		wq = MLX5_ADDR_OF(xrqc, xrqc, wq);
		MLX5_SET(wq, wq, dbr_umem_valid, 1);
		MLX5_SET(wq, wq, wq_umem_valid, 1);
		break;
	}

	case MLX5_CMD_OP_CREATE_XRC_SRQ:
	{
		void *xrc_srqc;

		MLX5_SET(create_xrc_srq_in, in, xrc_srq_umem_valid, 1);
		xrc_srqc = MLX5_ADDR_OF(create_xrc_srq_in, in,
					xrc_srq_context_entry);
		MLX5_SET(xrc_srqc, xrc_srqc, dbr_umem_valid, 1);
		break;
	}

	default:
		return;
	}
}