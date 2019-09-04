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
struct mlx5e_params {scalar_t__ xdp_prog; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_IPSEC_DEV (struct mlx5_core_dev*) ; 
 scalar_t__ mlx5e_check_fragmented_striding_rq_cap (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5e_rx_mpwqe_is_linear_skb (struct mlx5_core_dev*,struct mlx5e_params*) ; 

bool mlx5e_striding_rq_possible(struct mlx5_core_dev *mdev,
				struct mlx5e_params *params)
{
	return mlx5e_check_fragmented_striding_rq_cap(mdev) &&
		!MLX5_IPSEC_DEV(mdev) &&
		!(params->xdp_prog && !mlx5e_rx_mpwqe_is_linear_skb(mdev, params));
}