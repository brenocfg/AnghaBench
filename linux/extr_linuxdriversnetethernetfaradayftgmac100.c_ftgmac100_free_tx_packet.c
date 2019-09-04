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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct ftgmac100_txdes {int /*<<< orphan*/  txdes3; } ;
struct ftgmac100 {int /*<<< orphan*/ ** tx_skbs; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int FTGMAC100_TXDES0_FTS ; 
 int FTGMAC100_TXDES0_LTS ; 
 size_t FTGMAC100_TXDES0_TXBUF_SIZE (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 size_t skb_headlen (struct sk_buff*) ; 

__attribute__((used)) static void ftgmac100_free_tx_packet(struct ftgmac100 *priv,
				     unsigned int pointer,
				     struct sk_buff *skb,
				     struct ftgmac100_txdes *txdes,
				     u32 ctl_stat)
{
	dma_addr_t map = le32_to_cpu(txdes->txdes3);
	size_t len;

	if (ctl_stat & FTGMAC100_TXDES0_FTS) {
		len = skb_headlen(skb);
		dma_unmap_single(priv->dev, map, len, DMA_TO_DEVICE);
	} else {
		len = FTGMAC100_TXDES0_TXBUF_SIZE(ctl_stat);
		dma_unmap_page(priv->dev, map, len, DMA_TO_DEVICE);
	}

	/* Free SKB on last segment */
	if (ctl_stat & FTGMAC100_TXDES0_LTS)
		dev_kfree_skb(skb);
	priv->tx_skbs[pointer] = NULL;
}