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
struct mlx5e_params {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_GET_PFLAG (struct mlx5e_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_MPWQE_STRIDE_SZ (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5E_PFLAG_RX_CQE_COMPRESS ; 
 int /*<<< orphan*/  mlx5e_rx_get_linear_frag_sz (struct mlx5e_params*) ; 
 scalar_t__ mlx5e_rx_mpwqe_is_linear_skb (struct mlx5_core_dev*,struct mlx5e_params*) ; 
 int /*<<< orphan*/  order_base_2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 mlx5e_mpwqe_get_log_stride_size(struct mlx5_core_dev *mdev,
					  struct mlx5e_params *params)
{
	if (mlx5e_rx_mpwqe_is_linear_skb(mdev, params))
		return order_base_2(mlx5e_rx_get_linear_frag_sz(params));

	return MLX5E_MPWQE_STRIDE_SZ(mdev,
		MLX5E_GET_PFLAG(params, MLX5E_PFLAG_RX_CQE_COMPRESS));
}