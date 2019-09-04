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
typedef  int u8 ;
struct mlx4_qp {int dummy; } ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_protocol { ____Placeholder_mlx4_protocol } mlx4_protocol ;

/* Variables and functions */
 int MLX4_PROT_ETH ; 
 int MLX4_UC_STEER ; 
 int mlx4_QP_ATTACH (struct mlx4_dev*,struct mlx4_qp*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 int mlx4_qp_detach_common (struct mlx4_dev*,struct mlx4_qp*,int*,int,int) ; 

int mlx4_unicast_detach(struct mlx4_dev *dev, struct mlx4_qp *qp,
			       u8 gid[16], enum mlx4_protocol prot)
{
	if (prot == MLX4_PROT_ETH)
		gid[7] |= (MLX4_UC_STEER << 1);

	if (mlx4_is_mfunc(dev))
		return mlx4_QP_ATTACH(dev, qp, gid, 0, 0, prot);

	return mlx4_qp_detach_common(dev, qp, gid, prot, MLX4_UC_STEER);
}