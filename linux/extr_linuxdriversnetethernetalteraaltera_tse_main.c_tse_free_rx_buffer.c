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
struct tse_buffer {scalar_t__ dma_addr; struct sk_buff* skb; int /*<<< orphan*/  len; } ;
struct sk_buff {int dummy; } ;
struct altera_tse_private {int /*<<< orphan*/  device; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tse_free_rx_buffer(struct altera_tse_private *priv,
			       struct tse_buffer *rxbuffer)
{
	struct sk_buff *skb = rxbuffer->skb;
	dma_addr_t dma_addr = rxbuffer->dma_addr;

	if (skb != NULL) {
		if (dma_addr)
			dma_unmap_single(priv->device, dma_addr,
					 rxbuffer->len,
					 DMA_FROM_DEVICE);
		dev_kfree_skb_any(skb);
		rxbuffer->skb = NULL;
		rxbuffer->dma_addr = 0;
	}
}