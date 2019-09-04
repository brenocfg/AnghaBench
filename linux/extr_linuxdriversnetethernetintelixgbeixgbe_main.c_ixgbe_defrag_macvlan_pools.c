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
struct ixgbe_adapter {int /*<<< orphan*/  fwd_bitmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ixgbe_reassign_macvlan_pool ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_walk_all_upper_dev_rcu (struct net_device*,int /*<<< orphan*/ ,struct ixgbe_adapter*) ; 

__attribute__((used)) static void ixgbe_defrag_macvlan_pools(struct net_device *dev)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);

	/* flush any stale bits out of the fwd bitmask */
	bitmap_clear(adapter->fwd_bitmask, 1, 63);

	/* walk through upper devices reassigning pools */
	netdev_walk_all_upper_dev_rcu(dev, ixgbe_reassign_macvlan_pool,
				      adapter);
}