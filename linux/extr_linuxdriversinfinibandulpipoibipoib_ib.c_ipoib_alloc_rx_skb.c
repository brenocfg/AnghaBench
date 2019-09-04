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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct ipoib_pseudo_header {int dummy; } ;
struct ipoib_dev_priv {TYPE_1__* rx_ring; int /*<<< orphan*/  ca; int /*<<< orphan*/  max_ib_mtu; } ;
struct TYPE_2__ {struct sk_buff* skb; int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ IPOIB_HARD_LEN ; 
 int IPOIB_UD_BUF_SIZE (int /*<<< orphan*/ ) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *ipoib_alloc_rx_skb(struct net_device *dev, int id)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct sk_buff *skb;
	int buf_size;
	u64 *mapping;

	buf_size = IPOIB_UD_BUF_SIZE(priv->max_ib_mtu);

	skb = dev_alloc_skb(buf_size + IPOIB_HARD_LEN);
	if (unlikely(!skb))
		return NULL;

	/*
	 * the IP header will be at IPOIP_HARD_LEN + IB_GRH_BYTES, that is
	 * 64 bytes aligned
	 */
	skb_reserve(skb, sizeof(struct ipoib_pseudo_header));

	mapping = priv->rx_ring[id].mapping;
	mapping[0] = ib_dma_map_single(priv->ca, skb->data, buf_size,
				       DMA_FROM_DEVICE);
	if (unlikely(ib_dma_mapping_error(priv->ca, mapping[0])))
		goto error;

	priv->rx_ring[id].skb = skb;
	return skb;
error:
	dev_kfree_skb_any(skb);
	return NULL;
}