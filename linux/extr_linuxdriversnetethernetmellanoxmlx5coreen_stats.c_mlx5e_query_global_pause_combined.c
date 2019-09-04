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
typedef  int u32 ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int mlx5_query_port_pause (struct mlx5_core_dev*,int*,int*) ; 
 int /*<<< orphan*/  port_type ; 

__attribute__((used)) static bool mlx5e_query_global_pause_combined(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	u32 rx_pause;
	u32 tx_pause;
	int err;

	if (MLX5_CAP_GEN(mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		return false;

	err = mlx5_query_port_pause(mdev, &rx_pause, &tx_pause);

	return err ? false : rx_pause | tx_pause;
}