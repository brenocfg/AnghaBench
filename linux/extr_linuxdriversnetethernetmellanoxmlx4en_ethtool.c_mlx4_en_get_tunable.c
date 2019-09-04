#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {TYPE_1__* prof; } ;
struct ethtool_tunable {int id; } ;
struct TYPE_2__ {int /*<<< orphan*/  inline_thold; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_TX_COPYBREAK 128 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_get_tunable(struct net_device *dev,
			       const struct ethtool_tunable *tuna,
			       void *data)
{
	const struct mlx4_en_priv *priv = netdev_priv(dev);
	int ret = 0;

	switch (tuna->id) {
	case ETHTOOL_TX_COPYBREAK:
		*(u32 *)data = priv->prof->inline_thold;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}