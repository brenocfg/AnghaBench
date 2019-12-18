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
struct mtk_tx_buf {int flags; struct sk_buff* skb; } ;
struct mtk_eth {int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ MTK_DMA_DUMMY_DESC ; 
 scalar_t__ MTK_HAS_CAPS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTK_QDMA ; 
 int MTK_TX_FLAGS_PAGE0 ; 
 int MTK_TX_FLAGS_SINGLE0 ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_addr0 ; 
 int /*<<< orphan*/  dma_addr1 ; 
 int /*<<< orphan*/  dma_len0 ; 
 int /*<<< orphan*/  dma_len1 ; 
 int /*<<< orphan*/  dma_unmap_addr (struct mtk_tx_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct mtk_tx_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_tx_unmap(struct mtk_eth *eth, struct mtk_tx_buf *tx_buf)
{
	if (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) {
		if (tx_buf->flags & MTK_TX_FLAGS_SINGLE0) {
			dma_unmap_single(eth->dev,
					 dma_unmap_addr(tx_buf, dma_addr0),
					 dma_unmap_len(tx_buf, dma_len0),
					 DMA_TO_DEVICE);
		} else if (tx_buf->flags & MTK_TX_FLAGS_PAGE0) {
			dma_unmap_page(eth->dev,
				       dma_unmap_addr(tx_buf, dma_addr0),
				       dma_unmap_len(tx_buf, dma_len0),
				       DMA_TO_DEVICE);
		}
	} else {
		if (dma_unmap_len(tx_buf, dma_len0)) {
			dma_unmap_page(eth->dev,
				       dma_unmap_addr(tx_buf, dma_addr0),
				       dma_unmap_len(tx_buf, dma_len0),
				       DMA_TO_DEVICE);
		}

		if (dma_unmap_len(tx_buf, dma_len1)) {
			dma_unmap_page(eth->dev,
				       dma_unmap_addr(tx_buf, dma_addr1),
				       dma_unmap_len(tx_buf, dma_len1),
				       DMA_TO_DEVICE);
		}
	}

	tx_buf->flags = 0;
	if (tx_buf->skb &&
	    (tx_buf->skb != (struct sk_buff *)MTK_DMA_DUMMY_DESC))
		dev_kfree_skb_any(tx_buf->skb);
	tx_buf->skb = NULL;
}