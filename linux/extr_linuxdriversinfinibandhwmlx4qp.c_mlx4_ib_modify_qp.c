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
struct mlx4_ib_sqp {scalar_t__ roce_v2_gsi; } ;
struct mlx4_ib_qp {scalar_t__ mlx4_ib_qp_type; } ;
struct ib_udata {int dummy; } ;
struct ib_qp_attr {int dummy; } ;
struct ib_qp {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX4_IB_QPT_GSI ; 
 int _mlx4_ib_modify_qp (struct ib_qp*,struct ib_qp_attr*,int,struct ib_udata*) ; 
 int ib_modify_qp (scalar_t__,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct mlx4_ib_qp* to_mqp (struct ib_qp*) ; 
 struct mlx4_ib_sqp* to_msqp (struct mlx4_ib_qp*) ; 

int mlx4_ib_modify_qp(struct ib_qp *ibqp, struct ib_qp_attr *attr,
		      int attr_mask, struct ib_udata *udata)
{
	struct mlx4_ib_qp *mqp = to_mqp(ibqp);
	int ret;

	ret = _mlx4_ib_modify_qp(ibqp, attr, attr_mask, udata);

	if (mqp->mlx4_ib_qp_type == MLX4_IB_QPT_GSI) {
		struct mlx4_ib_sqp *sqp = to_msqp(mqp);
		int err = 0;

		if (sqp->roce_v2_gsi)
			err = ib_modify_qp(sqp->roce_v2_gsi, attr, attr_mask);
		if (err)
			pr_err("Failed to modify GSI QP for RoCEv2 (%d)\n",
			       err);
	}
	return ret;
}