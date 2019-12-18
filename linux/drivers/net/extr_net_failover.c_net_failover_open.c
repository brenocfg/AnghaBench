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
struct net_failover_info {int /*<<< orphan*/  standby_dev; int /*<<< orphan*/  primary_dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int dev_open (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ net_failover_xmit_ready (struct net_device*) ; 
 struct net_failover_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 struct net_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_failover_open(struct net_device *dev)
{
	struct net_failover_info *nfo_info = netdev_priv(dev);
	struct net_device *primary_dev, *standby_dev;
	int err;

	primary_dev = rtnl_dereference(nfo_info->primary_dev);
	if (primary_dev) {
		err = dev_open(primary_dev, NULL);
		if (err)
			goto err_primary_open;
	}

	standby_dev = rtnl_dereference(nfo_info->standby_dev);
	if (standby_dev) {
		err = dev_open(standby_dev, NULL);
		if (err)
			goto err_standby_open;
	}

	if ((primary_dev && net_failover_xmit_ready(primary_dev)) ||
	    (standby_dev && net_failover_xmit_ready(standby_dev))) {
		netif_carrier_on(dev);
		netif_tx_wake_all_queues(dev);
	}

	return 0;

err_standby_open:
	dev_close(primary_dev);
err_primary_open:
	netif_tx_disable(dev);
	return err;
}