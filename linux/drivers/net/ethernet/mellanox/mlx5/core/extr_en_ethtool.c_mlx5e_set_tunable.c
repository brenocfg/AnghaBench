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
struct mlx5e_priv {int /*<<< orphan*/  state_lock; } ;
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHTOOL_PFC_PREVENTION_TOUT 128 
 int mlx5e_set_pfc_prevention_tout (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_set_tunable(struct net_device *dev,
			     const struct ethtool_tunable *tuna,
			     const void *data)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	int err;

	mutex_lock(&priv->state_lock);

	switch (tuna->id) {
	case ETHTOOL_PFC_PREVENTION_TOUT:
		err = mlx5e_set_pfc_prevention_tout(dev, *(u16 *)data);
		break;
	default:
		err = -EINVAL;
		break;
	}

	mutex_unlock(&priv->state_lock);
	return err;
}