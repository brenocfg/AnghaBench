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
struct net_device_stats {scalar_t__ tx_dropped; scalar_t__ rx_dropped; scalar_t__ tx_errors; scalar_t__ rx_errors; scalar_t__ tx_bytes; scalar_t__ rx_bytes; scalar_t__ tx_packets; scalar_t__ rx_packets; scalar_t__ rx_crc_errors; scalar_t__ rx_length_errors; scalar_t__ tx_fifo_errors; scalar_t__ tx_aborted_errors; scalar_t__ rx_fifo_errors; scalar_t__ rx_frame_errors; scalar_t__ rx_over_errors; scalar_t__ collisions; } ;
struct net_device {int dummy; } ;
struct cas {int /*<<< orphan*/ * stat_lock; scalar_t__ regs; int /*<<< orphan*/  hw_running; struct net_device_stats* net_stats; } ;

/* Variables and functions */
 int N_TX_RINGS ; 
 scalar_t__ REG_MAC_ALIGN_ERR ; 
 scalar_t__ REG_MAC_COLL_EXCESS ; 
 scalar_t__ REG_MAC_COLL_LATE ; 
 scalar_t__ REG_MAC_COLL_NORMAL ; 
 scalar_t__ REG_MAC_FCS_ERR ; 
 scalar_t__ REG_MAC_LEN_ERR ; 
 int /*<<< orphan*/  cas_clear_mac_err (struct cas*) ; 
 int /*<<< orphan*/  memset (struct net_device_stats*,int /*<<< orphan*/ ,int) ; 
 struct cas* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct net_device_stats *cas_get_stats(struct net_device *dev)
{
	struct cas *cp = netdev_priv(dev);
	struct net_device_stats *stats = cp->net_stats;
	unsigned long flags;
	int i;
	unsigned long tmp;

	/* we collate all of the stats into net_stats[N_TX_RING] */
	if (!cp->hw_running)
		return stats + N_TX_RINGS;

	/* collect outstanding stats */
	/* WTZ: the Cassini spec gives these as 16 bit counters but
	 * stored in 32-bit words.  Added a mask of 0xffff to be safe,
	 * in case the chip somehow puts any garbage in the other bits.
	 * Also, counter usage didn't seem to mach what Adrian did
	 * in the parts of the code that set these quantities. Made
	 * that consistent.
	 */
	spin_lock_irqsave(&cp->stat_lock[N_TX_RINGS], flags);
	stats[N_TX_RINGS].rx_crc_errors +=
	  readl(cp->regs + REG_MAC_FCS_ERR) & 0xffff;
	stats[N_TX_RINGS].rx_frame_errors +=
		readl(cp->regs + REG_MAC_ALIGN_ERR) &0xffff;
	stats[N_TX_RINGS].rx_length_errors +=
		readl(cp->regs + REG_MAC_LEN_ERR) & 0xffff;
#if 1
	tmp = (readl(cp->regs + REG_MAC_COLL_EXCESS) & 0xffff) +
		(readl(cp->regs + REG_MAC_COLL_LATE) & 0xffff);
	stats[N_TX_RINGS].tx_aborted_errors += tmp;
	stats[N_TX_RINGS].collisions +=
	  tmp + (readl(cp->regs + REG_MAC_COLL_NORMAL) & 0xffff);
#else
	stats[N_TX_RINGS].tx_aborted_errors +=
		readl(cp->regs + REG_MAC_COLL_EXCESS);
	stats[N_TX_RINGS].collisions += readl(cp->regs + REG_MAC_COLL_EXCESS) +
		readl(cp->regs + REG_MAC_COLL_LATE);
#endif
	cas_clear_mac_err(cp);

	/* saved bits that are unique to ring 0 */
	spin_lock(&cp->stat_lock[0]);
	stats[N_TX_RINGS].collisions        += stats[0].collisions;
	stats[N_TX_RINGS].rx_over_errors    += stats[0].rx_over_errors;
	stats[N_TX_RINGS].rx_frame_errors   += stats[0].rx_frame_errors;
	stats[N_TX_RINGS].rx_fifo_errors    += stats[0].rx_fifo_errors;
	stats[N_TX_RINGS].tx_aborted_errors += stats[0].tx_aborted_errors;
	stats[N_TX_RINGS].tx_fifo_errors    += stats[0].tx_fifo_errors;
	spin_unlock(&cp->stat_lock[0]);

	for (i = 0; i < N_TX_RINGS; i++) {
		spin_lock(&cp->stat_lock[i]);
		stats[N_TX_RINGS].rx_length_errors +=
			stats[i].rx_length_errors;
		stats[N_TX_RINGS].rx_crc_errors += stats[i].rx_crc_errors;
		stats[N_TX_RINGS].rx_packets    += stats[i].rx_packets;
		stats[N_TX_RINGS].tx_packets    += stats[i].tx_packets;
		stats[N_TX_RINGS].rx_bytes      += stats[i].rx_bytes;
		stats[N_TX_RINGS].tx_bytes      += stats[i].tx_bytes;
		stats[N_TX_RINGS].rx_errors     += stats[i].rx_errors;
		stats[N_TX_RINGS].tx_errors     += stats[i].tx_errors;
		stats[N_TX_RINGS].rx_dropped    += stats[i].rx_dropped;
		stats[N_TX_RINGS].tx_dropped    += stats[i].tx_dropped;
		memset(stats + i, 0, sizeof(struct net_device_stats));
		spin_unlock(&cp->stat_lock[i]);
	}
	spin_unlock_irqrestore(&cp->stat_lock[N_TX_RINGS], flags);
	return stats + N_TX_RINGS;
}