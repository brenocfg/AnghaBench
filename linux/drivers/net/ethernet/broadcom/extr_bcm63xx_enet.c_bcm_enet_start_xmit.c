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
struct TYPE_4__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct bcm_enet_priv {size_t tx_curr_desc; int dma_desc_shift; size_t tx_ring_size; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  tx_desc_count; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  dma_chan_en_mask; TYPE_1__* pdev; struct sk_buff** tx_skb; struct bcm_enet_desc* tx_desc_cpu; scalar_t__ enet_is_sw; } ;
struct bcm_enet_desc {int len_stat; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMADESC_APPEND_CRC ; 
 int DMADESC_ESOP_MASK ; 
 int DMADESC_LENGTH_MASK ; 
 int DMADESC_LENGTH_SHIFT ; 
 int DMADESC_OWNER_MASK ; 
 int DMADESC_WRAP_MASK ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ENETDMAC_CHANCFG ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enet_dmac_writel (struct bcm_enet_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 struct sk_buff* skb_copy_expand (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* skb_put_zero (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t
bcm_enet_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct bcm_enet_priv *priv;
	struct bcm_enet_desc *desc;
	u32 len_stat;
	netdev_tx_t ret;

	priv = netdev_priv(dev);

	/* lock against tx reclaim */
	spin_lock(&priv->tx_lock);

	/* make sure  the tx hw queue  is not full,  should not happen
	 * since we stop queue before it's the case */
	if (unlikely(!priv->tx_desc_count)) {
		netif_stop_queue(dev);
		dev_err(&priv->pdev->dev, "xmit called with no tx desc "
			"available?\n");
		ret = NETDEV_TX_BUSY;
		goto out_unlock;
	}

	/* pad small packets sent on a switch device */
	if (priv->enet_is_sw && skb->len < 64) {
		int needed = 64 - skb->len;
		char *data;

		if (unlikely(skb_tailroom(skb) < needed)) {
			struct sk_buff *nskb;

			nskb = skb_copy_expand(skb, 0, needed, GFP_ATOMIC);
			if (!nskb) {
				ret = NETDEV_TX_BUSY;
				goto out_unlock;
			}
			dev_kfree_skb(skb);
			skb = nskb;
		}
		data = skb_put_zero(skb, needed);
	}

	/* point to the next available desc */
	desc = &priv->tx_desc_cpu[priv->tx_curr_desc];
	priv->tx_skb[priv->tx_curr_desc] = skb;

	/* fill descriptor */
	desc->address = dma_map_single(&priv->pdev->dev, skb->data, skb->len,
				       DMA_TO_DEVICE);

	len_stat = (skb->len << DMADESC_LENGTH_SHIFT) & DMADESC_LENGTH_MASK;
	len_stat |= (DMADESC_ESOP_MASK >> priv->dma_desc_shift) |
		DMADESC_APPEND_CRC |
		DMADESC_OWNER_MASK;

	priv->tx_curr_desc++;
	if (priv->tx_curr_desc == priv->tx_ring_size) {
		priv->tx_curr_desc = 0;
		len_stat |= (DMADESC_WRAP_MASK >> priv->dma_desc_shift);
	}
	priv->tx_desc_count--;

	/* dma might be already polling, make sure we update desc
	 * fields in correct order */
	wmb();
	desc->len_stat = len_stat;
	wmb();

	/* kick tx dma */
	enet_dmac_writel(priv, priv->dma_chan_en_mask,
				 ENETDMAC_CHANCFG, priv->tx_chan);

	/* stop queue if no more desc available */
	if (!priv->tx_desc_count)
		netif_stop_queue(dev);

	dev->stats.tx_bytes += skb->len;
	dev->stats.tx_packets++;
	ret = NETDEV_TX_OK;

out_unlock:
	spin_unlock(&priv->tx_lock);
	return ret;
}