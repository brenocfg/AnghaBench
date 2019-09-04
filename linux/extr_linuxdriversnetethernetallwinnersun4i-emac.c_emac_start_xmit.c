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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int tx_bytes; } ;
struct net_device {TYPE_1__ stats; } ;
struct emac_board_info {int tx_fifo_stat; int /*<<< orphan*/  lock; scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ EMAC_TX_CTL0_REG ; 
 scalar_t__ EMAC_TX_CTL1_REG ; 
 scalar_t__ EMAC_TX_INS_REG ; 
 scalar_t__ EMAC_TX_IO_DATA_REG ; 
 scalar_t__ EMAC_TX_PL0_REG ; 
 scalar_t__ EMAC_TX_PL1_REG ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  emac_outblk_32bit (scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct emac_board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int emac_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct emac_board_info *db = netdev_priv(dev);
	unsigned long channel;
	unsigned long flags;

	channel = db->tx_fifo_stat & 3;
	if (channel == 3)
		return 1;

	channel = (channel == 1 ? 1 : 0);

	spin_lock_irqsave(&db->lock, flags);

	writel(channel, db->membase + EMAC_TX_INS_REG);

	emac_outblk_32bit(db->membase + EMAC_TX_IO_DATA_REG,
			skb->data, skb->len);
	dev->stats.tx_bytes += skb->len;

	db->tx_fifo_stat |= 1 << channel;
	/* TX control: First packet immediately send, second packet queue */
	if (channel == 0) {
		/* set TX len */
		writel(skb->len, db->membase + EMAC_TX_PL0_REG);
		/* start translate from fifo to phy */
		writel(readl(db->membase + EMAC_TX_CTL0_REG) | 1,
		       db->membase + EMAC_TX_CTL0_REG);

		/* save the time stamp */
		netif_trans_update(dev);
	} else if (channel == 1) {
		/* set TX len */
		writel(skb->len, db->membase + EMAC_TX_PL1_REG);
		/* start translate from fifo to phy */
		writel(readl(db->membase + EMAC_TX_CTL1_REG) | 1,
		       db->membase + EMAC_TX_CTL1_REG);

		/* save the time stamp */
		netif_trans_update(dev);
	}

	if ((db->tx_fifo_stat & 3) == 3) {
		/* Second packet */
		netif_stop_queue(dev);
	}

	spin_unlock_irqrestore(&db->lock, flags);

	/* free this SKB */
	dev_consume_skb_any(skb);

	return NETDEV_TX_OK;
}