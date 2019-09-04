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
typedef  int /*<<< orphan*/  u32 ;
struct qpn_to_netdev {int /*<<< orphan*/  hlist; } ;
struct net_device {int dummy; } ;
struct mlx5i_priv {struct mlx5i_pkey_qpn_ht* qpn_htbl; } ;
struct mlx5i_pkey_qpn_ht {int /*<<< orphan*/  ht_lock; int /*<<< orphan*/  buckets; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; struct mlx5i_priv* ppriv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qpn_to_netdev*) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*) ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 struct qpn_to_netdev* mlx5i_find_qpn_to_netdev_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mlx5i_pkey_del_qpn(struct net_device *netdev, u32 qpn)
{
	struct mlx5e_priv *epriv = mlx5i_epriv(netdev);
	struct mlx5i_priv *ipriv = epriv->ppriv;
	struct mlx5i_pkey_qpn_ht *ht = ipriv->qpn_htbl;
	struct qpn_to_netdev *node;

	node = mlx5i_find_qpn_to_netdev_node(ht->buckets, qpn);
	if (!node) {
		mlx5_core_warn(epriv->mdev, "QPN to netdev delete from HT failed\n");
		return -EINVAL;
	}

	spin_lock_bh(&ht->ht_lock);
	hlist_del_init(&node->hlist);
	spin_unlock_bh(&ht->ht_lock);
	kfree(node);

	return 0;
}