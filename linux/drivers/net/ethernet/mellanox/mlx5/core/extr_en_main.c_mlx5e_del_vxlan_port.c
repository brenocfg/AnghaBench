#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct udp_tunnel_info {scalar_t__ type; int /*<<< orphan*/  port; } ;
struct net_device {int dummy; } ;
struct mlx5e_priv {TYPE_1__* mdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  vxlan; } ;

/* Variables and functions */
 scalar_t__ UDP_TUNNEL_TYPE_VXLAN ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_vxlan_allowed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_vxlan_queue_work (struct mlx5e_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

void mlx5e_del_vxlan_port(struct net_device *netdev, struct udp_tunnel_info *ti)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	if (ti->type != UDP_TUNNEL_TYPE_VXLAN)
		return;

	if (!mlx5_vxlan_allowed(priv->mdev->vxlan))
		return;

	mlx5e_vxlan_queue_work(priv, be16_to_cpu(ti->port), 0);
}