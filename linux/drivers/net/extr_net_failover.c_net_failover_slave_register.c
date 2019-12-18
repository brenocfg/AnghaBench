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
typedef  int u32 ;
struct net_failover_info {int /*<<< orphan*/  primary_stats; int /*<<< orphan*/  primary_dev; int /*<<< orphan*/  standby_stats; int /*<<< orphan*/  standby_dev; } ;
struct TYPE_2__ {scalar_t__ parent; } ;
struct net_device {int mtu; int /*<<< orphan*/  name; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  min_mtu; TYPE_1__ dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NETDEV_JOIN ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int /*<<< orphan*/  dev_get_stats (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_mc_sync_multiple (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_mc_unsync (struct net_device*,struct net_device*) ; 
 int dev_open (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int dev_set_mtu (struct net_device*,int) ; 
 int /*<<< orphan*/  dev_uc_sync_multiple (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_uc_unsync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  net_failover_compute_features (struct net_device*) ; 
 int /*<<< orphan*/  net_failover_lower_state_changed (struct net_device*,struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*,int /*<<< orphan*/ ) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int vlan_vids_add_by_dev (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int net_failover_slave_register(struct net_device *slave_dev,
				       struct net_device *failover_dev)
{
	struct net_device *standby_dev, *primary_dev;
	struct net_failover_info *nfo_info;
	bool slave_is_standby;
	u32 orig_mtu;
	int err;

	/* Align MTU of slave with failover dev */
	orig_mtu = slave_dev->mtu;
	err = dev_set_mtu(slave_dev, failover_dev->mtu);
	if (err) {
		netdev_err(failover_dev, "unable to change mtu of %s to %u register failed\n",
			   slave_dev->name, failover_dev->mtu);
		goto done;
	}

	dev_hold(slave_dev);

	if (netif_running(failover_dev)) {
		err = dev_open(slave_dev, NULL);
		if (err && (err != -EBUSY)) {
			netdev_err(failover_dev, "Opening slave %s failed err:%d\n",
				   slave_dev->name, err);
			goto err_dev_open;
		}
	}

	netif_addr_lock_bh(failover_dev);
	dev_uc_sync_multiple(slave_dev, failover_dev);
	dev_mc_sync_multiple(slave_dev, failover_dev);
	netif_addr_unlock_bh(failover_dev);

	err = vlan_vids_add_by_dev(slave_dev, failover_dev);
	if (err) {
		netdev_err(failover_dev, "Failed to add vlan ids to device %s err:%d\n",
			   slave_dev->name, err);
		goto err_vlan_add;
	}

	nfo_info = netdev_priv(failover_dev);
	standby_dev = rtnl_dereference(nfo_info->standby_dev);
	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	slave_is_standby = slave_dev->dev.parent == failover_dev->dev.parent;

	if (slave_is_standby) {
		rcu_assign_pointer(nfo_info->standby_dev, slave_dev);
		standby_dev = slave_dev;
		dev_get_stats(standby_dev, &nfo_info->standby_stats);
	} else {
		rcu_assign_pointer(nfo_info->primary_dev, slave_dev);
		primary_dev = slave_dev;
		dev_get_stats(primary_dev, &nfo_info->primary_stats);
		failover_dev->min_mtu = slave_dev->min_mtu;
		failover_dev->max_mtu = slave_dev->max_mtu;
	}

	net_failover_lower_state_changed(slave_dev, primary_dev, standby_dev);
	net_failover_compute_features(failover_dev);

	call_netdevice_notifiers(NETDEV_JOIN, slave_dev);

	netdev_info(failover_dev, "failover %s slave:%s registered\n",
		    slave_is_standby ? "standby" : "primary", slave_dev->name);

	return 0;

err_vlan_add:
	dev_uc_unsync(slave_dev, failover_dev);
	dev_mc_unsync(slave_dev, failover_dev);
	dev_close(slave_dev);
err_dev_open:
	dev_put(slave_dev);
	dev_set_mtu(slave_dev, orig_mtu);
done:
	return err;
}