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
struct mlx5e_priv {int /*<<< orphan*/  mdev; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VPORT_STATE_OP_MOD_VNIC_VPORT ; 
 scalar_t__ VPORT_STATE_UP ; 
 scalar_t__ mlx5_query_vport_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_test_link_state(struct mlx5e_priv *priv)
{
	u8 port_state;

	if (!netif_carrier_ok(priv->netdev))
		return 1;

	port_state = mlx5_query_vport_state(priv->mdev, MLX5_VPORT_STATE_OP_MOD_VNIC_VPORT, 0);
	return port_state == VPORT_STATE_UP ? 0 : 1;
}