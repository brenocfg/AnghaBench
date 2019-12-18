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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct emac_adapter {TYPE_1__ stats; } ;

/* Variables and functions */
 int EMAC_STATS_LEN ; 
 int /*<<< orphan*/  emac_update_hw_stats (struct emac_adapter*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void emac_get_ethtool_stats(struct net_device *netdev,
				   struct ethtool_stats *stats,
				   u64 *data)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	spin_lock(&adpt->stats.lock);

	emac_update_hw_stats(adpt);
	memcpy(data, &adpt->stats, EMAC_STATS_LEN * sizeof(u64));

	spin_unlock(&adpt->stats.lock);
}