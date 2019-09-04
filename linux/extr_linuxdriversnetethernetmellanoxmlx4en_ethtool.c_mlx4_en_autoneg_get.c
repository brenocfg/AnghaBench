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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int flags; } ;
struct mlx4_en_priv {TYPE_3__ port_state; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {TYPE_2__* dev; } ;
struct TYPE_4__ {int flags2; } ;
struct TYPE_5__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int MLX4_DEV_CAP_FLAG2_ETH_BACKPL_AN_REP ; 
 int MLX4_EN_PORT_ANE ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 mlx4_en_autoneg_get(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	u32 autoneg = AUTONEG_DISABLE;

	if ((mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ETH_BACKPL_AN_REP) &&
	    (priv->port_state.flags & MLX4_EN_PORT_ANE))
		autoneg = AUTONEG_ENABLE;

	return autoneg;
}