#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xgmac_priv {int rx_head; int /*<<< orphan*/  rx_tail; TYPE_1__* dev; scalar_t__ dma_buf_sz; struct sk_buff** rx_skbuff; int /*<<< orphan*/  device; struct xgmac_dma_desc* dma_rx; } ;
struct xgmac_dma_desc {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_RX_RING_SZ ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  desc_set_buf_addr (struct xgmac_dma_desc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  desc_set_rx_owner (struct xgmac_dma_desc*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_ring_incr (int,int /*<<< orphan*/ ) ; 
 int dma_ring_space (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (TYPE_1__*,int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgmac_rx_refill(struct xgmac_priv *priv)
{
	struct xgmac_dma_desc *p;
	dma_addr_t paddr;
	int bufsz = priv->dev->mtu + ETH_HLEN + ETH_FCS_LEN;

	while (dma_ring_space(priv->rx_head, priv->rx_tail, DMA_RX_RING_SZ) > 1) {
		int entry = priv->rx_head;
		struct sk_buff *skb;

		p = priv->dma_rx + entry;

		if (priv->rx_skbuff[entry] == NULL) {
			skb = netdev_alloc_skb_ip_align(priv->dev, bufsz);
			if (unlikely(skb == NULL))
				break;

			paddr = dma_map_single(priv->device, skb->data,
					       priv->dma_buf_sz - NET_IP_ALIGN,
					       DMA_FROM_DEVICE);
			if (dma_mapping_error(priv->device, paddr)) {
				dev_kfree_skb_any(skb);
				break;
			}
			priv->rx_skbuff[entry] = skb;
			desc_set_buf_addr(p, paddr, priv->dma_buf_sz);
		}

		netdev_dbg(priv->dev, "rx ring: head %d, tail %d\n",
			priv->rx_head, priv->rx_tail);

		priv->rx_head = dma_ring_incr(priv->rx_head, DMA_RX_RING_SZ);
		desc_set_rx_owner(p);
	}
}