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
struct mlx5e_profile {int /*<<< orphan*/  (* cleanup ) (struct mlx5e_priv*) ;} ;
struct mlx5e_priv {struct net_device* netdev; struct mlx5e_profile* profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct mlx5e_priv*) ; 

void mlx5e_destroy_netdev(struct mlx5e_priv *priv)
{
	const struct mlx5e_profile *profile = priv->profile;
	struct net_device *netdev = priv->netdev;

	if (profile->cleanup)
		profile->cleanup(priv);
	free_netdev(netdev);
}