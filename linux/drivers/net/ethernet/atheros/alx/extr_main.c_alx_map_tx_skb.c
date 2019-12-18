#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {void* addr; } ;
struct alx_txd {int word1; void* len; TYPE_1__ adrl; int /*<<< orphan*/  vlan_tag; } ;
struct alx_tx_queue {int write_idx; int count; TYPE_3__* bufs; int /*<<< orphan*/  dev; struct alx_txd* tpd; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_7__ {struct sk_buff* skb; } ;
struct TYPE_6__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int TPD_EOP_SHIFT ; 
 int TPD_LSO_V2_SHIFT ; 
 int /*<<< orphan*/  alx_free_txbuf (struct alx_tx_queue*,int) ; 
 void* cpu_to_le16 (int) ; 
 int cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  size ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int alx_map_tx_skb(struct alx_tx_queue *txq, struct sk_buff *skb)
{
	struct alx_txd *tpd, *first_tpd;
	dma_addr_t dma;
	int maplen, f, first_idx = txq->write_idx;

	first_tpd = &txq->tpd[txq->write_idx];
	tpd = first_tpd;

	if (tpd->word1 & (1 << TPD_LSO_V2_SHIFT)) {
		if (++txq->write_idx == txq->count)
			txq->write_idx = 0;

		tpd = &txq->tpd[txq->write_idx];
		tpd->len = first_tpd->len;
		tpd->vlan_tag = first_tpd->vlan_tag;
		tpd->word1 = first_tpd->word1;
	}

	maplen = skb_headlen(skb);
	dma = dma_map_single(txq->dev, skb->data, maplen,
			     DMA_TO_DEVICE);
	if (dma_mapping_error(txq->dev, dma))
		goto err_dma;

	dma_unmap_len_set(&txq->bufs[txq->write_idx], size, maplen);
	dma_unmap_addr_set(&txq->bufs[txq->write_idx], dma, dma);

	tpd->adrl.addr = cpu_to_le64(dma);
	tpd->len = cpu_to_le16(maplen);

	for (f = 0; f < skb_shinfo(skb)->nr_frags; f++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		if (++txq->write_idx == txq->count)
			txq->write_idx = 0;
		tpd = &txq->tpd[txq->write_idx];

		tpd->word1 = first_tpd->word1;

		maplen = skb_frag_size(frag);
		dma = skb_frag_dma_map(txq->dev, frag, 0,
				       maplen, DMA_TO_DEVICE);
		if (dma_mapping_error(txq->dev, dma))
			goto err_dma;
		dma_unmap_len_set(&txq->bufs[txq->write_idx], size, maplen);
		dma_unmap_addr_set(&txq->bufs[txq->write_idx], dma, dma);

		tpd->adrl.addr = cpu_to_le64(dma);
		tpd->len = cpu_to_le16(maplen);
	}

	/* last TPD, set EOP flag and store skb */
	tpd->word1 |= cpu_to_le32(1 << TPD_EOP_SHIFT);
	txq->bufs[txq->write_idx].skb = skb;

	if (++txq->write_idx == txq->count)
		txq->write_idx = 0;

	return 0;

err_dma:
	f = first_idx;
	while (f != txq->write_idx) {
		alx_free_txbuf(txq, f);
		if (++f == txq->count)
			f = 0;
	}
	return -ENOMEM;
}