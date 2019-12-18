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
struct mlx4_ptys_reg {int dummy; } ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_access_reg_method { ____Placeholder_mlx4_access_reg_method } mlx4_access_reg_method ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_REG_ID_PTYS ; 
 int mlx4_ACCESS_REG (struct mlx4_dev*,int /*<<< orphan*/ ,int,int,struct mlx4_ptys_reg*) ; 

int mlx4_ACCESS_PTYS_REG(struct mlx4_dev *dev,
			 enum mlx4_access_reg_method method,
			 struct mlx4_ptys_reg *ptys_reg)
{
	return mlx4_ACCESS_REG(dev, MLX4_REG_ID_PTYS,
			       method, sizeof(*ptys_reg), ptys_reg);
}