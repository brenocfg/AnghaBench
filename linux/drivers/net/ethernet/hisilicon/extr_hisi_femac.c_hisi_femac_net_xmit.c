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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {scalar_t__ tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_fifo_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct hisi_femac_queue {size_t head; int num; struct sk_buff** skb; scalar_t__* dma_phys; int /*<<< orphan*/  tail; } ;
struct hisi_femac_priv {int /*<<< orphan*/  tx_fifo_used_cnt; scalar_t__ port_base; int /*<<< orphan*/  dev; struct hisi_femac_queue txq; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ ADDRQ_STAT ; 
 int /*<<< orphan*/  BIT_TX_READY ; 
 int /*<<< orphan*/  CIRC_SPACE (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ EQFRM_LEN ; 
 scalar_t__ EQ_ADDR ; 
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  IRQ_INT_TX_PER_PACKET ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hisi_femac_irq_enable (struct hisi_femac_priv*,int /*<<< orphan*/ ) ; 
 struct hisi_femac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t hisi_femac_net_xmit(struct sk_buff *skb,
				       struct net_device *dev)
{
	struct hisi_femac_priv *priv = netdev_priv(dev);
	struct hisi_femac_queue *txq = &priv->txq;
	dma_addr_t addr;
	u32 val;

	val = readl(priv->port_base + ADDRQ_STAT);
	val &= BIT_TX_READY;
	if (!val) {
		hisi_femac_irq_enable(priv, IRQ_INT_TX_PER_PACKET);
		dev->stats.tx_dropped++;
		dev->stats.tx_fifo_errors++;
		netif_stop_queue(dev);
		return NETDEV_TX_BUSY;
	}

	if (unlikely(!CIRC_SPACE(txq->head, txq->tail,
				 txq->num))) {
		hisi_femac_irq_enable(priv, IRQ_INT_TX_PER_PACKET);
		dev->stats.tx_dropped++;
		dev->stats.tx_fifo_errors++;
		netif_stop_queue(dev);
		return NETDEV_TX_BUSY;
	}

	addr = dma_map_single(priv->dev, skb->data,
			      skb->len, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(priv->dev, addr))) {
		dev_kfree_skb_any(skb);
		dev->stats.tx_dropped++;
		return NETDEV_TX_OK;
	}
	txq->dma_phys[txq->head] = addr;

	txq->skb[txq->head] = skb;
	txq->head = (txq->head + 1) % txq->num;

	writel(addr, priv->port_base + EQ_ADDR);
	writel(skb->len + ETH_FCS_LEN, priv->port_base + EQFRM_LEN);

	priv->tx_fifo_used_cnt++;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	netdev_sent_queue(dev, skb->len);

	return NETDEV_TX_OK;
}