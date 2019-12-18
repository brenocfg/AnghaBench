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
struct pcmcia_device {scalar_t__ priv; } ;
struct net_device {int dummy; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct TYPE_2__ {scalar_t__ num_dev_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_EXTRA ; 
 int ENODEV ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  prism2_suspend (struct net_device*) ; 

__attribute__((used)) static int hostap_cs_suspend(struct pcmcia_device *link)
{
	struct net_device *dev = (struct net_device *) link->priv;
	int dev_open = 0;
	struct hostap_interface *iface = NULL;

	if (!dev)
		return -ENODEV;

	iface = netdev_priv(dev);

	PDEBUG(DEBUG_EXTRA, "%s: CS_EVENT_PM_SUSPEND\n", dev_info);
	if (iface && iface->local)
		dev_open = iface->local->num_dev_open > 0;
	if (dev_open) {
		netif_stop_queue(dev);
		netif_device_detach(dev);
	}
	prism2_suspend(dev);

	return 0;
}