#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_2__ stats; } ;
struct greth_private {scalar_t__ tx_free; int tx_next; int* tx_bufs_length; int /*<<< orphan*/  devlock; int /*<<< orphan*/  dev; struct greth_bd* tx_bd_base; TYPE_1__* regs; int /*<<< orphan*/  netdev; } ;
struct greth_bd {int /*<<< orphan*/  stat; int /*<<< orphan*/  addr; } ;
typedef  int netdev_tx_t ;
struct TYPE_3__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int GRETH_BD_EN ; 
 int GRETH_BD_IE ; 
 int GRETH_BD_LEN ; 
 int GRETH_BD_WR ; 
 int GRETH_REGLOAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRETH_REGSAVE (int /*<<< orphan*/ ,int) ; 
 int GRETH_RXI ; 
 size_t GRETH_TXBD_NUM_MASK ; 
 int GRETH_TXI ; 
 int MAX_FRAME_SIZE ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 size_t NEXT_TX (size_t) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  greth_clean_tx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  greth_enable_tx (struct greth_private*) ; 
 int /*<<< orphan*/  greth_print_tx_packet (struct sk_buff*) ; 
 int greth_read_bd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  greth_write_bd (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 struct greth_private* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_pktdata (struct greth_private*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 scalar_t__ phys_to_virt (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t
greth_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct greth_private *greth = netdev_priv(dev);
	struct greth_bd *bdp;
	int err = NETDEV_TX_OK;
	u32 status, dma_addr, ctrl;
	unsigned long flags;

	/* Clean TX Ring */
	greth_clean_tx(greth->netdev);

	if (unlikely(greth->tx_free <= 0)) {
		spin_lock_irqsave(&greth->devlock, flags);/*save from poll/irq*/
		ctrl = GRETH_REGLOAD(greth->regs->control);
		/* Enable TX IRQ only if not already in poll() routine */
		if (ctrl & GRETH_RXI)
			GRETH_REGSAVE(greth->regs->control, ctrl | GRETH_TXI);
		netif_stop_queue(dev);
		spin_unlock_irqrestore(&greth->devlock, flags);
		return NETDEV_TX_BUSY;
	}

	if (netif_msg_pktdata(greth))
		greth_print_tx_packet(skb);


	if (unlikely(skb->len > MAX_FRAME_SIZE)) {
		dev->stats.tx_errors++;
		goto out;
	}

	bdp = greth->tx_bd_base + greth->tx_next;
	dma_addr = greth_read_bd(&bdp->addr);

	memcpy((unsigned char *) phys_to_virt(dma_addr), skb->data, skb->len);

	dma_sync_single_for_device(greth->dev, dma_addr, skb->len, DMA_TO_DEVICE);

	status = GRETH_BD_EN | GRETH_BD_IE | (skb->len & GRETH_BD_LEN);
	greth->tx_bufs_length[greth->tx_next] = skb->len & GRETH_BD_LEN;

	/* Wrap around descriptor ring */
	if (greth->tx_next == GRETH_TXBD_NUM_MASK) {
		status |= GRETH_BD_WR;
	}

	greth->tx_next = NEXT_TX(greth->tx_next);
	greth->tx_free--;

	/* Write descriptor control word and enable transmission */
	greth_write_bd(&bdp->stat, status);
	spin_lock_irqsave(&greth->devlock, flags); /*save from poll/irq*/
	greth_enable_tx(greth);
	spin_unlock_irqrestore(&greth->devlock, flags);

out:
	dev_kfree_skb(skb);
	return err;
}