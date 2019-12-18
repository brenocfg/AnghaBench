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
typedef  int /*<<< orphan*/  u8 ;
struct mlx5e_xsk_param {int dummy; } ;
struct mlx5e_params {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_MPWRQ_DEF_LOG_STRIDE_SZ (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5e_rx_get_linear_frag_sz (struct mlx5e_params*,struct mlx5e_xsk_param*) ; 
 scalar_t__ mlx5e_rx_mpwqe_is_linear_skb (struct mlx5_core_dev*,struct mlx5e_params*,struct mlx5e_xsk_param*) ; 
 int /*<<< orphan*/  order_base_2 (int /*<<< orphan*/ ) ; 

u8 mlx5e_mpwqe_get_log_stride_size(struct mlx5_core_dev *mdev,
				   struct mlx5e_params *params,
				   struct mlx5e_xsk_param *xsk)
{
	if (mlx5e_rx_mpwqe_is_linear_skb(mdev, params, xsk))
		return order_base_2(mlx5e_rx_get_linear_frag_sz(params, xsk));

	return MLX5_MPWRQ_DEF_LOG_STRIDE_SZ(mdev);
}