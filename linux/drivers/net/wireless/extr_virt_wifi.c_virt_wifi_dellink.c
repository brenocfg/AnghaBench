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
struct virt_wifi_netdev_priv {int being_deleted; int /*<<< orphan*/  lowerdev; } ;
struct net_device {TYPE_1__* ieee80211_ptr; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct virt_wifi_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_upper_dev_unlink (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdevice_queue (struct net_device*,struct list_head*) ; 
 int /*<<< orphan*/  virt_wifi_cancel_connect (struct net_device*) ; 
 int /*<<< orphan*/  virt_wifi_cancel_scan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virt_wifi_dellink(struct net_device *dev,
			      struct list_head *head)
{
	struct virt_wifi_netdev_priv *priv = netdev_priv(dev);

	if (dev->ieee80211_ptr)
		virt_wifi_cancel_scan(dev->ieee80211_ptr->wiphy);

	priv->being_deleted = true;
	virt_wifi_cancel_connect(dev);
	netif_carrier_off(dev);

	netdev_rx_handler_unregister(priv->lowerdev);
	netdev_upper_dev_unlink(priv->lowerdev, dev);

	unregister_netdevice_queue(dev, head);
	module_put(THIS_MODULE);

	/* Deleting the wiphy is handled in the module destructor. */
}