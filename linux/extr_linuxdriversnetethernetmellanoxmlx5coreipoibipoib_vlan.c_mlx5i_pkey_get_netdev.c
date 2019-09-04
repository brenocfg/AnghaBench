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
struct qpn_to_netdev {struct net_device* netdev; } ;
struct net_device {int dummy; } ;
struct mlx5i_priv {TYPE_1__* qpn_htbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  buckets; } ;

/* Variables and functions */
 struct qpn_to_netdev* mlx5i_find_qpn_to_netdev_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5i_priv* netdev_priv (struct net_device*) ; 

struct net_device *mlx5i_pkey_get_netdev(struct net_device *netdev, u32 qpn)
{
	struct mlx5i_priv *ipriv = netdev_priv(netdev);
	struct qpn_to_netdev *node;

	node = mlx5i_find_qpn_to_netdev_node(ipriv->qpn_htbl->buckets, qpn);
	if (!node)
		return NULL;

	return node->netdev;
}