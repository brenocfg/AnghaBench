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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 struct net_device* __dev_get_by_index (struct net*,int) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static
struct mlx5_core_dev *mlx5e_hairpin_get_mdev(struct net *net, int ifindex)
{
	struct net_device *netdev;
	struct mlx5e_priv *priv;

	netdev = __dev_get_by_index(net, ifindex);
	priv = netdev_priv(netdev);
	return priv->mdev;
}