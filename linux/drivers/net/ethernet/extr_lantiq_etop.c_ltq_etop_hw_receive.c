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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct ltq_etop_priv {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {size_t desc; struct ltq_dma_desc* desc_base; } ;
struct ltq_etop_chan {int /*<<< orphan*/  netdev; TYPE_1__ dma; struct sk_buff** skb; } ;
struct ltq_dma_desc {int ctl; } ;

/* Variables and functions */
 size_t LTQ_DESC_NUM ; 
 int LTQ_DMA_SIZE_MASK ; 
 int MAX_DMA_CRC_LEN ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_dma_close (TYPE_1__*) ; 
 scalar_t__ ltq_etop_alloc_skb (struct ltq_etop_chan*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct ltq_etop_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
ltq_etop_hw_receive(struct ltq_etop_chan *ch)
{
	struct ltq_etop_priv *priv = netdev_priv(ch->netdev);
	struct ltq_dma_desc *desc = &ch->dma.desc_base[ch->dma.desc];
	struct sk_buff *skb = ch->skb[ch->dma.desc];
	int len = (desc->ctl & LTQ_DMA_SIZE_MASK) - MAX_DMA_CRC_LEN;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	if (ltq_etop_alloc_skb(ch)) {
		netdev_err(ch->netdev,
			"failed to allocate new rx buffer, stopping DMA\n");
		ltq_dma_close(&ch->dma);
	}
	ch->dma.desc++;
	ch->dma.desc %= LTQ_DESC_NUM;
	spin_unlock_irqrestore(&priv->lock, flags);

	skb_put(skb, len);
	skb->protocol = eth_type_trans(skb, ch->netdev);
	netif_receive_skb(skb);
}