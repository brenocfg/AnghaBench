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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct sk_buff {int csum_level; int /*<<< orphan*/  ip_summed; TYPE_2__* dev; int /*<<< orphan*/  protocol; } ;
struct rx_tpa_end_cmp_ext {int dummy; } ;
struct rx_tpa_end_cmp {int dummy; } ;
struct bnxt_tpa_info {scalar_t__ agg_count; scalar_t__* data; scalar_t__* data_ptr; unsigned int len; scalar_t__ hash_type; int flags2; size_t metadata; int /*<<< orphan*/  rss_hash; int /*<<< orphan*/  cfa_code; int /*<<< orphan*/  mapping; } ;
struct bnxt_rx_ring_info {struct bnxt_tpa_info* rx_tpa; } ;
struct bnxt_napi {int in_reset; struct bnxt_rx_ring_info* rx_ring; } ;
struct bnxt_cp_ring_info {struct bnxt_napi* bnapi; } ;
struct bnxt {int flags; unsigned int rx_copy_thresh; int rx_offset; int /*<<< orphan*/  rx_dir; int /*<<< orphan*/  rx_buf_use_size; TYPE_1__* pdev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int features; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNXT_AGG_EVENT ; 
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_GRO ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_ATTR_WEAK_ORDERING ; 
 int /*<<< orphan*/  EBUSY ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 size_t NEXT_CMP (size_t) ; 
 scalar_t__ PKT_HASH_TYPE_NONE ; 
 size_t RING_CMP (int /*<<< orphan*/ ) ; 
 size_t RX_CMP_FLAGS2_METADATA_TCI_MASK ; 
 size_t RX_CMP_FLAGS2_METADATA_TPID_SFT ; 
 int RX_CMP_FLAGS2_META_FORMAT_VLAN ; 
 int RX_CMP_FLAGS2_T_L4_CS_CALC ; 
 int RX_TPA_START_CMP_FLAGS2_L4_CS_CALC ; 
 scalar_t__ TPA_END_AGG_BUFS (struct rx_tpa_end_cmp*) ; 
 scalar_t__ TPA_END_AGG_BUFS_P5 (struct rx_tpa_end_cmp_ext*) ; 
 size_t TPA_END_AGG_ID (struct rx_tpa_end_cmp*) ; 
 size_t TPA_END_AGG_ID_P5 (struct rx_tpa_end_cmp*) ; 
 scalar_t__ TPA_END_ERRORS (struct rx_tpa_end_cmp_ext*) ; 
 int /*<<< orphan*/  TPA_END_GRO (struct rx_tpa_end_cmp*) ; 
 scalar_t__* __bnxt_alloc_rx_data (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bnxt_abort_tpa (struct bnxt_cp_ring_info*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  bnxt_agg_bufs_valid (struct bnxt*,struct bnxt_cp_ring_info*,scalar_t__,int /*<<< orphan*/ *) ; 
 struct sk_buff* bnxt_copy_skb (struct bnxt_napi*,scalar_t__*,unsigned int,int /*<<< orphan*/ ) ; 
 int bnxt_discard_rx (struct bnxt*,struct bnxt_cp_ring_info*,int /*<<< orphan*/ *,struct rx_tpa_end_cmp*) ; 
 int /*<<< orphan*/  bnxt_free_agg_idx (struct bnxt_rx_ring_info*,size_t) ; 
 int /*<<< orphan*/  bnxt_get_pkt_dev (struct bnxt*,int /*<<< orphan*/ ) ; 
 struct sk_buff* bnxt_gro_skb (struct bnxt*,struct bnxt_tpa_info*,struct rx_tpa_end_cmp*,struct rx_tpa_end_cmp_ext*,struct sk_buff*) ; 
 size_t bnxt_lookup_agg_idx (struct bnxt_rx_ring_info*,size_t) ; 
 struct sk_buff* bnxt_rx_pages (struct bnxt*,struct bnxt_cp_ring_info*,struct sk_buff*,size_t,scalar_t__,int) ; 
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (size_t) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  prefetch (scalar_t__*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct sk_buff *bnxt_tpa_end(struct bnxt *bp,
					   struct bnxt_cp_ring_info *cpr,
					   u32 *raw_cons,
					   struct rx_tpa_end_cmp *tpa_end,
					   struct rx_tpa_end_cmp_ext *tpa_end1,
					   u8 *event)
{
	struct bnxt_napi *bnapi = cpr->bnapi;
	struct bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	u8 *data_ptr, agg_bufs;
	unsigned int len;
	struct bnxt_tpa_info *tpa_info;
	dma_addr_t mapping;
	struct sk_buff *skb;
	u16 idx = 0, agg_id;
	void *data;
	bool gro;

	if (unlikely(bnapi->in_reset)) {
		int rc = bnxt_discard_rx(bp, cpr, raw_cons, tpa_end);

		if (rc < 0)
			return ERR_PTR(-EBUSY);
		return NULL;
	}

	if (bp->flags & BNXT_FLAG_CHIP_P5) {
		agg_id = TPA_END_AGG_ID_P5(tpa_end);
		agg_id = bnxt_lookup_agg_idx(rxr, agg_id);
		agg_bufs = TPA_END_AGG_BUFS_P5(tpa_end1);
		tpa_info = &rxr->rx_tpa[agg_id];
		if (unlikely(agg_bufs != tpa_info->agg_count)) {
			netdev_warn(bp->dev, "TPA end agg_buf %d != expected agg_bufs %d\n",
				    agg_bufs, tpa_info->agg_count);
			agg_bufs = tpa_info->agg_count;
		}
		tpa_info->agg_count = 0;
		*event |= BNXT_AGG_EVENT;
		bnxt_free_agg_idx(rxr, agg_id);
		idx = agg_id;
		gro = !!(bp->flags & BNXT_FLAG_GRO);
	} else {
		agg_id = TPA_END_AGG_ID(tpa_end);
		agg_bufs = TPA_END_AGG_BUFS(tpa_end);
		tpa_info = &rxr->rx_tpa[agg_id];
		idx = RING_CMP(*raw_cons);
		if (agg_bufs) {
			if (!bnxt_agg_bufs_valid(bp, cpr, agg_bufs, raw_cons))
				return ERR_PTR(-EBUSY);

			*event |= BNXT_AGG_EVENT;
			idx = NEXT_CMP(idx);
		}
		gro = !!TPA_END_GRO(tpa_end);
	}
	data = tpa_info->data;
	data_ptr = tpa_info->data_ptr;
	prefetch(data_ptr);
	len = tpa_info->len;
	mapping = tpa_info->mapping;

	if (unlikely(agg_bufs > MAX_SKB_FRAGS || TPA_END_ERRORS(tpa_end1))) {
		bnxt_abort_tpa(cpr, idx, agg_bufs);
		if (agg_bufs > MAX_SKB_FRAGS)
			netdev_warn(bp->dev, "TPA frags %d exceeded MAX_SKB_FRAGS %d\n",
				    agg_bufs, (int)MAX_SKB_FRAGS);
		return NULL;
	}

	if (len <= bp->rx_copy_thresh) {
		skb = bnxt_copy_skb(bnapi, data_ptr, len, mapping);
		if (!skb) {
			bnxt_abort_tpa(cpr, idx, agg_bufs);
			return NULL;
		}
	} else {
		u8 *new_data;
		dma_addr_t new_mapping;

		new_data = __bnxt_alloc_rx_data(bp, &new_mapping, GFP_ATOMIC);
		if (!new_data) {
			bnxt_abort_tpa(cpr, idx, agg_bufs);
			return NULL;
		}

		tpa_info->data = new_data;
		tpa_info->data_ptr = new_data + bp->rx_offset;
		tpa_info->mapping = new_mapping;

		skb = build_skb(data, 0);
		dma_unmap_single_attrs(&bp->pdev->dev, mapping,
				       bp->rx_buf_use_size, bp->rx_dir,
				       DMA_ATTR_WEAK_ORDERING);

		if (!skb) {
			kfree(data);
			bnxt_abort_tpa(cpr, idx, agg_bufs);
			return NULL;
		}
		skb_reserve(skb, bp->rx_offset);
		skb_put(skb, len);
	}

	if (agg_bufs) {
		skb = bnxt_rx_pages(bp, cpr, skb, idx, agg_bufs, true);
		if (!skb) {
			/* Page reuse already handled by bnxt_rx_pages(). */
			return NULL;
		}
	}

	skb->protocol =
		eth_type_trans(skb, bnxt_get_pkt_dev(bp, tpa_info->cfa_code));

	if (tpa_info->hash_type != PKT_HASH_TYPE_NONE)
		skb_set_hash(skb, tpa_info->rss_hash, tpa_info->hash_type);

	if ((tpa_info->flags2 & RX_CMP_FLAGS2_META_FORMAT_VLAN) &&
	    (skb->dev->features & NETIF_F_HW_VLAN_CTAG_RX)) {
		u16 vlan_proto = tpa_info->metadata >>
			RX_CMP_FLAGS2_METADATA_TPID_SFT;
		u16 vtag = tpa_info->metadata & RX_CMP_FLAGS2_METADATA_TCI_MASK;

		__vlan_hwaccel_put_tag(skb, htons(vlan_proto), vtag);
	}

	skb_checksum_none_assert(skb);
	if (likely(tpa_info->flags2 & RX_TPA_START_CMP_FLAGS2_L4_CS_CALC)) {
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb->csum_level =
			(tpa_info->flags2 & RX_CMP_FLAGS2_T_L4_CS_CALC) >> 3;
	}

	if (gro)
		skb = bnxt_gro_skb(bp, tpa_info, tpa_end, tpa_end1, skb);

	return skb;
}