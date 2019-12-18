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
struct ipoib_dev_priv {struct net_device* parent; int /*<<< orphan*/ * wq; int /*<<< orphan*/  vlan_rwsem; int /*<<< orphan*/  list; int /*<<< orphan*/  child_intfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_ib_dev_cleanup (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_neigh_hash_uninit (struct net_device*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_ndo_uninit(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	ASSERT_RTNL();

	/*
	 * ipoib_remove_one guarantees the children are removed before the
	 * parent, and that is the only place where a parent can be removed.
	 */
	WARN_ON(!list_empty(&priv->child_intfs));

	if (priv->parent) {
		struct ipoib_dev_priv *ppriv = ipoib_priv(priv->parent);

		down_write(&ppriv->vlan_rwsem);
		list_del(&priv->list);
		up_write(&ppriv->vlan_rwsem);
	}

	ipoib_neigh_hash_uninit(dev);

	ipoib_ib_dev_cleanup(dev);

	/* no more works over the priv->wq */
	if (priv->wq) {
		flush_workqueue(priv->wq);
		destroy_workqueue(priv->wq);
		priv->wq = NULL;
	}

	if (priv->parent)
		dev_put(priv->parent);
}