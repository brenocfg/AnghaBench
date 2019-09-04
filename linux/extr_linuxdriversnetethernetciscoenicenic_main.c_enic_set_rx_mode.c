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
struct net_device {int flags; } ;
struct enic {unsigned int flags; } ;

/* Variables and functions */
 scalar_t__ ENIC_MULTICAST_PERFECT_FILTERS ; 
 scalar_t__ ENIC_UNICAST_PERFECT_FILTERS ; 
 unsigned int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 unsigned int IFF_PROMISC ; 
 int /*<<< orphan*/  __dev_mc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dev_uc_sync (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enic_dev_packet_filter (struct enic*,int,int,int,int,int) ; 
 int /*<<< orphan*/  enic_mc_sync ; 
 int /*<<< orphan*/  enic_mc_unsync ; 
 int /*<<< orphan*/  enic_uc_sync ; 
 int /*<<< orphan*/  enic_uc_unsync ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 scalar_t__ netdev_uc_count (struct net_device*) ; 

__attribute__((used)) static void enic_set_rx_mode(struct net_device *netdev)
{
	struct enic *enic = netdev_priv(netdev);
	int directed = 1;
	int multicast = (netdev->flags & IFF_MULTICAST) ? 1 : 0;
	int broadcast = (netdev->flags & IFF_BROADCAST) ? 1 : 0;
	int promisc = (netdev->flags & IFF_PROMISC) ||
		netdev_uc_count(netdev) > ENIC_UNICAST_PERFECT_FILTERS;
	int allmulti = (netdev->flags & IFF_ALLMULTI) ||
		netdev_mc_count(netdev) > ENIC_MULTICAST_PERFECT_FILTERS;
	unsigned int flags = netdev->flags |
		(allmulti ? IFF_ALLMULTI : 0) |
		(promisc ? IFF_PROMISC : 0);

	if (enic->flags != flags) {
		enic->flags = flags;
		enic_dev_packet_filter(enic, directed,
			multicast, broadcast, promisc, allmulti);
	}

	if (!promisc) {
		__dev_uc_sync(netdev, enic_uc_sync, enic_uc_unsync);
		if (!allmulti)
			__dev_mc_sync(netdev, enic_mc_sync, enic_mc_unsync);
	}
}