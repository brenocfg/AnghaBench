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
struct sk_buff {int data_len; scalar_t__ len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  truesize; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  multicast; } ;
struct net_device {TYPE_1__ stats; } ;
struct ftmac100_rxdes {int dummy; } ;
struct ftmac100 {int /*<<< orphan*/  dev; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 int /*<<< orphan*/  __pskb_pull_tail (struct sk_buff*,int) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  ftmac100_alloc_rx_page (struct ftmac100*,struct ftmac100_rxdes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftmac100_rx_drop_packet (struct ftmac100*) ; 
 struct ftmac100_rxdes* ftmac100_rx_locate_first_segment (struct ftmac100*) ; 
 int ftmac100_rx_packet_error (struct ftmac100*,struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_rx_pointer_advance (struct ftmac100*) ; 
 int ftmac100_rxdes_frame_length (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_rxdes_get_dma_addr (struct ftmac100_rxdes*) ; 
 struct page* ftmac100_rxdes_get_page (struct ftmac100_rxdes*) ; 
 int ftmac100_rxdes_last_segment (struct ftmac100_rxdes*) ; 
 int ftmac100_rxdes_multicast (struct ftmac100_rxdes*) ; 
 scalar_t__ net_ratelimit () ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_fill_page_desc (struct sk_buff*,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ftmac100_rx_packet(struct ftmac100 *priv, int *processed)
{
	struct net_device *netdev = priv->netdev;
	struct ftmac100_rxdes *rxdes;
	struct sk_buff *skb;
	struct page *page;
	dma_addr_t map;
	int length;
	bool ret;

	rxdes = ftmac100_rx_locate_first_segment(priv);
	if (!rxdes)
		return false;

	if (unlikely(ftmac100_rx_packet_error(priv, rxdes))) {
		ftmac100_rx_drop_packet(priv);
		return true;
	}

	/*
	 * It is impossible to get multi-segment packets
	 * because we always provide big enough receive buffers.
	 */
	ret = ftmac100_rxdes_last_segment(rxdes);
	BUG_ON(!ret);

	/* start processing */
	skb = netdev_alloc_skb_ip_align(netdev, 128);
	if (unlikely(!skb)) {
		if (net_ratelimit())
			netdev_err(netdev, "rx skb alloc failed\n");

		ftmac100_rx_drop_packet(priv);
		return true;
	}

	if (unlikely(ftmac100_rxdes_multicast(rxdes)))
		netdev->stats.multicast++;

	map = ftmac100_rxdes_get_dma_addr(rxdes);
	dma_unmap_page(priv->dev, map, RX_BUF_SIZE, DMA_FROM_DEVICE);

	length = ftmac100_rxdes_frame_length(rxdes);
	page = ftmac100_rxdes_get_page(rxdes);
	skb_fill_page_desc(skb, 0, page, 0, length);
	skb->len += length;
	skb->data_len += length;

	if (length > 128) {
		skb->truesize += PAGE_SIZE;
		/* We pull the minimum amount into linear part */
		__pskb_pull_tail(skb, ETH_HLEN);
	} else {
		/* Small frames are copied into linear part to free one page */
		__pskb_pull_tail(skb, length);
	}
	ftmac100_alloc_rx_page(priv, rxdes, GFP_ATOMIC);

	ftmac100_rx_pointer_advance(priv);

	skb->protocol = eth_type_trans(skb, netdev);

	netdev->stats.rx_packets++;
	netdev->stats.rx_bytes += skb->len;

	/* push packet to protocol stack */
	netif_receive_skb(skb);

	(*processed)++;
	return true;
}