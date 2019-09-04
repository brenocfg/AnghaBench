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
struct xgmac_priv {unsigned int rx_tail; int /*<<< orphan*/  napi; int /*<<< orphan*/  dev; scalar_t__ dma_buf_sz; int /*<<< orphan*/  device; struct sk_buff** rx_skbuff; struct xgmac_dma_desc* dma_rx; int /*<<< orphan*/  rx_head; } ;
struct xgmac_dma_desc {int dummy; } ;
struct sk_buff {int ip_summed; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int CHECKSUM_NONE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_RX_RING_SZ ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  desc_get_buf_addr (struct xgmac_dma_desc*) ; 
 scalar_t__ desc_get_owner (struct xgmac_dma_desc*) ; 
 int desc_get_rx_frame_len (struct xgmac_dma_desc*) ; 
 int desc_get_rx_status (struct xgmac_priv*,struct xgmac_dma_desc*) ; 
 int /*<<< orphan*/  dma_ring_cnt (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int dma_ring_incr (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xgmac_rx_refill (struct xgmac_priv*) ; 

__attribute__((used)) static int xgmac_rx(struct xgmac_priv *priv, int limit)
{
	unsigned int entry;
	unsigned int count = 0;
	struct xgmac_dma_desc *p;

	while (count < limit) {
		int ip_checksum;
		struct sk_buff *skb;
		int frame_len;

		if (!dma_ring_cnt(priv->rx_head, priv->rx_tail, DMA_RX_RING_SZ))
			break;

		entry = priv->rx_tail;
		p = priv->dma_rx + entry;
		if (desc_get_owner(p))
			break;

		count++;
		priv->rx_tail = dma_ring_incr(priv->rx_tail, DMA_RX_RING_SZ);

		/* read the status of the incoming frame */
		ip_checksum = desc_get_rx_status(priv, p);
		if (ip_checksum < 0)
			continue;

		skb = priv->rx_skbuff[entry];
		if (unlikely(!skb)) {
			netdev_err(priv->dev, "Inconsistent Rx descriptor chain\n");
			break;
		}
		priv->rx_skbuff[entry] = NULL;

		frame_len = desc_get_rx_frame_len(p);
		netdev_dbg(priv->dev, "RX frame size %d, COE status: %d\n",
			frame_len, ip_checksum);

		skb_put(skb, frame_len);
		dma_unmap_single(priv->device, desc_get_buf_addr(p),
				 priv->dma_buf_sz - NET_IP_ALIGN, DMA_FROM_DEVICE);

		skb->protocol = eth_type_trans(skb, priv->dev);
		skb->ip_summed = ip_checksum;
		if (ip_checksum == CHECKSUM_NONE)
			netif_receive_skb(skb);
		else
			napi_gro_receive(&priv->napi, skb);
	}

	xgmac_rx_refill(priv);

	return count;
}