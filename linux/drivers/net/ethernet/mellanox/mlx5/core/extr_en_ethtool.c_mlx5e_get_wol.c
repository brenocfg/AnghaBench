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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ethtool_wolinfo*,int /*<<< orphan*/ ,int) ; 
 int mlx5_query_port_wol (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_get_wol_supported (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5e_reformat_wol_mode_mlx5_to_linux (int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx5e_get_wol(struct net_device *netdev,
			  struct ethtool_wolinfo *wol)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5_core_dev *mdev = priv->mdev;
	u8 mlx5_wol_mode;
	int err;

	memset(wol, 0, sizeof(*wol));

	wol->supported = mlx5e_get_wol_supported(mdev);
	if (!wol->supported)
		return;

	err = mlx5_query_port_wol(mdev, &mlx5_wol_mode);
	if (err)
		return;

	wol->wolopts = mlx5e_reformat_wol_mode_mlx5_to_linux(mlx5_wol_mode);
}