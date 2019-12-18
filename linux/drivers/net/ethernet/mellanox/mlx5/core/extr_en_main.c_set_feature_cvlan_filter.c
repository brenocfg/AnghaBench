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
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_disable_cvlan_filter (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_enable_cvlan_filter (struct mlx5e_priv*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int set_feature_cvlan_filter(struct net_device *netdev, bool enable)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	if (enable)
		mlx5e_enable_cvlan_filter(priv);
	else
		mlx5e_disable_cvlan_filter(priv);

	return 0;
}