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
struct lapbethdev {int /*<<< orphan*/  axdev; } ;

/* Variables and functions */
#define  NETDEV_DOWN 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  dev_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_is_ethdev (struct net_device*) ; 
 int /*<<< orphan*/ * dev_net (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  lapbeth_free_device (struct lapbethdev*) ; 
 struct lapbethdev* lapbeth_get_x25_dev (struct net_device*) ; 
 int /*<<< orphan*/  lapbeth_new_device (struct net_device*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int lapbeth_device_event(struct notifier_block *this,
				unsigned long event, void *ptr)
{
	struct lapbethdev *lapbeth;
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	if (dev_net(dev) != &init_net)
		return NOTIFY_DONE;

	if (!dev_is_ethdev(dev))
		return NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		/* New ethernet device -> new LAPB interface	 */
		if (lapbeth_get_x25_dev(dev) == NULL)
			lapbeth_new_device(dev);
		break;
	case NETDEV_DOWN:	
		/* ethernet device closed -> close LAPB interface */
		lapbeth = lapbeth_get_x25_dev(dev);
		if (lapbeth) 
			dev_close(lapbeth->axdev);
		break;
	case NETDEV_UNREGISTER:
		/* ethernet device disappears -> remove LAPB interface */
		lapbeth = lapbeth_get_x25_dev(dev);
		if (lapbeth)
			lapbeth_free_device(lapbeth);
		break;
	}

	return NOTIFY_DONE;
}