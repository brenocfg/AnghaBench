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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct ftgmac100_rxdes {void* rxdes0; void* rxdes3; } ;
struct ftgmac100 {int rx_q_entries; int /*<<< orphan*/  rxdes0_edorr_mask; struct sk_buff** rx_skbs; int /*<<< orphan*/  rx_scratch_dma; int /*<<< orphan*/  dev; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 scalar_t__ net_ratelimit () ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ftgmac100_alloc_rx_buf(struct ftgmac100 *priv, unsigned int entry,
				  struct ftgmac100_rxdes *rxdes, gfp_t gfp)
{
	struct net_device *netdev = priv->netdev;
	struct sk_buff *skb;
	dma_addr_t map;
	int err = 0;

	skb = netdev_alloc_skb_ip_align(netdev, RX_BUF_SIZE);
	if (unlikely(!skb)) {
		if (net_ratelimit())
			netdev_warn(netdev, "failed to allocate rx skb\n");
		err = -ENOMEM;
		map = priv->rx_scratch_dma;
	} else {
		map = dma_map_single(priv->dev, skb->data, RX_BUF_SIZE,
				     DMA_FROM_DEVICE);
		if (unlikely(dma_mapping_error(priv->dev, map))) {
			if (net_ratelimit())
				netdev_err(netdev, "failed to map rx page\n");
			dev_kfree_skb_any(skb);
			map = priv->rx_scratch_dma;
			skb = NULL;
			err = -ENOMEM;
		}
	}

	/* Store skb */
	priv->rx_skbs[entry] = skb;

	/* Store DMA address into RX desc */
	rxdes->rxdes3 = cpu_to_le32(map);

	/* Ensure the above is ordered vs clearing the OWN bit */
	dma_wmb();

	/* Clean status (which resets own bit) */
	if (entry == (priv->rx_q_entries - 1))
		rxdes->rxdes0 = cpu_to_le32(priv->rxdes0_edorr_mask);
	else
		rxdes->rxdes0 = 0;

	return err;
}