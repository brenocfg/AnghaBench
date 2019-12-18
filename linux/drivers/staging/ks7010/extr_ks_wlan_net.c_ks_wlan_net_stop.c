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
struct ks_wlan_private {int is_device_open; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  update_phyinfo_timer ; 

int ks_wlan_net_stop(struct net_device *dev)
{
	struct ks_wlan_private *priv = netdev_priv(dev);

	priv->is_device_open = false;
	del_timer_sync(&update_phyinfo_timer);

	if (netif_running(dev))
		netif_stop_queue(dev);

	return 0;
}