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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct mlx5e_priv {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ ETH_P_8021AD ; 
 scalar_t__ ETH_P_8021Q ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int mlx5e_vlan_rx_add_cvid (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int mlx5e_vlan_rx_add_svid (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

int mlx5e_vlan_rx_add_vid(struct net_device *dev, __be16 proto, u16 vid)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	if (be16_to_cpu(proto) == ETH_P_8021Q)
		return mlx5e_vlan_rx_add_cvid(priv, vid);
	else if (be16_to_cpu(proto) == ETH_P_8021AD)
		return mlx5e_vlan_rx_add_svid(priv, vid);

	return -EOPNOTSUPP;
}