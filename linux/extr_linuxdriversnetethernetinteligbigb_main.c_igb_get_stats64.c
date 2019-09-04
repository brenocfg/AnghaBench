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
struct rtnl_link_stats64 {int dummy; } ;
struct net_device {int dummy; } ;
struct igb_adapter {int /*<<< orphan*/  stats64_lock; int /*<<< orphan*/  stats64; } ;

/* Variables and functions */
 int /*<<< orphan*/  igb_update_stats (struct igb_adapter*) ; 
 int /*<<< orphan*/  memcpy (struct rtnl_link_stats64*,int /*<<< orphan*/ *,int) ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igb_get_stats64(struct net_device *netdev,
			    struct rtnl_link_stats64 *stats)
{
	struct igb_adapter *adapter = netdev_priv(netdev);

	spin_lock(&adapter->stats64_lock);
	igb_update_stats(adapter);
	memcpy(stats, &adapter->stats64, sizeof(*stats));
	spin_unlock(&adapter->stats64_lock);
}