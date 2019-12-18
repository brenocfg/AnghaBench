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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct cas {int /*<<< orphan*/ * stat_lock; TYPE_1__* net_stats; int /*<<< orphan*/  dev; scalar_t__ regs; } ;
struct TYPE_2__ {int collisions; int tx_aborted_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_fifo_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int MAC_TX_COLL_EXCESS ; 
 int MAC_TX_COLL_LATE ; 
 int MAC_TX_COLL_NORMAL ; 
 int MAC_TX_DEFER_TIMER ; 
 int MAC_TX_MAX_PACKET_ERR ; 
 int MAC_TX_UNDERRUN ; 
 scalar_t__ REG_MAC_TX_STATUS ; 
 int /*<<< orphan*/  intr ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_printk (struct cas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cas_txmac_interrupt(struct net_device *dev,
			       struct cas *cp, u32 status)
{
	u32 txmac_stat = readl(cp->regs + REG_MAC_TX_STATUS);

	if (!txmac_stat)
		return 0;

	netif_printk(cp, intr, KERN_DEBUG, cp->dev,
		     "txmac interrupt, txmac_stat: 0x%x\n", txmac_stat);

	/* Defer timer expiration is quite normal,
	 * don't even log the event.
	 */
	if ((txmac_stat & MAC_TX_DEFER_TIMER) &&
	    !(txmac_stat & ~MAC_TX_DEFER_TIMER))
		return 0;

	spin_lock(&cp->stat_lock[0]);
	if (txmac_stat & MAC_TX_UNDERRUN) {
		netdev_err(dev, "TX MAC xmit underrun\n");
		cp->net_stats[0].tx_fifo_errors++;
	}

	if (txmac_stat & MAC_TX_MAX_PACKET_ERR) {
		netdev_err(dev, "TX MAC max packet size error\n");
		cp->net_stats[0].tx_errors++;
	}

	/* The rest are all cases of one of the 16-bit TX
	 * counters expiring.
	 */
	if (txmac_stat & MAC_TX_COLL_NORMAL)
		cp->net_stats[0].collisions += 0x10000;

	if (txmac_stat & MAC_TX_COLL_EXCESS) {
		cp->net_stats[0].tx_aborted_errors += 0x10000;
		cp->net_stats[0].collisions += 0x10000;
	}

	if (txmac_stat & MAC_TX_COLL_LATE) {
		cp->net_stats[0].tx_aborted_errors += 0x10000;
		cp->net_stats[0].collisions += 0x10000;
	}
	spin_unlock(&cp->stat_lock[0]);

	/* We do not keep track of MAC_TX_COLL_FIRST and
	 * MAC_TX_PEAK_ATTEMPTS events.
	 */
	return 0;
}