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
typedef  int u32 ;
typedef  int u16 ;
struct mlx5_core_dev {int dummy; } ;
struct mbox_info {int /*<<< orphan*/ * in; int /*<<< orphan*/ * out; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_ADDR_OF (void*,int /*<<< orphan*/ *,void*) ; 
#define  MLX5_CMD_OP_2ERR_QP 135 
#define  MLX5_CMD_OP_2RST_QP 134 
#define  MLX5_CMD_OP_INIT2INIT_QP 133 
#define  MLX5_CMD_OP_INIT2RTR_QP 132 
#define  MLX5_CMD_OP_RST2INIT_QP 131 
#define  MLX5_CMD_OP_RTR2RTS_QP 130 
#define  MLX5_CMD_OP_RTS2RTS_QP 129 
#define  MLX5_CMD_OP_SQERR2RTS_QP 128 
 int /*<<< orphan*/  MLX5_SET (void*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (void*) ; 
 void* init2init_qp_in ; 
 void* init2init_qp_out ; 
 void* init2rtr_qp_in ; 
 void* init2rtr_qp_out ; 
 int /*<<< orphan*/  mbox_alloc (struct mbox_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int,int) ; 
 void* qp_2err_in ; 
 void* qp_2err_out ; 
 void* qp_2rst_in ; 
 void* qp_2rst_out ; 
 void* rst2init_qp_in ; 
 void* rst2init_qp_out ; 
 void* rtr2rts_qp_in ; 
 void* rtr2rts_qp_out ; 
 void* rts2rts_qp_in ; 
 void* rts2rts_qp_out ; 
 void* sqerr2rts_qp_in ; 
 void* sqerr2rts_qp_out ; 

__attribute__((used)) static int modify_qp_mbox_alloc(struct mlx5_core_dev *dev, u16 opcode, int qpn,
				u32 opt_param_mask, void *qpc,
				struct mbox_info *mbox)
{
	mbox->out = NULL;
	mbox->in = NULL;

#define MBOX_ALLOC(mbox, typ)  \
	mbox_alloc(mbox, MLX5_ST_SZ_BYTES(typ##_in), MLX5_ST_SZ_BYTES(typ##_out))

#define MOD_QP_IN_SET(typ, in, _opcode, _qpn) \
	MLX5_SET(typ##_in, in, opcode, _opcode); \
	MLX5_SET(typ##_in, in, qpn, _qpn)

#define MOD_QP_IN_SET_QPC(typ, in, _opcode, _qpn, _opt_p, _qpc) \
	MOD_QP_IN_SET(typ, in, _opcode, _qpn); \
	MLX5_SET(typ##_in, in, opt_param_mask, _opt_p); \
	memcpy(MLX5_ADDR_OF(typ##_in, in, qpc), _qpc, MLX5_ST_SZ_BYTES(qpc))

	switch (opcode) {
	/* 2RST & 2ERR */
	case MLX5_CMD_OP_2RST_QP:
		if (MBOX_ALLOC(mbox, qp_2rst))
			return -ENOMEM;
		MOD_QP_IN_SET(qp_2rst, mbox->in, opcode, qpn);
		break;
	case MLX5_CMD_OP_2ERR_QP:
		if (MBOX_ALLOC(mbox, qp_2err))
			return -ENOMEM;
		MOD_QP_IN_SET(qp_2err, mbox->in, opcode, qpn);
		break;

	/* MODIFY with QPC */
	case MLX5_CMD_OP_RST2INIT_QP:
		if (MBOX_ALLOC(mbox, rst2init_qp))
			return -ENOMEM;
		MOD_QP_IN_SET_QPC(rst2init_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc);
		break;
	case MLX5_CMD_OP_INIT2RTR_QP:
		if (MBOX_ALLOC(mbox, init2rtr_qp))
			return -ENOMEM;
		MOD_QP_IN_SET_QPC(init2rtr_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc);
		break;
	case MLX5_CMD_OP_RTR2RTS_QP:
		if (MBOX_ALLOC(mbox, rtr2rts_qp))
			return -ENOMEM;
		MOD_QP_IN_SET_QPC(rtr2rts_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc);
		break;
	case MLX5_CMD_OP_RTS2RTS_QP:
		if (MBOX_ALLOC(mbox, rts2rts_qp))
			return -ENOMEM;
		MOD_QP_IN_SET_QPC(rts2rts_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc);
		break;
	case MLX5_CMD_OP_SQERR2RTS_QP:
		if (MBOX_ALLOC(mbox, sqerr2rts_qp))
			return -ENOMEM;
		MOD_QP_IN_SET_QPC(sqerr2rts_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc);
		break;
	case MLX5_CMD_OP_INIT2INIT_QP:
		if (MBOX_ALLOC(mbox, init2init_qp))
			return -ENOMEM;
		MOD_QP_IN_SET_QPC(init2init_qp, mbox->in, opcode, qpn,
				  opt_param_mask, qpc);
		break;
	default:
		mlx5_core_err(dev, "Unknown transition for modify QP: OP(0x%x) QPN(0x%x)\n",
			      opcode, qpn);
		return -EINVAL;
	}
	return 0;
}