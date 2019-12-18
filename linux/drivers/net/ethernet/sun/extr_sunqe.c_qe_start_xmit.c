#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sunqe_buffers {unsigned char** tx_buf; } ;
struct sunqe {int tx_new; int /*<<< orphan*/  lock; scalar_t__ qcregs; TYPE_2__* qe_block; int /*<<< orphan*/  buffers_dvma; struct sunqe_buffers* buffers; } ;
struct sk_buff {int len; } ;
struct TYPE_6__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_3__ stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_5__ {TYPE_1__* qe_txd; } ;
struct TYPE_4__ {int tx_flags; scalar_t__ tx_addr; } ;

/* Variables and functions */
 scalar_t__ CREG_CTRL ; 
 int /*<<< orphan*/  CREG_CTRL_TWAKEUP ; 
 scalar_t__ CREG_TIMASK ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int NEXT_TX (int) ; 
 int TXD_EOP ; 
 int TXD_LENGTH ; 
 int TXD_OWN ; 
 int TXD_SOP ; 
 int TXD_UPDATE ; 
 scalar_t__ TX_BUFFS_AVAIL (struct sunqe*) ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct sunqe* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  qe_tx_reclaim (struct sunqe*) ; 
 scalar_t__ qebuf_offset (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbus_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_buf ; 

__attribute__((used)) static netdev_tx_t qe_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct sunqe *qep = netdev_priv(dev);
	struct sunqe_buffers *qbufs = qep->buffers;
	__u32 txbuf_dvma, qbufs_dvma = (__u32)qep->buffers_dvma;
	unsigned char *txbuf;
	int len, entry;

	spin_lock_irq(&qep->lock);

	qe_tx_reclaim(qep);

	len = skb->len;
	entry = qep->tx_new;

	txbuf = &qbufs->tx_buf[entry & (TX_RING_SIZE - 1)][0];
	txbuf_dvma = qbufs_dvma +
		qebuf_offset(tx_buf, (entry & (TX_RING_SIZE - 1)));

	/* Avoid a race... */
	qep->qe_block->qe_txd[entry].tx_flags = TXD_UPDATE;

	skb_copy_from_linear_data(skb, txbuf, len);

	qep->qe_block->qe_txd[entry].tx_addr = txbuf_dvma;
	qep->qe_block->qe_txd[entry].tx_flags =
		(TXD_OWN | TXD_SOP | TXD_EOP | (len & TXD_LENGTH));
	qep->tx_new = NEXT_TX(entry);

	/* Get it going. */
	sbus_writel(CREG_CTRL_TWAKEUP, qep->qcregs + CREG_CTRL);

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;

	if (TX_BUFFS_AVAIL(qep) <= 0) {
		/* Halt the net queue and enable tx interrupts.
		 * When the tx queue empties the tx irq handler
		 * will wake up the queue and return us back to
		 * the lazy tx reclaim scheme.
		 */
		netif_stop_queue(dev);
		sbus_writel(0, qep->qcregs + CREG_TIMASK);
	}
	spin_unlock_irq(&qep->lock);

	dev_kfree_skb(skb);

	return NETDEV_TX_OK;
}