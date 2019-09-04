#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {scalar_t__ netdev_ops; } ;
struct mlx5e_priv {TYPE_4__* mdev; TYPE_1__* netdev; } ;
struct TYPE_7__ {TYPE_3__* eswitch; } ;
struct TYPE_9__ {TYPE_2__ priv; } ;
struct TYPE_8__ {scalar_t__ mode; } ;
struct TYPE_6__ {scalar_t__ netdev_ops; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_ESW (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_VPORT_MANAGER (TYPE_4__*) ; 
 scalar_t__ SRIOV_OFFLOADS ; 
 int /*<<< orphan*/  merged_eswitch ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ same_hw_devs (struct mlx5e_priv*,struct mlx5e_priv*) ; 

__attribute__((used)) static bool is_merged_eswitch_dev(struct mlx5e_priv *priv,
				  struct net_device *peer_netdev)
{
	struct mlx5e_priv *peer_priv;

	peer_priv = netdev_priv(peer_netdev);

	return (MLX5_CAP_ESW(priv->mdev, merged_eswitch) &&
		(priv->netdev->netdev_ops == peer_netdev->netdev_ops) &&
		same_hw_devs(priv, peer_priv) &&
		MLX5_VPORT_MANAGER(peer_priv->mdev) &&
		(peer_priv->mdev->priv.eswitch->mode == SRIOV_OFFLOADS));
}