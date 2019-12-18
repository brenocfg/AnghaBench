#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct net_device {int features; } ;
struct mlx4_en_priv {TYPE_2__* mdev; } ;
struct TYPE_6__ {int flags2; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {TYPE_3__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ETH_RSS_HASH_TOP ; 
 scalar_t__ ETH_RSS_HASH_XOR ; 
 int MLX4_DEV_CAP_FLAG2_RSS_TOP ; 
 int MLX4_DEV_CAP_FLAG2_RSS_XOR ; 
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_check_rxfh_func(struct net_device *dev, u8 hfunc)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	/* check if requested function is supported by the device */
	if (hfunc == ETH_RSS_HASH_TOP) {
		if (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_TOP))
			return -EINVAL;
		if (!(dev->features & NETIF_F_RXHASH))
			en_warn(priv, "Toeplitz hash function should be used in conjunction with RX hashing for optimal performance\n");
		return 0;
	} else if (hfunc == ETH_RSS_HASH_XOR) {
		if (!(priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RSS_XOR))
			return -EINVAL;
		if (dev->features & NETIF_F_RXHASH)
			en_warn(priv, "Enabling both XOR Hash function and RX Hashing can limit RPS functionality\n");
		return 0;
	}

	return -EINVAL;
}