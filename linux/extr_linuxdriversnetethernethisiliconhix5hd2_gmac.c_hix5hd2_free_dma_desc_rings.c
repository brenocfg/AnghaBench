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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_4__ {struct hix5hd2_desc* desc; } ;
struct TYPE_3__ {struct hix5hd2_desc* desc; } ;
struct hix5hd2_priv {struct sk_buff** tx_skb; int /*<<< orphan*/  dev; TYPE_2__ tx_rq; struct sk_buff** rx_skb; TYPE_1__ rx_fq; } ;
struct hix5hd2_desc {int /*<<< orphan*/  buff_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  MAC_MAX_FRAME_SIZE ; 
 int RX_DESC_NUM ; 
 int TX_DESC_NUM ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hix5hd2_free_dma_desc_rings(struct hix5hd2_priv *priv)
{
	struct hix5hd2_desc *desc;
	dma_addr_t addr;
	int i;

	for (i = 0; i < RX_DESC_NUM; i++) {
		struct sk_buff *skb = priv->rx_skb[i];
		if (skb == NULL)
			continue;

		desc = priv->rx_fq.desc + i;
		addr = le32_to_cpu(desc->buff_addr);
		dma_unmap_single(priv->dev, addr,
				 MAC_MAX_FRAME_SIZE, DMA_FROM_DEVICE);
		dev_kfree_skb_any(skb);
		priv->rx_skb[i] = NULL;
	}

	for (i = 0; i < TX_DESC_NUM; i++) {
		struct sk_buff *skb = priv->tx_skb[i];
		if (skb == NULL)
			continue;

		desc = priv->tx_rq.desc + i;
		addr = le32_to_cpu(desc->buff_addr);
		dma_unmap_single(priv->dev, addr, skb->len, DMA_TO_DEVICE);
		dev_kfree_skb_any(skb);
		priv->tx_skb[i] = NULL;
	}
}