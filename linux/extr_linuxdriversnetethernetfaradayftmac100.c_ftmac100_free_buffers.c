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
struct page {int dummy; } ;
struct ftmac100_txdes {int dummy; } ;
struct ftmac100_rxdes {int dummy; } ;
struct ftmac100_descs {int dummy; } ;
struct ftmac100 {int /*<<< orphan*/  descs_dma_addr; TYPE_1__* descs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct ftmac100_txdes* txdes; struct ftmac100_rxdes* rxdes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  RX_BUF_SIZE ; 
 int RX_QUEUE_ENTRIES ; 
 int TX_QUEUE_ENTRIES ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftmac100_rxdes_get_dma_addr (struct ftmac100_rxdes*) ; 
 struct page* ftmac100_rxdes_get_page (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_txdes_get_dma_addr (struct ftmac100_txdes*) ; 
 struct sk_buff* ftmac100_txdes_get_skb (struct ftmac100_txdes*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 

__attribute__((used)) static void ftmac100_free_buffers(struct ftmac100 *priv)
{
	int i;

	for (i = 0; i < RX_QUEUE_ENTRIES; i++) {
		struct ftmac100_rxdes *rxdes = &priv->descs->rxdes[i];
		struct page *page = ftmac100_rxdes_get_page(rxdes);
		dma_addr_t map = ftmac100_rxdes_get_dma_addr(rxdes);

		if (!page)
			continue;

		dma_unmap_page(priv->dev, map, RX_BUF_SIZE, DMA_FROM_DEVICE);
		__free_page(page);
	}

	for (i = 0; i < TX_QUEUE_ENTRIES; i++) {
		struct ftmac100_txdes *txdes = &priv->descs->txdes[i];
		struct sk_buff *skb = ftmac100_txdes_get_skb(txdes);
		dma_addr_t map = ftmac100_txdes_get_dma_addr(txdes);

		if (!skb)
			continue;

		dma_unmap_single(priv->dev, map, skb_headlen(skb), DMA_TO_DEVICE);
		dev_kfree_skb(skb);
	}

	dma_free_coherent(priv->dev, sizeof(struct ftmac100_descs),
			  priv->descs, priv->descs_dma_addr);
}