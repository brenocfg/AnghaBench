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
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int mlx5_nic_vport_update_local_lb (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  port_type ; 

__attribute__((used)) static int mlx5_core_set_hca_defaults(struct mlx5_core_dev *dev)
{
	int ret = 0;

	/* Disable local_lb by default */
	if (MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_ETH)
		ret = mlx5_nic_vport_update_local_lb(dev, false);

	return ret;
}