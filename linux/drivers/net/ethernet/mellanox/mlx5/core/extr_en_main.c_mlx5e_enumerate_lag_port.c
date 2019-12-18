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
typedef  int u16 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5_core_is_pf (struct mlx5_core_dev*) ; 
 int mlx5e_get_num_lag_ports (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  vhca_id ; 

__attribute__((used)) static u8 mlx5e_enumerate_lag_port(struct mlx5_core_dev *mdev, int ix)
{
	u16 port_aff_bias = mlx5_core_is_pf(mdev) ? 0 : MLX5_CAP_GEN(mdev, vhca_id);

	return (ix + port_aff_bias) % mlx5e_get_num_lag_ports(mdev);
}