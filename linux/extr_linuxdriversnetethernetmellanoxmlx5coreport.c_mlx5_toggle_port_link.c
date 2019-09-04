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
typedef  enum mlx5_port_status { ____Placeholder_mlx5_port_status } mlx5_port_status ;

/* Variables and functions */
 int MLX5_PORT_DOWN ; 
 int MLX5_PORT_UP ; 
 int /*<<< orphan*/  mlx5_query_port_admin_status (struct mlx5_core_dev*,int*) ; 
 int /*<<< orphan*/  mlx5_set_port_admin_status (struct mlx5_core_dev*,int) ; 

void mlx5_toggle_port_link(struct mlx5_core_dev *dev)
{
	enum mlx5_port_status ps;

	mlx5_query_port_admin_status(dev, &ps);
	mlx5_set_port_admin_status(dev, MLX5_PORT_DOWN);
	if (ps == MLX5_PORT_UP)
		mlx5_set_port_admin_status(dev, MLX5_PORT_UP);
}