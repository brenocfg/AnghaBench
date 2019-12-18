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
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {unsigned long tx_packets; unsigned long tx_bytes; } ;
struct net_device {TYPE_1__ stats; } ;
struct ioc3_private {int tx_ci; scalar_t__ txqlen; int /*<<< orphan*/  ioc3_lock; struct sk_buff** tx_skbs; struct ioc3_ethregs* regs; } ;
struct ioc3_ethregs {int /*<<< orphan*/  etcir; } ;

/* Variables and functions */
 scalar_t__ TX_RING_ENTRIES ; 
 int TX_RING_MASK ; 
 int /*<<< orphan*/  dev_consume_skb_irq (struct sk_buff*) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ioc3_tx(struct net_device *dev)
{
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3_ethregs *regs = ip->regs;
	unsigned long packets, bytes;
	int tx_entry, o_entry;
	struct sk_buff *skb;
	u32 etcir;

	spin_lock(&ip->ioc3_lock);
	etcir = readl(&regs->etcir);

	tx_entry = (etcir >> 7) & TX_RING_MASK;
	o_entry = ip->tx_ci;
	packets = 0;
	bytes = 0;

	while (o_entry != tx_entry) {
		packets++;
		skb = ip->tx_skbs[o_entry];
		bytes += skb->len;
		dev_consume_skb_irq(skb);
		ip->tx_skbs[o_entry] = NULL;

		o_entry = (o_entry + 1) & TX_RING_MASK;	/* Next */

		etcir = readl(&regs->etcir);		/* More pkts sent?  */
		tx_entry = (etcir >> 7) & TX_RING_MASK;
	}

	dev->stats.tx_packets += packets;
	dev->stats.tx_bytes += bytes;
	ip->txqlen -= packets;

	if (netif_queue_stopped(dev) && ip->txqlen < TX_RING_ENTRIES)
		netif_wake_queue(dev);

	ip->tx_ci = o_entry;
	spin_unlock(&ip->ioc3_lock);
}