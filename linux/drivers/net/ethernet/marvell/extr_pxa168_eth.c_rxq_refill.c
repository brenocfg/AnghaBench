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
struct sk_buff {int data; } ;
struct rx_desc {int buf_size; int cmd_sts; int /*<<< orphan*/  buf_ptr; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct pxa168_eth_private {scalar_t__ rx_desc_count; scalar_t__ rx_ring_size; int rx_used_desc_q; TYPE_2__ timeout; scalar_t__ rx_resource_err; struct sk_buff** rx_skb; TYPE_1__* pdev; struct rx_desc* p_rx_desc_area; int /*<<< orphan*/  skb_size; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BUF_OWNED_BY_DMA ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ ETH_HW_IP_ALIGN ; 
 int HZ ; 
 int RX_EN_INT ; 
 scalar_t__ SKB_DMA_REALIGN ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 scalar_t__ jiffies ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int skb_end_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void rxq_refill(struct net_device *dev)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);
	struct sk_buff *skb;
	struct rx_desc *p_used_rx_desc;
	int used_rx_desc;

	while (pep->rx_desc_count < pep->rx_ring_size) {
		int size;

		skb = netdev_alloc_skb(dev, pep->skb_size);
		if (!skb)
			break;
		if (SKB_DMA_REALIGN)
			skb_reserve(skb, SKB_DMA_REALIGN);
		pep->rx_desc_count++;
		/* Get 'used' Rx descriptor */
		used_rx_desc = pep->rx_used_desc_q;
		p_used_rx_desc = &pep->p_rx_desc_area[used_rx_desc];
		size = skb_end_pointer(skb) - skb->data;
		p_used_rx_desc->buf_ptr = dma_map_single(&pep->pdev->dev,
							 skb->data,
							 size,
							 DMA_FROM_DEVICE);
		p_used_rx_desc->buf_size = size;
		pep->rx_skb[used_rx_desc] = skb;

		/* Return the descriptor to DMA ownership */
		dma_wmb();
		p_used_rx_desc->cmd_sts = BUF_OWNED_BY_DMA | RX_EN_INT;
		dma_wmb();

		/* Move the used descriptor pointer to the next descriptor */
		pep->rx_used_desc_q = (used_rx_desc + 1) % pep->rx_ring_size;

		/* Any Rx return cancels the Rx resource error status */
		pep->rx_resource_err = 0;

		skb_reserve(skb, ETH_HW_IP_ALIGN);
	}

	/*
	 * If RX ring is empty of SKB, set a timer to try allocating
	 * again at a later time.
	 */
	if (pep->rx_desc_count == 0) {
		pep->timeout.expires = jiffies + (HZ / 10);
		add_timer(&pep->timeout);
	}
}