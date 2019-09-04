#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tx_desc {void* wb_addr; void* cfg; void* send_size; void* send_addr; } ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct net_device_stats {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {int /*<<< orphan*/  dev; struct net_device_stats stats; } ;
struct hip04_priv {unsigned int tx_head; int* tx_phys; int tx_desc_dma; unsigned int tx_coalesce_frames; int reg_inten; int /*<<< orphan*/  tx_coalesce_timer; int /*<<< orphan*/  napi; scalar_t__ base; struct sk_buff** tx_skb; int /*<<< orphan*/  tx_tail; struct tx_desc* tx_desc; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int DEF_INT_MASK ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 scalar_t__ PPE_INTEN ; 
 int RCV_INT ; 
 int /*<<< orphan*/  READ_ONCE (int /*<<< orphan*/ ) ; 
 int TX_CLEAR_WB ; 
 int TX_DESC_NUM ; 
 int TX_FINISH_CACHE_INV ; 
 unsigned int TX_NEXT (unsigned int) ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hip04_set_xmit_desc (struct hip04_priv*,int) ; 
 int /*<<< orphan*/  hip04_start_tx_timer (struct hip04_priv*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_is_queued (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 unsigned int tx_count (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int hip04_mac_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct hip04_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	unsigned int tx_head = priv->tx_head, count;
	struct tx_desc *desc = &priv->tx_desc[tx_head];
	dma_addr_t phys;

	smp_rmb();
	count = tx_count(tx_head, READ_ONCE(priv->tx_tail));
	if (count == (TX_DESC_NUM - 1)) {
		netif_stop_queue(ndev);
		return NETDEV_TX_BUSY;
	}

	phys = dma_map_single(&ndev->dev, skb->data, skb->len, DMA_TO_DEVICE);
	if (dma_mapping_error(&ndev->dev, phys)) {
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}

	priv->tx_skb[tx_head] = skb;
	priv->tx_phys[tx_head] = phys;
	desc->send_addr = cpu_to_be32(phys);
	desc->send_size = cpu_to_be32(skb->len);
	desc->cfg = cpu_to_be32(TX_CLEAR_WB | TX_FINISH_CACHE_INV);
	phys = priv->tx_desc_dma + tx_head * sizeof(struct tx_desc);
	desc->wb_addr = cpu_to_be32(phys);
	skb_tx_timestamp(skb);

	hip04_set_xmit_desc(priv, phys);
	priv->tx_head = TX_NEXT(tx_head);
	count++;
	netdev_sent_queue(ndev, skb->len);

	stats->tx_bytes += skb->len;
	stats->tx_packets++;

	/* Ensure tx_head update visible to tx reclaim */
	smp_wmb();

	/* queue is getting full, better start cleaning up now */
	if (count >= priv->tx_coalesce_frames) {
		if (napi_schedule_prep(&priv->napi)) {
			/* disable rx interrupt and timer */
			priv->reg_inten &= ~(RCV_INT);
			writel_relaxed(DEF_INT_MASK & ~RCV_INT,
				       priv->base + PPE_INTEN);
			hrtimer_cancel(&priv->tx_coalesce_timer);
			__napi_schedule(&priv->napi);
		}
	} else if (!hrtimer_is_queued(&priv->tx_coalesce_timer)) {
		/* cleanup not pending yet, start a new timer */
		hip04_start_tx_timer(priv);
	}

	return NETDEV_TX_OK;
}