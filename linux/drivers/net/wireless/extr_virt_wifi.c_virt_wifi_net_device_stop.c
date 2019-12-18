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
struct virt_wifi_netdev_priv {int is_up; } ;
struct net_device {TYPE_1__* ieee80211_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 struct virt_wifi_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  virt_wifi_cancel_connect (struct net_device*) ; 
 int /*<<< orphan*/  virt_wifi_cancel_scan (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virt_wifi_net_device_stop(struct net_device *dev)
{
	struct virt_wifi_netdev_priv *n_priv = netdev_priv(dev);

	n_priv->is_up = false;

	if (!dev->ieee80211_ptr)
		return 0;

	virt_wifi_cancel_scan(dev->ieee80211_ptr->wiphy);
	virt_wifi_cancel_connect(dev);
	netif_carrier_off(dev);

	return 0;
}