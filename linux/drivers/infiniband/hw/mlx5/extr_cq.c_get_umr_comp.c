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
struct mlx5_ib_wq {int* wr_data; } ;
typedef  enum ib_wc_opcode { ____Placeholder_ib_wc_opcode } ib_wc_opcode ;

/* Variables and functions */
 int IB_WC_LOCAL_INV ; 
 int IB_WC_REG_MR ; 
#define  IB_WR_LOCAL_INV 130 
#define  IB_WR_REG_MR 129 
#define  MLX5_IB_WR_UMR 128 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static enum ib_wc_opcode get_umr_comp(struct mlx5_ib_wq *wq, int idx)
{
	switch (wq->wr_data[idx]) {
	case MLX5_IB_WR_UMR:
		return 0;

	case IB_WR_LOCAL_INV:
		return IB_WC_LOCAL_INV;

	case IB_WR_REG_MR:
		return IB_WC_REG_MR;

	default:
		pr_warn("unknown completion status\n");
		return 0;
	}
}