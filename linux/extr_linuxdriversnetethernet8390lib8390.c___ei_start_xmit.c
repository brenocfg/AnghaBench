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
struct sk_buff {int len; char* data; } ;
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_errors; } ;
struct net_device {unsigned long base_addr; TYPE_1__ stats; int /*<<< orphan*/  irq; } ;
struct ei_device {int irqlock; int tx1; int tx_start_page; int tx2; int lasttx; int txing; int /*<<< orphan*/  page_lock; int /*<<< orphan*/  txqueue; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ EN0_IMR ; 
 int ENISR_ALL ; 
 int ETH_ZLEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  NS8390_trigger_send (struct net_device*,int,int) ; 
 int TX_PAGES ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  disable_irq_nosync_lockdep_irqsave (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  ei_block_output (struct net_device*,int,char*,int) ; 
 int /*<<< orphan*/  ei_outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  enable_irq_lockdep_irqrestore (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int,int,int) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct ei_device*,int /*<<< orphan*/ ,struct net_device*,char*,int,int,int) ; 
 scalar_t__ netif_msg_tx_queued (struct ei_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_err ; 

__attribute__((used)) static netdev_tx_t __ei_start_xmit(struct sk_buff *skb,
				   struct net_device *dev)
{
	unsigned long e8390_base = dev->base_addr;
	struct ei_device *ei_local = netdev_priv(dev);
	int send_length = skb->len, output_page;
	unsigned long flags;
	char buf[ETH_ZLEN];
	char *data = skb->data;

	if (skb->len < ETH_ZLEN) {
		memset(buf, 0, ETH_ZLEN);	/* more efficient than doing just the needed bits */
		memcpy(buf, data, skb->len);
		send_length = ETH_ZLEN;
		data = buf;
	}

	/* Mask interrupts from the ethercard.
	   SMP: We have to grab the lock here otherwise the IRQ handler
	   on another CPU can flip window and race the IRQ mask set. We end
	   up trashing the mcast filter not disabling irqs if we don't lock */

	spin_lock_irqsave(&ei_local->page_lock, flags);
	ei_outb_p(0x00, e8390_base + EN0_IMR);
	spin_unlock_irqrestore(&ei_local->page_lock, flags);


	/*
	 *	Slow phase with lock held.
	 */

	disable_irq_nosync_lockdep_irqsave(dev->irq, &flags);

	spin_lock(&ei_local->page_lock);

	ei_local->irqlock = 1;

	/*
	 * We have two Tx slots available for use. Find the first free
	 * slot, and then perform some sanity checks. With two Tx bufs,
	 * you get very close to transmitting back-to-back packets. With
	 * only one Tx buf, the transmitter sits idle while you reload the
	 * card, leaving a substantial gap between each transmitted packet.
	 */

	if (ei_local->tx1 == 0) {
		output_page = ei_local->tx_start_page;
		ei_local->tx1 = send_length;
		if ((netif_msg_tx_queued(ei_local)) &&
		    ei_local->tx2 > 0)
			netdev_dbg(dev,
				   "idle transmitter tx2=%d, lasttx=%d, txing=%d\n",
				   ei_local->tx2, ei_local->lasttx, ei_local->txing);
	} else if (ei_local->tx2 == 0) {
		output_page = ei_local->tx_start_page + TX_PAGES/2;
		ei_local->tx2 = send_length;
		if ((netif_msg_tx_queued(ei_local)) &&
		    ei_local->tx1 > 0)
			netdev_dbg(dev,
				   "idle transmitter, tx1=%d, lasttx=%d, txing=%d\n",
				   ei_local->tx1, ei_local->lasttx, ei_local->txing);
	} else {			/* We should never get here. */
		netif_dbg(ei_local, tx_err, dev,
			  "No Tx buffers free! tx1=%d tx2=%d last=%d\n",
			  ei_local->tx1, ei_local->tx2, ei_local->lasttx);
		ei_local->irqlock = 0;
		netif_stop_queue(dev);
		ei_outb_p(ENISR_ALL, e8390_base + EN0_IMR);
		spin_unlock(&ei_local->page_lock);
		enable_irq_lockdep_irqrestore(dev->irq, &flags);
		dev->stats.tx_errors++;
		return NETDEV_TX_BUSY;
	}

	/*
	 * Okay, now upload the packet and trigger a send if the transmitter
	 * isn't already sending. If it is busy, the interrupt handler will
	 * trigger the send later, upon receiving a Tx done interrupt.
	 */

	ei_block_output(dev, send_length, data, output_page);

	if (!ei_local->txing) {
		ei_local->txing = 1;
		NS8390_trigger_send(dev, send_length, output_page);
		if (output_page == ei_local->tx_start_page) {
			ei_local->tx1 = -1;
			ei_local->lasttx = -1;
		} else {
			ei_local->tx2 = -1;
			ei_local->lasttx = -2;
		}
	} else
		ei_local->txqueue++;

	if (ei_local->tx1 && ei_local->tx2)
		netif_stop_queue(dev);
	else
		netif_start_queue(dev);

	/* Turn 8390 interrupts back on. */
	ei_local->irqlock = 0;
	ei_outb_p(ENISR_ALL, e8390_base + EN0_IMR);

	spin_unlock(&ei_local->page_lock);
	enable_irq_lockdep_irqrestore(dev->irq, &flags);
	skb_tx_timestamp(skb);
	dev_consume_skb_any(skb);
	dev->stats.tx_bytes += send_length;

	return NETDEV_TX_OK;
}