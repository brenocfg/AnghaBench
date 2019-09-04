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
struct nic {int /*<<< orphan*/  flags; int /*<<< orphan*/  netdev; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 scalar_t__ E100_MAX_MULTICAST_ADDRS ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  e100_configure ; 
 int /*<<< orphan*/  e100_exec_cb (struct nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e100_multi ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  multicast_all ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_printk (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  promiscuous ; 

__attribute__((used)) static void e100_set_multicast_list(struct net_device *netdev)
{
	struct nic *nic = netdev_priv(netdev);

	netif_printk(nic, hw, KERN_DEBUG, nic->netdev,
		     "mc_count=%d, flags=0x%04X\n",
		     netdev_mc_count(netdev), netdev->flags);

	if (netdev->flags & IFF_PROMISC)
		nic->flags |= promiscuous;
	else
		nic->flags &= ~promiscuous;

	if (netdev->flags & IFF_ALLMULTI ||
		netdev_mc_count(netdev) > E100_MAX_MULTICAST_ADDRS)
		nic->flags |= multicast_all;
	else
		nic->flags &= ~multicast_all;

	e100_exec_cb(nic, NULL, e100_configure);
	e100_exec_cb(nic, NULL, e100_multi);
}