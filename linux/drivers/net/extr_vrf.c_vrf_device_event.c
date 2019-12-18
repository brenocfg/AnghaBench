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
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned long NETDEV_UNREGISTER ; 
 int NOTIFY_DONE ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  netif_is_l3_slave (struct net_device*) ; 
 int /*<<< orphan*/  vrf_del_slave (struct net_device*,struct net_device*) ; 

__attribute__((used)) static int vrf_device_event(struct notifier_block *unused,
			    unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	/* only care about unregister events to drop slave references */
	if (event == NETDEV_UNREGISTER) {
		struct net_device *vrf_dev;

		if (!netif_is_l3_slave(dev))
			goto out;

		vrf_dev = netdev_master_upper_dev_get(dev);
		vrf_del_slave(vrf_dev, dev);
	}
out:
	return NOTIFY_DONE;
}