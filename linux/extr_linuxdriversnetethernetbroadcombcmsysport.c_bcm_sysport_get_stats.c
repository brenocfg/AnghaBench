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
typedef  void* u64 ;
typedef  void* u32 ;
struct u64_stats_sync {int dummy; } ;
struct net_device {int num_tx_queues; int /*<<< orphan*/  stats; } ;
struct ethtool_stats {int dummy; } ;
struct bcm_sysport_tx_ring {void* bytes; void* packets; } ;
struct bcm_sysport_stats64 {void* tx_packets; void* tx_bytes; } ;
struct bcm_sysport_stats {scalar_t__ type; int stat_sizeof; int /*<<< orphan*/  stat_offset; } ;
struct bcm_sysport_priv {struct bcm_sysport_tx_ring* tx_rings; scalar_t__ is_lite; struct u64_stats_sync syncp; struct bcm_sysport_stats64 stats64; } ;

/* Variables and functions */
 int BCM_SYSPORT_STATS_LEN ; 
 scalar_t__ BCM_SYSPORT_STAT_NETDEV ; 
 scalar_t__ BCM_SYSPORT_STAT_NETDEV64 ; 
 int /*<<< orphan*/  ETH_SS_STATS ; 
 int NUM_SYSPORT_TXQ_STAT ; 
 int bcm_sysport_get_sset_count (struct net_device*,int /*<<< orphan*/ ) ; 
 struct bcm_sysport_stats* bcm_sysport_gstrings_stats ; 
 int /*<<< orphan*/  bcm_sysport_lite_stat_valid (scalar_t__) ; 
 int /*<<< orphan*/  bcm_sysport_update_mib_counters (struct bcm_sysport_priv*) ; 
 int /*<<< orphan*/  bcm_sysport_update_tx_stats (struct bcm_sysport_priv*,void**,void**) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 unsigned int u64_stats_fetch_begin_irq (struct u64_stats_sync*) ; 
 scalar_t__ u64_stats_fetch_retry_irq (struct u64_stats_sync*,unsigned int) ; 

__attribute__((used)) static void bcm_sysport_get_stats(struct net_device *dev,
				  struct ethtool_stats *stats, u64 *data)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	struct bcm_sysport_stats64 *stats64 = &priv->stats64;
	struct u64_stats_sync *syncp = &priv->syncp;
	struct bcm_sysport_tx_ring *ring;
	u64 tx_bytes = 0, tx_packets = 0;
	unsigned int start;
	int i, j;

	if (netif_running(dev)) {
		bcm_sysport_update_mib_counters(priv);
		bcm_sysport_update_tx_stats(priv, &tx_bytes, &tx_packets);
		stats64->tx_bytes = tx_bytes;
		stats64->tx_packets = tx_packets;
	}

	for (i =  0, j = 0; i < BCM_SYSPORT_STATS_LEN; i++) {
		const struct bcm_sysport_stats *s;
		char *p;

		s = &bcm_sysport_gstrings_stats[i];
		if (s->type == BCM_SYSPORT_STAT_NETDEV)
			p = (char *)&dev->stats;
		else if (s->type == BCM_SYSPORT_STAT_NETDEV64)
			p = (char *)stats64;
		else
			p = (char *)priv;

		if (priv->is_lite && !bcm_sysport_lite_stat_valid(s->type))
			continue;
		p += s->stat_offset;

		if (s->stat_sizeof == sizeof(u64) &&
		    s->type == BCM_SYSPORT_STAT_NETDEV64) {
			do {
				start = u64_stats_fetch_begin_irq(syncp);
				data[i] = *(u64 *)p;
			} while (u64_stats_fetch_retry_irq(syncp, start));
		} else
			data[i] = *(u32 *)p;
		j++;
	}

	/* For SYSTEMPORT Lite since we have holes in our statistics, j would
	 * be equal to BCM_SYSPORT_STATS_LEN at the end of the loop, but it
	 * needs to point to how many total statistics we have minus the
	 * number of per TX queue statistics
	 */
	j = bcm_sysport_get_sset_count(dev, ETH_SS_STATS) -
	    dev->num_tx_queues * NUM_SYSPORT_TXQ_STAT;

	for (i = 0; i < dev->num_tx_queues; i++) {
		ring = &priv->tx_rings[i];
		data[j] = ring->packets;
		j++;
		data[j] = ring->bytes;
		j++;
	}
}