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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
typedef  int __u32 ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int mlx5_set_port_wol (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int mlx5e_get_wol_supported (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5e_reformat_wol_mode_linux_to_mlx5 (int) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_set_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5_core_dev *mdev = priv->mdev;
	__u32 wol_supported = mlx5e_get_wol_supported(mdev);
	u32 mlx5_wol_mode;

	if (!wol_supported)
		return -EOPNOTSUPP;

	if (wol->wolopts & ~wol_supported)
		return -EINVAL;

	mlx5_wol_mode = mlx5e_reformat_wol_mode_linux_to_mlx5(wol->wolopts);

	return mlx5_set_port_wol(mdev, mlx5_wol_mode);
}