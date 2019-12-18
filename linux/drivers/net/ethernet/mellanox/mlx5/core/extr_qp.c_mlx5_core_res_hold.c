#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mlx5_qp_table {int dummy; } ;
struct mlx5_core_rsc_common {int dummy; } ;
struct TYPE_2__ {struct mlx5_qp_table qp_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
typedef  enum mlx5_res_type { ____Placeholder_mlx5_res_type } mlx5_res_type ;

/* Variables and functions */
 int MLX5_USER_INDEX_LEN ; 
 struct mlx5_core_rsc_common* mlx5_get_rsc (struct mlx5_qp_table*,int) ; 

struct mlx5_core_rsc_common *mlx5_core_res_hold(struct mlx5_core_dev *dev,
						int res_num,
						enum mlx5_res_type res_type)
{
	u32 rsn = res_num | (res_type << MLX5_USER_INDEX_LEN);
	struct mlx5_qp_table *table = &dev->priv.qp_table;

	return mlx5_get_rsc(table, rsn);
}