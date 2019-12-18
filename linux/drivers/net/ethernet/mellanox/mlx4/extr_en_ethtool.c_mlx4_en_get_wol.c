#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int port; TYPE_1__* mdev; } ;
struct mlx4_caps {int flags; scalar_t__* wol_port; } ;
struct ethtool_wolinfo {void* wolopts; void* supported; } ;
struct TYPE_4__ {struct mlx4_caps caps; } ;
struct TYPE_3__ {TYPE_2__* dev; } ;

/* Variables and functions */
 int MLX4_DEV_CAP_FLAG_WOL_PORT1 ; 
 int MLX4_DEV_CAP_FLAG_WOL_PORT2 ; 
 int MLX4_EN_WOL_ENABLED ; 
 int MLX4_EN_WOL_MAGIC ; 
 void* WAKE_MAGIC ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int mlx4_wol_read (TYPE_2__*,int*,size_t) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx4_en_get_wol(struct net_device *netdev,
			    struct ethtool_wolinfo *wol)
{
	struct mlx4_en_priv *priv = netdev_priv(netdev);
	struct mlx4_caps *caps = &priv->mdev->dev->caps;
	int err = 0;
	u64 config = 0;
	u64 mask;

	if ((priv->port < 1) || (priv->port > 2)) {
		en_err(priv, "Failed to get WoL information\n");
		return;
	}

	mask = (priv->port == 1) ? MLX4_DEV_CAP_FLAG_WOL_PORT1 :
		MLX4_DEV_CAP_FLAG_WOL_PORT2;

	if (!(caps->flags & mask)) {
		wol->supported = 0;
		wol->wolopts = 0;
		return;
	}

	if (caps->wol_port[priv->port])
		wol->supported = WAKE_MAGIC;
	else
		wol->supported = 0;

	err = mlx4_wol_read(priv->mdev->dev, &config, priv->port);
	if (err) {
		en_err(priv, "Failed to get WoL information\n");
		return;
	}

	if ((config & MLX4_EN_WOL_ENABLED) && (config & MLX4_EN_WOL_MAGIC))
		wol->wolopts = WAKE_MAGIC;
	else
		wol->wolopts = 0;
}