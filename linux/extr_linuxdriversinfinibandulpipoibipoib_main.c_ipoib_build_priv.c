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
struct ipoib_dev_priv {int /*<<< orphan*/  neigh_reap_task; int /*<<< orphan*/  ah_reap_task; int /*<<< orphan*/  restart_task; int /*<<< orphan*/  flush_heavy; int /*<<< orphan*/  flush_normal; int /*<<< orphan*/  flush_light; int /*<<< orphan*/  carrier_on_task; int /*<<< orphan*/  mcast_task; int /*<<< orphan*/  multicast_list; int /*<<< orphan*/  dead_ahs; int /*<<< orphan*/  child_intfs; int /*<<< orphan*/  path_list; int /*<<< orphan*/  mcast_mutex; int /*<<< orphan*/  vlan_rwsem; int /*<<< orphan*/  lock; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_ib_dev_flush_heavy ; 
 int /*<<< orphan*/  ipoib_ib_dev_flush_light ; 
 int /*<<< orphan*/  ipoib_ib_dev_flush_normal ; 
 int /*<<< orphan*/  ipoib_mcast_carrier_on_task ; 
 int /*<<< orphan*/  ipoib_mcast_join_task ; 
 int /*<<< orphan*/  ipoib_mcast_restart_task ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_reap_ah ; 
 int /*<<< orphan*/  ipoib_reap_neigh ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_build_priv(struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	priv->dev = dev;
	spin_lock_init(&priv->lock);
	init_rwsem(&priv->vlan_rwsem);
	mutex_init(&priv->mcast_mutex);

	INIT_LIST_HEAD(&priv->path_list);
	INIT_LIST_HEAD(&priv->child_intfs);
	INIT_LIST_HEAD(&priv->dead_ahs);
	INIT_LIST_HEAD(&priv->multicast_list);

	INIT_DELAYED_WORK(&priv->mcast_task,   ipoib_mcast_join_task);
	INIT_WORK(&priv->carrier_on_task, ipoib_mcast_carrier_on_task);
	INIT_WORK(&priv->flush_light,   ipoib_ib_dev_flush_light);
	INIT_WORK(&priv->flush_normal,   ipoib_ib_dev_flush_normal);
	INIT_WORK(&priv->flush_heavy,   ipoib_ib_dev_flush_heavy);
	INIT_WORK(&priv->restart_task, ipoib_mcast_restart_task);
	INIT_DELAYED_WORK(&priv->ah_reap_task, ipoib_reap_ah);
	INIT_DELAYED_WORK(&priv->neigh_reap_task, ipoib_reap_neigh);
}