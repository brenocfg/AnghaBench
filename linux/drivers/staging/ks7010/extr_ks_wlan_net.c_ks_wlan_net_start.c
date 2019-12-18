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
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * wireless_handlers; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  dev_addr; } ;
struct ks_wlan_private {int mac_address_valid; int is_device_open; int /*<<< orphan*/  eth_addr; scalar_t__ need_commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_TIMEOUT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dummy_addr ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_wlan_handler_def ; 
 int /*<<< orphan*/  ks_wlan_netdev_ops ; 
 int /*<<< orphan*/  ks_wlan_update_phyinfo_timeout ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_phyinfo ; 
 int /*<<< orphan*/  update_phyinfo_timer ; 

int ks_wlan_net_start(struct net_device *dev)
{
	struct ks_wlan_private *priv;
	/* int rc; */

	priv = netdev_priv(dev);
	priv->mac_address_valid = false;
	priv->is_device_open = true;
	priv->need_commit = 0;
	/* phy information update timer */
	atomic_set(&update_phyinfo, 0);
	timer_setup(&update_phyinfo_timer, ks_wlan_update_phyinfo_timeout, 0);

	/* dummy address set */
	ether_addr_copy(priv->eth_addr, dummy_addr);
	ether_addr_copy(dev->dev_addr, priv->eth_addr);

	/* The ks_wlan-specific entries in the device structure. */
	dev->netdev_ops = &ks_wlan_netdev_ops;
	dev->wireless_handlers = &ks_wlan_handler_def;
	dev->watchdog_timeo = TX_TIMEOUT;

	netif_carrier_off(dev);

	return 0;
}