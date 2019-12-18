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
struct stmmac_tx_queue {unsigned int cur_tx; TYPE_2__* tx_skbuff_dma; struct dma_desc* dma_tx; scalar_t__ dma_etx; int /*<<< orphan*/ ** tx_skbuff; struct stmmac_priv* priv_data; } ;
struct stmmac_priv {int /*<<< orphan*/  device; scalar_t__ extend_desc; TYPE_1__* plat; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct dma_desc {void* des3; void* des2; } ;
struct TYPE_4__ {unsigned int buf; unsigned int len; int is_jumbo; } ;
struct TYPE_3__ {scalar_t__ enh_desc; } ;

/* Variables and functions */
 unsigned int BUF_SIZE_2KiB ; 
 unsigned int BUF_SIZE_4KiB ; 
 unsigned int BUF_SIZE_8KiB ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DMA_TX_SIZE ; 
 unsigned int STMMAC_GET_ENTRY (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STMMAC_RING_MODE ; 
 void* cpu_to_le32 (unsigned int) ; 
 unsigned int dma_map_single (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 int /*<<< orphan*/  stmmac_prepare_tx_desc (struct stmmac_priv*,struct dma_desc*,int,unsigned int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jumbo_frm(void *p, struct sk_buff *skb, int csum)
{
	struct stmmac_tx_queue *tx_q = (struct stmmac_tx_queue *)p;
	unsigned int nopaged_len = skb_headlen(skb);
	struct stmmac_priv *priv = tx_q->priv_data;
	unsigned int entry = tx_q->cur_tx;
	unsigned int bmax, len, des2;
	struct dma_desc *desc;

	if (priv->extend_desc)
		desc = (struct dma_desc *)(tx_q->dma_etx + entry);
	else
		desc = tx_q->dma_tx + entry;

	if (priv->plat->enh_desc)
		bmax = BUF_SIZE_8KiB;
	else
		bmax = BUF_SIZE_2KiB;

	len = nopaged_len - bmax;

	if (nopaged_len > BUF_SIZE_8KiB) {

		des2 = dma_map_single(priv->device, skb->data, bmax,
				      DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		if (dma_mapping_error(priv->device, des2))
			return -1;

		tx_q->tx_skbuff_dma[entry].buf = des2;
		tx_q->tx_skbuff_dma[entry].len = bmax;
		tx_q->tx_skbuff_dma[entry].is_jumbo = true;

		desc->des3 = cpu_to_le32(des2 + BUF_SIZE_4KiB);
		stmmac_prepare_tx_desc(priv, desc, 1, bmax, csum,
				STMMAC_RING_MODE, 0, false, skb->len);
		tx_q->tx_skbuff[entry] = NULL;
		entry = STMMAC_GET_ENTRY(entry, DMA_TX_SIZE);

		if (priv->extend_desc)
			desc = (struct dma_desc *)(tx_q->dma_etx + entry);
		else
			desc = tx_q->dma_tx + entry;

		des2 = dma_map_single(priv->device, skb->data + bmax, len,
				      DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		if (dma_mapping_error(priv->device, des2))
			return -1;
		tx_q->tx_skbuff_dma[entry].buf = des2;
		tx_q->tx_skbuff_dma[entry].len = len;
		tx_q->tx_skbuff_dma[entry].is_jumbo = true;

		desc->des3 = cpu_to_le32(des2 + BUF_SIZE_4KiB);
		stmmac_prepare_tx_desc(priv, desc, 0, len, csum,
				STMMAC_RING_MODE, 1, !skb_is_nonlinear(skb),
				skb->len);
	} else {
		des2 = dma_map_single(priv->device, skb->data,
				      nopaged_len, DMA_TO_DEVICE);
		desc->des2 = cpu_to_le32(des2);
		if (dma_mapping_error(priv->device, des2))
			return -1;
		tx_q->tx_skbuff_dma[entry].buf = des2;
		tx_q->tx_skbuff_dma[entry].len = nopaged_len;
		tx_q->tx_skbuff_dma[entry].is_jumbo = true;
		desc->des3 = cpu_to_le32(des2 + BUF_SIZE_4KiB);
		stmmac_prepare_tx_desc(priv, desc, 1, nopaged_len, csum,
				STMMAC_RING_MODE, 0, !skb_is_nonlinear(skb),
				skb->len);
	}

	tx_q->cur_tx = entry;

	return entry;
}