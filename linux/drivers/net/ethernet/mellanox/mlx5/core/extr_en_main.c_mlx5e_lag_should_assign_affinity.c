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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lag_tx_port_affinity ; 
 int mlx5e_get_num_lag_ports (struct mlx5_core_dev*) ; 

__attribute__((used)) static bool mlx5e_lag_should_assign_affinity(struct mlx5_core_dev *mdev)
{
	return MLX5_CAP_GEN(mdev, lag_tx_port_affinity) && mlx5e_get_num_lag_ports(mdev) > 1;
}