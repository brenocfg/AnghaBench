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
struct mlx5_ib_dev {int dummy; } ;
struct mlx5_err_cqe {int syndrome; int /*<<< orphan*/  vendor_err_synd; } ;
struct ib_wc {int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_BAD_RESP_ERR ; 
 int /*<<< orphan*/  IB_WC_GENERAL_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_LEN_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_PROT_ERR ; 
 int /*<<< orphan*/  IB_WC_LOC_QP_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_MW_BIND_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_ABORT_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_ACCESS_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_INV_REQ_ERR ; 
 int /*<<< orphan*/  IB_WC_REM_OP_ERR ; 
 int /*<<< orphan*/  IB_WC_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_RNR_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
#define  MLX5_CQE_SYNDROME_BAD_RESP_ERR 140 
#define  MLX5_CQE_SYNDROME_LOCAL_ACCESS_ERR 139 
#define  MLX5_CQE_SYNDROME_LOCAL_LENGTH_ERR 138 
#define  MLX5_CQE_SYNDROME_LOCAL_PROT_ERR 137 
#define  MLX5_CQE_SYNDROME_LOCAL_QP_OP_ERR 136 
#define  MLX5_CQE_SYNDROME_MW_BIND_ERR 135 
#define  MLX5_CQE_SYNDROME_REMOTE_ABORTED_ERR 134 
#define  MLX5_CQE_SYNDROME_REMOTE_ACCESS_ERR 133 
#define  MLX5_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR 132 
#define  MLX5_CQE_SYNDROME_REMOTE_OP_ERR 131 
#define  MLX5_CQE_SYNDROME_RNR_RETRY_EXC_ERR 130 
#define  MLX5_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR 129 
#define  MLX5_CQE_SYNDROME_WR_FLUSH_ERR 128 
 int /*<<< orphan*/  dump_cqe (struct mlx5_ib_dev*,struct mlx5_err_cqe*) ; 

__attribute__((used)) static void mlx5_handle_error_cqe(struct mlx5_ib_dev *dev,
				  struct mlx5_err_cqe *cqe,
				  struct ib_wc *wc)
{
	int dump = 1;

	switch (cqe->syndrome) {
	case MLX5_CQE_SYNDROME_LOCAL_LENGTH_ERR:
		wc->status = IB_WC_LOC_LEN_ERR;
		break;
	case MLX5_CQE_SYNDROME_LOCAL_QP_OP_ERR:
		wc->status = IB_WC_LOC_QP_OP_ERR;
		break;
	case MLX5_CQE_SYNDROME_LOCAL_PROT_ERR:
		wc->status = IB_WC_LOC_PROT_ERR;
		break;
	case MLX5_CQE_SYNDROME_WR_FLUSH_ERR:
		dump = 0;
		wc->status = IB_WC_WR_FLUSH_ERR;
		break;
	case MLX5_CQE_SYNDROME_MW_BIND_ERR:
		wc->status = IB_WC_MW_BIND_ERR;
		break;
	case MLX5_CQE_SYNDROME_BAD_RESP_ERR:
		wc->status = IB_WC_BAD_RESP_ERR;
		break;
	case MLX5_CQE_SYNDROME_LOCAL_ACCESS_ERR:
		wc->status = IB_WC_LOC_ACCESS_ERR;
		break;
	case MLX5_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR:
		wc->status = IB_WC_REM_INV_REQ_ERR;
		break;
	case MLX5_CQE_SYNDROME_REMOTE_ACCESS_ERR:
		wc->status = IB_WC_REM_ACCESS_ERR;
		break;
	case MLX5_CQE_SYNDROME_REMOTE_OP_ERR:
		wc->status = IB_WC_REM_OP_ERR;
		break;
	case MLX5_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR:
		wc->status = IB_WC_RETRY_EXC_ERR;
		dump = 0;
		break;
	case MLX5_CQE_SYNDROME_RNR_RETRY_EXC_ERR:
		wc->status = IB_WC_RNR_RETRY_EXC_ERR;
		dump = 0;
		break;
	case MLX5_CQE_SYNDROME_REMOTE_ABORTED_ERR:
		wc->status = IB_WC_REM_ABORT_ERR;
		break;
	default:
		wc->status = IB_WC_GENERAL_ERR;
		break;
	}

	wc->vendor_err = cqe->vendor_err_synd;
	if (dump)
		dump_cqe(dev, cqe);
}