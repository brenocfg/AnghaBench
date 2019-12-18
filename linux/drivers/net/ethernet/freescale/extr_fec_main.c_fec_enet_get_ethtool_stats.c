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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct fec_enet_private {int /*<<< orphan*/  ethtool_stats; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEC_STATS_SIZE ; 
 int /*<<< orphan*/  fec_enet_update_ethtool_stats (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static void fec_enet_get_ethtool_stats(struct net_device *dev,
				       struct ethtool_stats *stats, u64 *data)
{
	struct fec_enet_private *fep = netdev_priv(dev);

	if (netif_running(dev))
		fec_enet_update_ethtool_stats(dev);

	memcpy(data, fep->ethtool_stats, FEC_STATS_SIZE);
}