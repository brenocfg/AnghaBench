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
struct sk_buff {int dummy; } ;
struct enet_cb {struct sk_buff* skb; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_addr ; 
 int /*<<< orphan*/  dma_len ; 
 scalar_t__ dma_unmap_addr (struct enet_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct enet_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct enet_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *bcmgenet_free_rx_cb(struct device *dev,
					   struct enet_cb *cb)
{
	struct sk_buff *skb;

	skb = cb->skb;
	cb->skb = NULL;

	if (dma_unmap_addr(cb, dma_addr)) {
		dma_unmap_single(dev, dma_unmap_addr(cb, dma_addr),
				 dma_unmap_len(cb, dma_len), DMA_FROM_DEVICE);
		dma_unmap_addr_set(cb, dma_addr, 0);
	}

	return skb;
}