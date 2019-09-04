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
struct TYPE_2__ {int /*<<< orphan*/  rx_mcasts; int /*<<< orphan*/  tx_mcasts; int /*<<< orphan*/  rx_bcasts; int /*<<< orphan*/  tx_bcasts; int /*<<< orphan*/  tx_aborted; int /*<<< orphan*/  tx_deferred_excessive; int /*<<< orphan*/  tx_deferred; int /*<<< orphan*/  tx_late_collisions; int /*<<< orphan*/  tx_single_collisions; int /*<<< orphan*/  tx_multiple_collisions; } ;
struct netdev_private {TYPE_1__ xstats; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_stats (struct net_device*) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void get_ethtool_stats(struct net_device *dev,
		struct ethtool_stats *stats, u64 *data)
{
	struct netdev_private *np = netdev_priv(dev);
	int i = 0;

	get_stats(dev);
	data[i++] = np->xstats.tx_multiple_collisions;
	data[i++] = np->xstats.tx_single_collisions;
	data[i++] = np->xstats.tx_late_collisions;
	data[i++] = np->xstats.tx_deferred;
	data[i++] = np->xstats.tx_deferred_excessive;
	data[i++] = np->xstats.tx_aborted;
	data[i++] = np->xstats.tx_bcasts;
	data[i++] = np->xstats.rx_bcasts;
	data[i++] = np->xstats.tx_mcasts;
	data[i++] = np->xstats.rx_mcasts;
}