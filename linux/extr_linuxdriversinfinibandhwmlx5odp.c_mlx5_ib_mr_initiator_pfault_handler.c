#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_wqe_raddr_seg {int dummy; } ;
struct mlx5_wqe_ctrl_seg {int /*<<< orphan*/  opmod_idx_opcode; int /*<<< orphan*/  qpn_ds; } ;
struct mlx5_wqe_atomic_seg {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  wqe_index; } ;
struct mlx5_pagefault {TYPE_1__ wqe; } ;
struct TYPE_14__ {int qp_type; } ;
struct TYPE_9__ {int qpn; } ;
struct TYPE_10__ {TYPE_2__ mqp; } ;
struct TYPE_11__ {TYPE_3__ base; } ;
struct mlx5_ib_qp {TYPE_7__ ibqp; TYPE_4__ trans_qp; } ;
struct TYPE_12__ {int rc_odp_caps; int ud_odp_caps; } ;
struct TYPE_13__ {TYPE_5__ per_transport_caps; } ;
struct mlx5_ib_dev {TYPE_6__ odp_caps; } ;
struct mlx5_base_av {int dqp_dct; } ;
struct mlx5_av {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int EFAULT ; 
#define  IB_QPT_RC 134 
#define  IB_QPT_UD 133 
 int /*<<< orphan*/  MLX5_EXTENDED_UD_AV ; 
#define  MLX5_OPCODE_ATOMIC_CS 132 
#define  MLX5_OPCODE_ATOMIC_FA 131 
#define  MLX5_OPCODE_RDMA_READ 130 
#define  MLX5_OPCODE_RDMA_WRITE 129 
#define  MLX5_OPCODE_RDMA_WRITE_IMM 128 
 unsigned int MLX5_WQE_CTRL_DS_MASK ; 
 unsigned int MLX5_WQE_CTRL_OPCODE_MASK ; 
 unsigned int MLX5_WQE_DS_UNITS ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,unsigned int,...) ; 
 int* mlx5_ib_odp_opcode_cap ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx5_ib_mr_initiator_pfault_handler(
	struct mlx5_ib_dev *dev, struct mlx5_pagefault *pfault,
	struct mlx5_ib_qp *qp, void **wqe, void **wqe_end, int wqe_length)
{
	struct mlx5_wqe_ctrl_seg *ctrl = *wqe;
	u16 wqe_index = pfault->wqe.wqe_index;
	u32 transport_caps;
	struct mlx5_base_av *av;
	unsigned ds, opcode;
#if defined(DEBUG)
	u32 ctrl_wqe_index, ctrl_qpn;
#endif
	u32 qpn = qp->trans_qp.base.mqp.qpn;

	ds = be32_to_cpu(ctrl->qpn_ds) & MLX5_WQE_CTRL_DS_MASK;
	if (ds * MLX5_WQE_DS_UNITS > wqe_length) {
		mlx5_ib_err(dev, "Unable to read the complete WQE. ds = 0x%x, ret = 0x%x\n",
			    ds, wqe_length);
		return -EFAULT;
	}

	if (ds == 0) {
		mlx5_ib_err(dev, "Got WQE with zero DS. wqe_index=%x, qpn=%x\n",
			    wqe_index, qpn);
		return -EFAULT;
	}

#if defined(DEBUG)
	ctrl_wqe_index = (be32_to_cpu(ctrl->opmod_idx_opcode) &
			MLX5_WQE_CTRL_WQE_INDEX_MASK) >>
			MLX5_WQE_CTRL_WQE_INDEX_SHIFT;
	if (wqe_index != ctrl_wqe_index) {
		mlx5_ib_err(dev, "Got WQE with invalid wqe_index. wqe_index=0x%x, qpn=0x%x ctrl->wqe_index=0x%x\n",
			    wqe_index, qpn,
			    ctrl_wqe_index);
		return -EFAULT;
	}

	ctrl_qpn = (be32_to_cpu(ctrl->qpn_ds) & MLX5_WQE_CTRL_QPN_MASK) >>
		MLX5_WQE_CTRL_QPN_SHIFT;
	if (qpn != ctrl_qpn) {
		mlx5_ib_err(dev, "Got WQE with incorrect QP number. wqe_index=0x%x, qpn=0x%x ctrl->qpn=0x%x\n",
			    wqe_index, qpn,
			    ctrl_qpn);
		return -EFAULT;
	}
#endif /* DEBUG */

	*wqe_end = *wqe + ds * MLX5_WQE_DS_UNITS;
	*wqe += sizeof(*ctrl);

	opcode = be32_to_cpu(ctrl->opmod_idx_opcode) &
		 MLX5_WQE_CTRL_OPCODE_MASK;

	switch (qp->ibqp.qp_type) {
	case IB_QPT_RC:
		transport_caps = dev->odp_caps.per_transport_caps.rc_odp_caps;
		break;
	case IB_QPT_UD:
		transport_caps = dev->odp_caps.per_transport_caps.ud_odp_caps;
		break;
	default:
		mlx5_ib_err(dev, "ODP fault on QP of an unsupported transport 0x%x\n",
			    qp->ibqp.qp_type);
		return -EFAULT;
	}

	if (unlikely(opcode >= ARRAY_SIZE(mlx5_ib_odp_opcode_cap) ||
		     !(transport_caps & mlx5_ib_odp_opcode_cap[opcode]))) {
		mlx5_ib_err(dev, "ODP fault on QP of an unsupported opcode 0x%x\n",
			    opcode);
		return -EFAULT;
	}

	if (qp->ibqp.qp_type != IB_QPT_RC) {
		av = *wqe;
		if (av->dqp_dct & cpu_to_be32(MLX5_EXTENDED_UD_AV))
			*wqe += sizeof(struct mlx5_av);
		else
			*wqe += sizeof(struct mlx5_base_av);
	}

	switch (opcode) {
	case MLX5_OPCODE_RDMA_WRITE:
	case MLX5_OPCODE_RDMA_WRITE_IMM:
	case MLX5_OPCODE_RDMA_READ:
		*wqe += sizeof(struct mlx5_wqe_raddr_seg);
		break;
	case MLX5_OPCODE_ATOMIC_CS:
	case MLX5_OPCODE_ATOMIC_FA:
		*wqe += sizeof(struct mlx5_wqe_raddr_seg);
		*wqe += sizeof(struct mlx5_wqe_atomic_seg);
		break;
	}

	return 0;
}