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
struct net_device {int /*<<< orphan*/  features; void* max_mtu; void* min_mtu; void* mtu; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  watchdog_timeo; } ;

/* Variables and functions */
 int /*<<< orphan*/  FJES_TX_RETRY_INTERVAL ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  fjes_netdev_ops ; 
 int /*<<< orphan*/  fjes_set_ethtool_ops (struct net_device*) ; 
 void** fjes_support_mtu ; 

__attribute__((used)) static void fjes_netdev_setup(struct net_device *netdev)
{
	ether_setup(netdev);

	netdev->watchdog_timeo = FJES_TX_RETRY_INTERVAL;
	netdev->netdev_ops = &fjes_netdev_ops;
	fjes_set_ethtool_ops(netdev);
	netdev->mtu = fjes_support_mtu[3];
	netdev->min_mtu = fjes_support_mtu[0];
	netdev->max_mtu = fjes_support_mtu[3];
	netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
}