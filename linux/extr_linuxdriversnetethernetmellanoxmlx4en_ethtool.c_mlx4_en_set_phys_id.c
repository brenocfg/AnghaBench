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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  port; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {TYPE_2__* dev; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;
struct TYPE_3__ {int flags2; } ;
struct TYPE_4__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_ID_ACTIVE 129 
#define  ETHTOOL_ID_INACTIVE 128 
 int MLX4_DEV_CAP_FLAG2_PORT_BEACON ; 
 int /*<<< orphan*/  PORT_BEACON_MAX_LIMIT ; 
 int mlx4_SET_PORT_BEACON (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_set_phys_id(struct net_device *dev,
			       enum ethtool_phys_id_state state)
{
	int err;
	u16 beacon_duration;
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;

	if (!(mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PORT_BEACON))
		return -EOPNOTSUPP;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		beacon_duration = PORT_BEACON_MAX_LIMIT;
		break;
	case ETHTOOL_ID_INACTIVE:
		beacon_duration = 0;
		break;
	default:
		return -EOPNOTSUPP;
	}

	err = mlx4_SET_PORT_BEACON(mdev->dev, priv->port, beacon_duration);
	return err;
}