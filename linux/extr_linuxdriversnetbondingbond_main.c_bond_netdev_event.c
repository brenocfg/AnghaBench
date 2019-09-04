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
struct notifier_block {int dummy; } ;
struct net_device {int priv_flags; int flags; } ;

/* Variables and functions */
 int IFF_BONDING ; 
 int IFF_MASTER ; 
 int IFF_SLAVE ; 
 int NOTIFY_DONE ; 
 int bond_master_netdev_event (unsigned long,struct net_device*) ; 
 int bond_slave_netdev_event (unsigned long,struct net_device*) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int bond_netdev_event(struct notifier_block *this,
			     unsigned long event, void *ptr)
{
	struct net_device *event_dev = netdev_notifier_info_to_dev(ptr);

	netdev_dbg(event_dev, "event: %lx\n", event);

	if (!(event_dev->priv_flags & IFF_BONDING))
		return NOTIFY_DONE;

	if (event_dev->flags & IFF_MASTER) {
		int ret;

		netdev_dbg(event_dev, "IFF_MASTER\n");
		ret = bond_master_netdev_event(event, event_dev);
		if (ret != NOTIFY_DONE)
			return ret;
	}

	if (event_dev->flags & IFF_SLAVE) {
		netdev_dbg(event_dev, "IFF_SLAVE\n");
		return bond_slave_netdev_event(event, event_dev);
	}

	return NOTIFY_DONE;
}