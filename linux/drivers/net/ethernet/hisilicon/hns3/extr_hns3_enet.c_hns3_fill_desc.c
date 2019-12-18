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
typedef  unsigned int u16 ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int /*<<< orphan*/  sw_err_cnt; } ;
struct hns3_enet_ring {size_t next_to_use; struct hns3_desc* desc; struct hns3_desc_cb* desc_cb; int /*<<< orphan*/  syncp; TYPE_1__ stats; } ;
struct hns3_desc_cb {unsigned int length; int type; void* dma; void* priv; } ;
struct TYPE_4__ {void* bdtp_fe_sc_vld_ra_ri; void* send_size; } ;
struct hns3_desc {TYPE_2__ tx; void* addr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  enum hns_desc_type { ____Placeholder_hns_desc_type } hns_desc_type ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 int DESC_TYPE_PAGE ; 
 int DESC_TYPE_SKB ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 unsigned int HNS3_MAX_BD_SIZE ; 
 unsigned int HNS3_TX_LAST_SIZE_M ; 
 void* cpu_to_le16 (unsigned int) ; 
 void* cpu_to_le64 (void*) ; 
 void* dma_map_single (struct device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (struct device*,void*) ; 
 int hns3_fill_skb_desc (struct hns3_enet_ring*,struct sk_buff*,struct hns3_desc*) ; 
 int /*<<< orphan*/  hns3_set_txbd_baseinfo (unsigned int*,int) ; 
 unsigned int hns3_tx_bd_count (unsigned int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  next_to_use ; 
 int /*<<< orphan*/  ring_ptr_move_fw (struct hns3_enet_ring*,int /*<<< orphan*/ ) ; 
 struct device* ring_to_dev (struct hns3_enet_ring*) ; 
 void* skb_frag_dma_map (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hns3_fill_desc(struct hns3_enet_ring *ring, void *priv,
			  unsigned int size, int frag_end,
			  enum hns_desc_type type)
{
	struct hns3_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_use];
	struct hns3_desc *desc = &ring->desc[ring->next_to_use];
	struct device *dev = ring_to_dev(ring);
	skb_frag_t *frag;
	unsigned int frag_buf_num;
	int k, sizeoflast;
	dma_addr_t dma;

	if (type == DESC_TYPE_SKB) {
		struct sk_buff *skb = (struct sk_buff *)priv;
		int ret;

		ret = hns3_fill_skb_desc(ring, skb, desc);
		if (unlikely(ret))
			return ret;

		dma = dma_map_single(dev, skb->data, size, DMA_TO_DEVICE);
	} else {
		frag = (skb_frag_t *)priv;
		dma = skb_frag_dma_map(dev, frag, 0, size, DMA_TO_DEVICE);
	}

	if (unlikely(dma_mapping_error(dev, dma))) {
		u64_stats_update_begin(&ring->syncp);
		ring->stats.sw_err_cnt++;
		u64_stats_update_end(&ring->syncp);
		return -ENOMEM;
	}

	desc_cb->length = size;

	if (likely(size <= HNS3_MAX_BD_SIZE)) {
		u16 bdtp_fe_sc_vld_ra_ri = 0;

		desc_cb->priv = priv;
		desc_cb->dma = dma;
		desc_cb->type = type;
		desc->addr = cpu_to_le64(dma);
		desc->tx.send_size = cpu_to_le16(size);
		hns3_set_txbd_baseinfo(&bdtp_fe_sc_vld_ra_ri, frag_end);
		desc->tx.bdtp_fe_sc_vld_ra_ri =
			cpu_to_le16(bdtp_fe_sc_vld_ra_ri);

		ring_ptr_move_fw(ring, next_to_use);
		return 0;
	}

	frag_buf_num = hns3_tx_bd_count(size);
	sizeoflast = size & HNS3_TX_LAST_SIZE_M;
	sizeoflast = sizeoflast ? sizeoflast : HNS3_MAX_BD_SIZE;

	/* When frag size is bigger than hardware limit, split this frag */
	for (k = 0; k < frag_buf_num; k++) {
		u16 bdtp_fe_sc_vld_ra_ri = 0;

		/* The txbd's baseinfo of DESC_TYPE_PAGE & DESC_TYPE_SKB */
		desc_cb->priv = priv;
		desc_cb->dma = dma + HNS3_MAX_BD_SIZE * k;
		desc_cb->type = (type == DESC_TYPE_SKB && !k) ?
				DESC_TYPE_SKB : DESC_TYPE_PAGE;

		/* now, fill the descriptor */
		desc->addr = cpu_to_le64(dma + HNS3_MAX_BD_SIZE * k);
		desc->tx.send_size = cpu_to_le16((k == frag_buf_num - 1) ?
				     (u16)sizeoflast : (u16)HNS3_MAX_BD_SIZE);
		hns3_set_txbd_baseinfo(&bdtp_fe_sc_vld_ra_ri,
				       frag_end && (k == frag_buf_num - 1) ?
						1 : 0);
		desc->tx.bdtp_fe_sc_vld_ra_ri =
				cpu_to_le16(bdtp_fe_sc_vld_ra_ri);

		/* move ring pointer to next */
		ring_ptr_move_fw(ring, next_to_use);

		desc_cb = &ring->desc_cb[ring->next_to_use];
		desc = &ring->desc[ring->next_to_use];
	}

	return 0;
}