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
struct net_device {TYPE_1__* netdev_ops; } ;
struct mlx5i_priv {int /*<<< orphan*/  qpn_htbl; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct mlx5i_priv* ppriv; } ;
struct TYPE_2__ {int (* ndo_get_iflink ) (struct net_device*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*) ; 
 int mlx5i_dev_init (struct net_device*) ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 struct mlx5i_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct net_device*) ; 

__attribute__((used)) static int mlx5i_pkey_dev_init(struct net_device *dev)
{
	struct mlx5e_priv *priv = mlx5i_epriv(dev);
	struct mlx5i_priv *ipriv, *parent_ipriv;
	struct net_device *parent_dev;
	int parent_ifindex;

	ipriv = priv->ppriv;

	/* Get QPN to netdevice hash table from parent */
	parent_ifindex = dev->netdev_ops->ndo_get_iflink(dev);
	parent_dev = dev_get_by_index(dev_net(dev), parent_ifindex);
	if (!parent_dev) {
		mlx5_core_warn(priv->mdev, "failed to get parent device\n");
		return -EINVAL;
	}

	parent_ipriv = netdev_priv(parent_dev);
	ipriv->qpn_htbl = parent_ipriv->qpn_htbl;
	dev_put(parent_dev);

	return mlx5i_dev_init(dev);
}