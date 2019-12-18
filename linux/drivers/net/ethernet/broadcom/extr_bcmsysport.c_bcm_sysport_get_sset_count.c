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
struct net_device {int num_tx_queues; } ;
struct bcm_sysport_stats {int /*<<< orphan*/  type; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  is_lite; } ;

/* Variables and functions */
 unsigned int BCM_SYSPORT_STATS_LEN ; 
 int EOPNOTSUPP ; 
#define  ETH_SS_STATS 128 
 int NUM_SYSPORT_TXQ_STAT ; 
 struct bcm_sysport_stats* bcm_sysport_gstrings_stats ; 
 int /*<<< orphan*/  bcm_sysport_lite_stat_valid (int /*<<< orphan*/ ) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bcm_sysport_get_sset_count(struct net_device *dev, int string_set)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	const struct bcm_sysport_stats *s;
	unsigned int i, j;

	switch (string_set) {
	case ETH_SS_STATS:
		for (i = 0, j = 0; i < BCM_SYSPORT_STATS_LEN; i++) {
			s = &bcm_sysport_gstrings_stats[i];
			if (priv->is_lite &&
			    !bcm_sysport_lite_stat_valid(s->type))
				continue;
			j++;
		}
		/* Include per-queue statistics */
		return j + dev->num_tx_queues * NUM_SYSPORT_TXQ_STAT;
	default:
		return -EOPNOTSUPP;
	}
}