#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct TYPE_7__ {unsigned int produce_idx; unsigned int count; } ;
struct emac_tx_queue {TYPE_3__ tpd; } ;
struct emac_tpd {int dummy; } ;
struct emac_buffer {unsigned int length; void* dma_addr; struct sk_buff* skb; } ;
struct emac_adapter {TYPE_2__* netdev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_8__ {unsigned int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 struct emac_buffer* GET_TPD_BUFFER (struct emac_tx_queue*,unsigned int) ; 
 int /*<<< orphan*/  TPD_BUFFER_ADDR_H_SET (struct emac_tpd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPD_BUFFER_ADDR_L_SET (struct emac_tpd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPD_BUF_LEN_SET (struct emac_tpd*,unsigned int) ; 
 scalar_t__ TPD_LSO (struct emac_tpd*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 void* dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_tx_tpd_create (struct emac_adapter*,struct emac_tx_queue*,struct emac_tpd*) ; 
 int /*<<< orphan*/  emac_tx_tpd_mark_last (struct emac_adapter*,struct emac_tx_queue*) ; 
 int /*<<< orphan*/  lower_32_bits (void*) ; 
 int /*<<< orphan*/  offset_in_page (scalar_t__) ; 
 void* skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 unsigned int tcp_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  upper_32_bits (void*) ; 
 int /*<<< orphan*/  virt_to_page (scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void emac_tx_fill_tpd(struct emac_adapter *adpt,
			     struct emac_tx_queue *tx_q, struct sk_buff *skb,
			     struct emac_tpd *tpd)
{
	unsigned int nr_frags = skb_shinfo(skb)->nr_frags;
	unsigned int first = tx_q->tpd.produce_idx;
	unsigned int len = skb_headlen(skb);
	struct emac_buffer *tpbuf = NULL;
	unsigned int mapped_len = 0;
	unsigned int i;
	int count = 0;
	int ret;

	/* if Large Segment Offload is (in TCP Segmentation Offload struct) */
	if (TPD_LSO(tpd)) {
		mapped_len = skb_transport_offset(skb) + tcp_hdrlen(skb);

		tpbuf = GET_TPD_BUFFER(tx_q, tx_q->tpd.produce_idx);
		tpbuf->length = mapped_len;
		tpbuf->dma_addr = dma_map_page(adpt->netdev->dev.parent,
					       virt_to_page(skb->data),
					       offset_in_page(skb->data),
					       tpbuf->length,
					       DMA_TO_DEVICE);
		ret = dma_mapping_error(adpt->netdev->dev.parent,
					tpbuf->dma_addr);
		if (ret)
			goto error;

		TPD_BUFFER_ADDR_L_SET(tpd, lower_32_bits(tpbuf->dma_addr));
		TPD_BUFFER_ADDR_H_SET(tpd, upper_32_bits(tpbuf->dma_addr));
		TPD_BUF_LEN_SET(tpd, tpbuf->length);
		emac_tx_tpd_create(adpt, tx_q, tpd);
		count++;
	}

	if (mapped_len < len) {
		tpbuf = GET_TPD_BUFFER(tx_q, tx_q->tpd.produce_idx);
		tpbuf->length = len - mapped_len;
		tpbuf->dma_addr = dma_map_page(adpt->netdev->dev.parent,
					       virt_to_page(skb->data +
							    mapped_len),
					       offset_in_page(skb->data +
							      mapped_len),
					       tpbuf->length, DMA_TO_DEVICE);
		ret = dma_mapping_error(adpt->netdev->dev.parent,
					tpbuf->dma_addr);
		if (ret)
			goto error;

		TPD_BUFFER_ADDR_L_SET(tpd, lower_32_bits(tpbuf->dma_addr));
		TPD_BUFFER_ADDR_H_SET(tpd, upper_32_bits(tpbuf->dma_addr));
		TPD_BUF_LEN_SET(tpd, tpbuf->length);
		emac_tx_tpd_create(adpt, tx_q, tpd);
		count++;
	}

	for (i = 0; i < nr_frags; i++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		tpbuf = GET_TPD_BUFFER(tx_q, tx_q->tpd.produce_idx);
		tpbuf->length = skb_frag_size(frag);
		tpbuf->dma_addr = skb_frag_dma_map(adpt->netdev->dev.parent,
						   frag, 0, tpbuf->length,
						   DMA_TO_DEVICE);
		ret = dma_mapping_error(adpt->netdev->dev.parent,
					tpbuf->dma_addr);
		if (ret)
			goto error;

		TPD_BUFFER_ADDR_L_SET(tpd, lower_32_bits(tpbuf->dma_addr));
		TPD_BUFFER_ADDR_H_SET(tpd, upper_32_bits(tpbuf->dma_addr));
		TPD_BUF_LEN_SET(tpd, tpbuf->length);
		emac_tx_tpd_create(adpt, tx_q, tpd);
		count++;
	}

	/* The last tpd */
	wmb();
	emac_tx_tpd_mark_last(adpt, tx_q);

	/* The last buffer info contain the skb address,
	 * so it will be freed after unmap
	 */
	tpbuf->skb = skb;

	return;

error:
	/* One of the memory mappings failed, so undo everything */
	tx_q->tpd.produce_idx = first;

	while (count--) {
		tpbuf = GET_TPD_BUFFER(tx_q, first);
		dma_unmap_page(adpt->netdev->dev.parent, tpbuf->dma_addr,
			       tpbuf->length, DMA_TO_DEVICE);
		tpbuf->dma_addr = 0;
		tpbuf->length = 0;

		if (++first == tx_q->tpd.count)
			first = 0;
	}

	dev_kfree_skb(skb);
}