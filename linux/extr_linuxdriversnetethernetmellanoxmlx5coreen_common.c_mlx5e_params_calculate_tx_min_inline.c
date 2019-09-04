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
typedef  scalar_t__ u8 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_INLINE_MODE_L2 ; 
 scalar_t__ MLX5_INLINE_MODE_NONE ; 
 int /*<<< orphan*/  mlx5_query_min_inline (struct mlx5_core_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  wqe_vlan_insert ; 

u8 mlx5e_params_calculate_tx_min_inline(struct mlx5_core_dev *mdev)
{
	u8 min_inline_mode;

	mlx5_query_min_inline(mdev, &min_inline_mode);
	if (min_inline_mode == MLX5_INLINE_MODE_NONE &&
	    !MLX5_CAP_ETH(mdev, wqe_vlan_insert))
		min_inline_mode = MLX5_INLINE_MODE_L2;

	return min_inline_mode;
}