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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sk_buff {int csum_level; int /*<<< orphan*/  ip_summed; TYPE_2__* dev; int /*<<< orphan*/  protocol; } ;
struct rx_tpa_end_cmp_ext {int dummy; } ;
struct rx_tpa_end_cmp {int /*<<< orphan*/  rx_tpa_end_cmp_misc_v1; } ;
struct bnxt_tpa_info {size_t* data; size_t* data_ptr; unsigned int len; scalar_t__ hash_type; int flags2; int metadata; int /*<<< orphan*/  rss_hash; int /*<<< orphan*/  cfa_code; int /*<<< orphan*/  mapping; } ;
struct bnxt_rx_ring_info {struct bnxt_tpa_info* rx_tpa; } ;
struct bnxt_cp_ring_info {int dummy; } ;
struct bnxt_napi {int in_reset; struct bnxt_rx_ring_info* rx_ring; struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {unsigned int rx_copy_thresh; int rx_offset; int /*<<< orphan*/  rx_dir; int /*<<< orphan*/  rx_buf_use_size; TYPE_1__* pdev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int features; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t BNXT_AGG_EVENT ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_ATTR_WEAK_ORDERING ; 
 int /*<<< orphan*/  EBUSY ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t MAX_SKB_FRAGS ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NEXT_CMP (int) ; 
 scalar_t__ PKT_HASH_TYPE_NONE ; 
 int RING_CMP (int /*<<< orphan*/ ) ; 
 int RX_CMP_FLAGS2_METADATA_TCI_MASK ; 
 int RX_CMP_FLAGS2_METADATA_TPID_SFT ; 
 int RX_CMP_FLAGS2_META_FORMAT_VLAN ; 
 int RX_CMP_FLAGS2_T_L4_CS_CALC ; 
 size_t RX_TPA_END_CMP_AGG_BUFS ; 
 size_t RX_TPA_END_CMP_AGG_BUFS_SHIFT ; 
 int RX_TPA_START_CMP_FLAGS2_L4_CS_CALC ; 
 size_t TPA_END_AGG_ID (struct rx_tpa_end_cmp*) ; 
 scalar_t__ TPA_END_ERRORS (struct rx_tpa_end_cmp_ext*) ; 
 scalar_t__ TPA_END_GRO (struct rx_tpa_end_cmp*) ; 
 size_t* __bnxt_alloc_rx_data (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnxt_abort_tpa (struct bnxt*,struct bnxt_napi*,int,size_t) ; 
 int /*<<< orphan*/  bnxt_agg_bufs_valid (struct bnxt*,struct bnxt_cp_ring_info*,size_t,int /*<<< orphan*/ *) ; 
 struct sk_buff* bnxt_copy_skb (struct bnxt_napi*,size_t*,unsigned int,int /*<<< orphan*/ ) ; 
 int bnxt_discard_rx (struct bnxt*,struct bnxt_napi*,int /*<<< orphan*/ *,struct rx_tpa_end_cmp*) ; 
 int /*<<< orphan*/  bnxt_get_pkt_dev (struct bnxt*,int /*<<< orphan*/ ) ; 
 struct sk_buff* bnxt_gro_skb (struct bnxt*,struct bnxt_tpa_info*,struct rx_tpa_end_cmp*,struct rx_tpa_end_cmp_ext*,struct sk_buff*) ; 
 struct sk_buff* bnxt_rx_pages (struct bnxt*,struct bnxt_napi*,struct sk_buff*,int,size_t) ; 
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  prefetch (size_t*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct sk_buff *bnxt_tpa_end(struct bnxt *bp,
					   struct bnxt_napi *bnapi,
					   u32 *raw_cons,
					   struct rx_tpa_end_cmp *tpa_end,
					   struct rx_tpa_end_cmp_ext *tpa_end1,
					   u8 *event)
{
	struct bnxt_cp_ring_info *cpr = &bnapi->cp_ring;
	struct bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	u8 agg_id = TPA_END_AGG_ID(tpa_end);
	u8 *data_ptr, agg_bufs;
	u16 cp_cons = RING_CMP(*raw_cons);
	unsigned int len;
	struct bnxt_tpa_info *tpa_info;
	dma_addr_t mapping;
	struct sk_buff *skb;
	void *data;

	if (unlikely(bnapi->in_reset)) {
		int rc = bnxt_discard_rx(bp, bnapi, raw_cons, tpa_end);

		if (rc < 0)
			return ERR_PTR(-EBUSY);
		return NULL;
	}

	tpa_info = &rxr->rx_tpa[agg_id];
	data = tpa_info->data;
	data_ptr = tpa_info->data_ptr;
	prefetch(data_ptr);
	len = tpa_info->len;
	mapping = tpa_info->mapping;

	agg_bufs = (le32_to_cpu(tpa_end->rx_tpa_end_cmp_misc_v1) &
		    RX_TPA_END_CMP_AGG_BUFS) >> RX_TPA_END_CMP_AGG_BUFS_SHIFT;

	if (agg_bufs) {
		if (!bnxt_agg_bufs_valid(bp, cpr, agg_bufs, raw_cons))
			return ERR_PTR(-EBUSY);

		*event |= BNXT_AGG_EVENT;
		cp_cons = NEXT_CMP(cp_cons);
	}

	if (unlikely(agg_bufs > MAX_SKB_FRAGS || TPA_END_ERRORS(tpa_end1))) {
		bnxt_abort_tpa(bp, bnapi, cp_cons, agg_bufs);
		if (agg_bufs > MAX_SKB_FRAGS)
			netdev_warn(bp->dev, "TPA frags %d exceeded MAX_SKB_FRAGS %d\n",
				    agg_bufs, (int)MAX_SKB_FRAGS);
		return NULL;
	}

	if (len <= bp->rx_copy_thresh) {
		skb = bnxt_copy_skb(bnapi, data_ptr, len, mapping);
		if (!skb) {
			bnxt_abort_tpa(bp, bnapi, cp_cons, agg_bufs);
			return NULL;
		}
	} else {
		u8 *new_data;
		dma_addr_t new_mapping;

		new_data = __bnxt_alloc_rx_data(bp, &new_mapping, GFP_ATOMIC);
		if (!new_data) {
			bnxt_abort_tpa(bp, bnapi, cp_cons, agg_bufs);
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
			bnxt_abort_tpa(bp, bnapi, cp_cons, agg_bufs);
			return NULL;
		}
		skb_reserve(skb, bp->rx_offset);
		skb_put(skb, len);
	}

	if (agg_bufs) {
		skb = bnxt_rx_pages(bp, bnapi, skb, cp_cons, agg_bufs);
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

	if (TPA_END_GRO(tpa_end))
		skb = bnxt_gro_skb(bp, tpa_info, tpa_end, tpa_end1, skb);

	return skb;
}