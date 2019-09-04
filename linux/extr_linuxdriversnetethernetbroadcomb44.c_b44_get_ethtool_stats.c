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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct b44_hw_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_good_octets; } ;
struct b44 {int /*<<< orphan*/  lock; struct b44_hw_stats hw_stats; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b44_gstrings ; 
 int /*<<< orphan*/  b44_stats_update (struct b44*) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 unsigned int u64_stats_fetch_begin_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ u64_stats_fetch_retry_irq (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void b44_get_ethtool_stats(struct net_device *dev,
				  struct ethtool_stats *stats, u64 *data)
{
	struct b44 *bp = netdev_priv(dev);
	struct b44_hw_stats *hwstat = &bp->hw_stats;
	u64 *data_src, *data_dst;
	unsigned int start;
	u32 i;

	spin_lock_irq(&bp->lock);
	b44_stats_update(bp);
	spin_unlock_irq(&bp->lock);

	do {
		data_src = &hwstat->tx_good_octets;
		data_dst = data;
		start = u64_stats_fetch_begin_irq(&hwstat->syncp);

		for (i = 0; i < ARRAY_SIZE(b44_gstrings); i++)
			*data_dst++ = *data_src++;

	} while (u64_stats_fetch_retry_irq(&hwstat->syncp, start));
}