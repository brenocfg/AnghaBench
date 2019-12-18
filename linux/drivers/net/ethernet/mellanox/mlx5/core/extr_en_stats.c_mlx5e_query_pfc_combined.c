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
typedef  unsigned long u8 ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_CAP_PORT_TYPE_ETH ; 
 int mlx5_query_port_pfc (struct mlx5_core_dev*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  port_type ; 

__attribute__((used)) static unsigned long mlx5e_query_pfc_combined(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	u8 pfc_en_tx;
	u8 pfc_en_rx;
	int err;

	if (MLX5_CAP_GEN(mdev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		return 0;

	err = mlx5_query_port_pfc(mdev, &pfc_en_tx, &pfc_en_rx);

	return err ? 0 : pfc_en_tx | pfc_en_rx;
}