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
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct ltq_etop_priv {int /*<<< orphan*/  lock; TYPE_1__* pdev; struct ltq_etop_chan* ch; } ;
struct TYPE_4__ {size_t desc; struct ltq_dma_desc* desc_base; } ;
struct ltq_etop_chan {TYPE_2__ dma; struct sk_buff** skb; } ;
struct ltq_dma_desc {int ctl; unsigned int addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CPHYSADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ETH_ZLEN ; 
 size_t LTQ_DESC_NUM ; 
 int LTQ_DMA_C ; 
 int LTQ_DMA_EOP ; 
 int LTQ_DMA_OWN ; 
 int LTQ_DMA_SIZE_MASK ; 
 int LTQ_DMA_SOP ; 
 int LTQ_DMA_TX_OFFSET (unsigned int) ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 struct ltq_etop_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int
ltq_etop_tx(struct sk_buff *skb, struct net_device *dev)
{
	int queue = skb_get_queue_mapping(skb);
	struct netdev_queue *txq = netdev_get_tx_queue(dev, queue);
	struct ltq_etop_priv *priv = netdev_priv(dev);
	struct ltq_etop_chan *ch = &priv->ch[(queue << 1) | 1];
	struct ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];
	int len;
	unsigned long flags;
	u32 byte_offset;

	len = skb->len < ETH_ZLEN ? ETH_ZLEN : skb->len;

	if ((desc->ctl & (LTQ_DMA_OWN | LTQ_DMA_C)) || ch->skb[ch->dma.desc]) {
		dev_kfree_skb_any(skb);
		netdev_err(dev, "tx ring full\n");
		netif_tx_stop_queue(txq);
		return NETDEV_TX_BUSY;
	}

	/* dma needs to start on a 16 byte aligned address */
	byte_offset = CPHYSADDR(skb->data) % 16;
	ch->skb[ch->dma.desc] = skb;

	netif_trans_update(dev);

	spin_lock_irqsave(&priv->lock, flags);
	desc->addr = ((unsigned int) dma_map_single(&priv->pdev->dev, skb->data, len,
						DMA_TO_DEVICE)) - byte_offset;
	wmb();
	desc->ctl = LTQ_DMA_OWN | LTQ_DMA_SOP | LTQ_DMA_EOP |
		LTQ_DMA_TX_OFFSET(byte_offset) | (len & LTQ_DMA_SIZE_MASK);
	ch->dma.desc++;
	ch->dma.desc %= LTQ_DESC_NUM;
	spin_unlock_irqrestore(&priv->lock, flags);

	if (ch->dma.desc_base[ch->dma.desc].ctl & LTQ_DMA_OWN)
		netif_tx_stop_queue(txq);

	return NETDEV_TX_OK;
}