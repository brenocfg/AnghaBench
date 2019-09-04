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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ib_qp {int /*<<< orphan*/  has_rq; } ;
struct ib_qp_init_attr {scalar_t__ qp_type; scalar_t__ srq; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_XRC_INI ; 
 scalar_t__ IB_QPT_XRC_TGT ; 
 scalar_t__ MLX5_IB_QPT_DCI ; 
 int /*<<< orphan*/  MLX5_NON_ZERO_RQ ; 
 int /*<<< orphan*/  MLX5_SRQ_RQ ; 
 int /*<<< orphan*/  MLX5_ZERO_LEN_RQ ; 

__attribute__((used)) static u32 get_rx_type(struct mlx5_ib_qp *qp, struct ib_qp_init_attr *attr)
{
	if (attr->srq || (attr->qp_type == IB_QPT_XRC_TGT) ||
	    (attr->qp_type == MLX5_IB_QPT_DCI) ||
	    (attr->qp_type == IB_QPT_XRC_INI))
		return MLX5_SRQ_RQ;
	else if (!qp->has_rq)
		return MLX5_ZERO_LEN_RQ;
	else
		return MLX5_NON_ZERO_RQ;
}