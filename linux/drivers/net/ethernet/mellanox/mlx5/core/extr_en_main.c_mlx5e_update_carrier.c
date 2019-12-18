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
struct mlx5e_priv {int /*<<< orphan*/  netdev; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VPORT_STATE_OP_MOD_VNIC_VPORT ; 
 scalar_t__ VPORT_STATE_UP ; 
 scalar_t__ mlx5_query_vport_state (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

void mlx5e_update_carrier(struct mlx5e_priv *priv)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	u8 port_state;

	port_state = mlx5_query_vport_state(mdev,
					    MLX5_VPORT_STATE_OP_MOD_VNIC_VPORT,
					    0);

	if (port_state == VPORT_STATE_UP) {
		netdev_info(priv->netdev, "Link up\n");
		netif_carrier_on(priv->netdev);
	} else {
		netdev_info(priv->netdev, "Link down\n");
		netif_carrier_off(priv->netdev);
	}
}