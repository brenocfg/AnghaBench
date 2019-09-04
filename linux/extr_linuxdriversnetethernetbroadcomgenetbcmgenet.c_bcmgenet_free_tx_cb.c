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
struct sk_buff {int dummy; } ;
struct enet_cb {struct sk_buff* skb; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct enet_cb* last_cb; struct enet_cb* first_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 TYPE_1__* GENET_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_len ; 
 scalar_t__ dma_unmap_addr (struct enet_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct enet_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct enet_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *bcmgenet_free_tx_cb(struct device *dev,
					   struct enet_cb *cb)
{
	struct sk_buff *skb;

	skb = cb->skb;

	if (skb) {
		cb->skb = NULL;
		if (cb == GENET_CB(skb)->first_cb)
			dma_unmap_single(dev, dma_unmap_addr(cb, dma_addr),
					 dma_unmap_len(cb, dma_len),
					 DMA_TO_DEVICE);
		else
			dma_unmap_page(dev, dma_unmap_addr(cb, dma_addr),
				       dma_unmap_len(cb, dma_len),
				       DMA_TO_DEVICE);
		dma_unmap_addr_set(cb, dma_addr, 0);

		if (cb == GENET_CB(skb)->last_cb)
			return skb;

	} else if (dma_unmap_addr(cb, dma_addr)) {
		dma_unmap_page(dev,
			       dma_unmap_addr(cb, dma_addr),
			       dma_unmap_len(cb, dma_len),
			       DMA_TO_DEVICE);
		dma_unmap_addr_set(cb, dma_addr, 0);
	}

	return NULL;
}