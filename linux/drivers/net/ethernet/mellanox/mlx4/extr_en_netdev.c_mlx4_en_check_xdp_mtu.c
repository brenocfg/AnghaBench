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
struct mlx4_en_priv {int dummy; } ;

/* Variables and functions */
 int MLX4_EN_MAX_XDP_MTU ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,int,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static bool mlx4_en_check_xdp_mtu(struct net_device *dev, int mtu)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	if (mtu > MLX4_EN_MAX_XDP_MTU) {
		en_err(priv, "mtu:%d > max:%d when XDP prog is attached\n",
		       mtu, MLX4_EN_MAX_XDP_MTU);
		return false;
	}

	return true;
}