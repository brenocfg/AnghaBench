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
typedef  unsigned int u32 ;
typedef  size_t u16 ;
struct sk_buff {unsigned int len; scalar_t__ ip_summed; int /*<<< orphan*/  data; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;
struct bcm_sysport_tx_ring {scalar_t__ desc_count; size_t curr_desc; size_t size; int /*<<< orphan*/  lock; int /*<<< orphan*/  index; struct bcm_sysport_cb* cbs; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dma_failed; } ;
struct bcm_sysport_priv {TYPE_2__ mib; scalar_t__ tsb_en; struct bcm_sysport_tx_ring* tx_rings; TYPE_1__* pdev; } ;
struct bcm_sysport_cb {struct sk_buff* skb; } ;
typedef  int netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 unsigned int DESC_ADDR_HI_MASK ; 
 unsigned int DESC_EOP ; 
 unsigned int DESC_L4_CSUM ; 
 unsigned int DESC_LEN_SHIFT ; 
 unsigned int DESC_SOP ; 
 unsigned int DESC_STATUS_SHIFT ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  TDMA_WRITE_PORT_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDMA_WRITE_PORT_LO (int /*<<< orphan*/ ) ; 
 unsigned int TX_STATUS_APP_CRC ; 
 struct sk_buff* bcm_sysport_insert_tsb (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_len ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct bcm_sysport_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct bcm_sysport_cb*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,size_t) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,size_t) ; 
 struct bcm_sysport_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct bcm_sysport_priv*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  netif_err (struct bcm_sysport_priv*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tdma_writel (struct bcm_sysport_priv*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_err ; 
 int /*<<< orphan*/  tx_queued ; 
 scalar_t__ unlikely (int) ; 
 unsigned int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t bcm_sysport_xmit(struct sk_buff *skb,
				    struct net_device *dev)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	struct device *kdev = &priv->pdev->dev;
	struct bcm_sysport_tx_ring *ring;
	struct bcm_sysport_cb *cb;
	struct netdev_queue *txq;
	u32 len_status, addr_lo;
	unsigned int skb_len;
	unsigned long flags;
	dma_addr_t mapping;
	u16 queue;
	int ret;

	queue = skb_get_queue_mapping(skb);
	txq = netdev_get_tx_queue(dev, queue);
	ring = &priv->tx_rings[queue];

	/* lock against tx reclaim in BH context and TX ring full interrupt */
	spin_lock_irqsave(&ring->lock, flags);
	if (unlikely(ring->desc_count == 0)) {
		netif_tx_stop_queue(txq);
		netdev_err(dev, "queue %d awake and ring full!\n", queue);
		ret = NETDEV_TX_BUSY;
		goto out;
	}

	/* Insert TSB and checksum infos */
	if (priv->tsb_en) {
		skb = bcm_sysport_insert_tsb(skb, dev);
		if (!skb) {
			ret = NETDEV_TX_OK;
			goto out;
		}
	}

	skb_len = skb->len;

	mapping = dma_map_single(kdev, skb->data, skb_len, DMA_TO_DEVICE);
	if (dma_mapping_error(kdev, mapping)) {
		priv->mib.tx_dma_failed++;
		netif_err(priv, tx_err, dev, "DMA map failed at %p (len=%d)\n",
			  skb->data, skb_len);
		ret = NETDEV_TX_OK;
		goto out;
	}

	/* Remember the SKB for future freeing */
	cb = &ring->cbs[ring->curr_desc];
	cb->skb = skb;
	dma_unmap_addr_set(cb, dma_addr, mapping);
	dma_unmap_len_set(cb, dma_len, skb_len);

	addr_lo = lower_32_bits(mapping);
	len_status = upper_32_bits(mapping) & DESC_ADDR_HI_MASK;
	len_status |= (skb_len << DESC_LEN_SHIFT);
	len_status |= (DESC_SOP | DESC_EOP | TX_STATUS_APP_CRC) <<
		       DESC_STATUS_SHIFT;
	if (skb->ip_summed == CHECKSUM_PARTIAL)
		len_status |= (DESC_L4_CSUM << DESC_STATUS_SHIFT);

	ring->curr_desc++;
	if (ring->curr_desc == ring->size)
		ring->curr_desc = 0;
	ring->desc_count--;

	/* Ports are latched, so write upper address first */
	tdma_writel(priv, len_status, TDMA_WRITE_PORT_HI(ring->index));
	tdma_writel(priv, addr_lo, TDMA_WRITE_PORT_LO(ring->index));

	/* Check ring space and update SW control flow */
	if (ring->desc_count == 0)
		netif_tx_stop_queue(txq);

	netif_dbg(priv, tx_queued, dev, "ring=%d desc_count=%d, curr_desc=%d\n",
		  ring->index, ring->desc_count, ring->curr_desc);

	ret = NETDEV_TX_OK;
out:
	spin_unlock_irqrestore(&ring->lock, flags);
	return ret;
}