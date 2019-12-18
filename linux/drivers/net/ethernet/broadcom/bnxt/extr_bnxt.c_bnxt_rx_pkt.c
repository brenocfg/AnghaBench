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
typedef  int u32 ;
typedef  size_t u16 ;
struct sk_buff {int /*<<< orphan*/  csum_level; int /*<<< orphan*/  ip_summed; TYPE_1__* dev; int /*<<< orphan*/  protocol; } ;
struct rx_tpa_start_cmp_ext {int dummy; } ;
struct rx_tpa_start_cmp {int dummy; } ;
struct rx_tpa_end_cmp_ext {int dummy; } ;
struct rx_tpa_end_cmp {int dummy; } ;
struct rx_cmp_ext {int rx_cmp_cfa_code_errors_v2; int rx_cmp_flags2; int rx_cmp_meta_data; } ;
struct rx_cmp {size_t rx_cmp_opaque; int rx_cmp_misc_v1; int rx_cmp_len_flags_type; int rx_cmp_rss_hash; } ;
struct rx_agg_cmp {int dummy; } ;
struct net_device {int features; } ;
struct bnxt_sw_rx_bd {scalar_t__* data_ptr; int /*<<< orphan*/  mapping; int /*<<< orphan*/ * data; } ;
struct bnxt_rx_ring_info {size_t rx_prod; size_t rx_next_cons; struct bnxt_sw_rx_bd* rx_buf_ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_l4_csum_errors; } ;
struct bnxt_napi {TYPE_2__ cp_ring; struct bnxt_rx_ring_info* rx_ring; } ;
struct bnxt_cp_ring_info {int rx_packets; unsigned int rx_bytes; int /*<<< orphan*/ ** cp_desc_ring; struct bnxt_napi* bnapi; } ;
struct bnxt {unsigned int rx_copy_thresh; struct sk_buff* (* rx_skb_func ) (struct bnxt*,struct bnxt_rx_ring_info*,size_t,void*,scalar_t__*,int /*<<< orphan*/ ,int) ;struct net_device* dev; } ;
typedef  enum pkt_hash_types { ____Placeholder_pkt_hash_types } pkt_hash_types ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 scalar_t__ BNXT_AGG_EVENT ; 
 scalar_t__ BNXT_RX_EVENT ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 scalar_t__ CMP_TYPE_RX_L2_TPA_END_CMP ; 
 scalar_t__ CMP_TYPE_RX_L2_TPA_START_CMP ; 
 scalar_t__ CMP_TYPE_RX_TPA_AGG_CMP ; 
 size_t CP_IDX (size_t) ; 
 size_t CP_RING (size_t) ; 
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 size_t NEXT_CMP (size_t) ; 
 int NEXT_RAW_CMP (int) ; 
 void* NEXT_RX (size_t) ; 
 int PKT_HASH_TYPE_L3 ; 
 int PKT_HASH_TYPE_L4 ; 
 size_t RING_CMP (int) ; 
 int RX_CMPL_ERRORS_BUFFER_ERROR_MASK ; 
 int RX_CMP_AGG_BUFS ; 
 int RX_CMP_AGG_BUFS_SHIFT ; 
 size_t RX_CMP_CFA_CODE (struct rx_cmp_ext*) ; 
 int /*<<< orphan*/  RX_CMP_ENCAP (struct rx_cmp_ext*) ; 
 int RX_CMP_FLAGS2_METADATA_TCI_MASK ; 
 int RX_CMP_FLAGS2_METADATA_TPID_SFT ; 
 int /*<<< orphan*/  RX_CMP_FLAGS2_META_FORMAT_VLAN ; 
 int RX_CMP_HASH_TYPE (struct rx_cmp*) ; 
 scalar_t__ RX_CMP_HASH_VALID (struct rx_cmp*) ; 
 int RX_CMP_L2_ERRORS ; 
 int RX_CMP_L4_CS_ERR_BITS ; 
 scalar_t__ RX_CMP_L4_CS_OK (struct rx_cmp_ext*) ; 
 int RX_CMP_LEN_SHIFT ; 
 int RX_CMP_PAYLOAD_OFFSET ; 
 scalar_t__ RX_CMP_TYPE (struct rx_cmp*) ; 
 int /*<<< orphan*/  RX_CMP_VALID (struct rx_cmp_ext*,int) ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  bnxt_agg_bufs_valid (struct bnxt*,struct bnxt_cp_ring_info*,scalar_t__,int*) ; 
 struct sk_buff* bnxt_copy_skb (struct bnxt_napi*,scalar_t__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_deliver_skb (struct bnxt*,struct bnxt_napi*,struct sk_buff*) ; 
 int bnxt_discard_rx (struct bnxt*,struct bnxt_cp_ring_info*,int*,struct rx_cmp*) ; 
 int /*<<< orphan*/  bnxt_get_pkt_dev (struct bnxt*,size_t) ; 
 int /*<<< orphan*/  bnxt_reuse_rx_agg_bufs (struct bnxt_cp_ring_info*,size_t,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  bnxt_reuse_rx_data (struct bnxt_rx_ring_info*,size_t,void*) ; 
 struct sk_buff* bnxt_rx_pages (struct bnxt*,struct bnxt_cp_ring_info*,struct sk_buff*,size_t,scalar_t__,int) ; 
 scalar_t__ bnxt_rx_xdp (struct bnxt*,struct bnxt_rx_ring_info*,size_t,void*,scalar_t__**,unsigned int*,scalar_t__*) ; 
 int /*<<< orphan*/  bnxt_sched_reset (struct bnxt*,struct bnxt_rx_ring_info*) ; 
 int /*<<< orphan*/  bnxt_tpa_agg (struct bnxt*,struct bnxt_rx_ring_info*,struct rx_agg_cmp*) ; 
 struct sk_buff* bnxt_tpa_end (struct bnxt*,struct bnxt_cp_ring_info*,int*,struct rx_tpa_end_cmp*,struct rx_tpa_end_cmp_ext*,scalar_t__*) ; 
 int /*<<< orphan*/  bnxt_tpa_start (struct bnxt*,struct bnxt_rx_ring_info*,struct rx_tpa_start_cmp*,struct rx_tpa_start_cmp_ext*) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (size_t) ; 
 int le32_to_cpu (int) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int,...) ; 
 int /*<<< orphan*/  prefetch (scalar_t__*) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int,int) ; 
 struct sk_buff* stub1 (struct bnxt*,struct bnxt_rx_ring_info*,size_t,void*,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bnxt_rx_pkt(struct bnxt *bp, struct bnxt_cp_ring_info *cpr,
		       u32 *raw_cons, u8 *event)
{
	struct bnxt_napi *bnapi = cpr->bnapi;
	struct bnxt_rx_ring_info *rxr = bnapi->rx_ring;
	struct net_device *dev = bp->dev;
	struct rx_cmp *rxcmp;
	struct rx_cmp_ext *rxcmp1;
	u32 tmp_raw_cons = *raw_cons;
	u16 cfa_code, cons, prod, cp_cons = RING_CMP(tmp_raw_cons);
	struct bnxt_sw_rx_bd *rx_buf;
	unsigned int len;
	u8 *data_ptr, agg_bufs, cmp_type;
	dma_addr_t dma_addr;
	struct sk_buff *skb;
	void *data;
	int rc = 0;
	u32 misc;

	rxcmp = (struct rx_cmp *)
			&cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];

	cmp_type = RX_CMP_TYPE(rxcmp);

	if (cmp_type == CMP_TYPE_RX_TPA_AGG_CMP) {
		bnxt_tpa_agg(bp, rxr, (struct rx_agg_cmp *)rxcmp);
		goto next_rx_no_prod_no_len;
	}

	tmp_raw_cons = NEXT_RAW_CMP(tmp_raw_cons);
	cp_cons = RING_CMP(tmp_raw_cons);
	rxcmp1 = (struct rx_cmp_ext *)
			&cpr->cp_desc_ring[CP_RING(cp_cons)][CP_IDX(cp_cons)];

	if (!RX_CMP_VALID(rxcmp1, tmp_raw_cons))
		return -EBUSY;

	prod = rxr->rx_prod;

	if (cmp_type == CMP_TYPE_RX_L2_TPA_START_CMP) {
		bnxt_tpa_start(bp, rxr, (struct rx_tpa_start_cmp *)rxcmp,
			       (struct rx_tpa_start_cmp_ext *)rxcmp1);

		*event |= BNXT_RX_EVENT;
		goto next_rx_no_prod_no_len;

	} else if (cmp_type == CMP_TYPE_RX_L2_TPA_END_CMP) {
		skb = bnxt_tpa_end(bp, cpr, &tmp_raw_cons,
				   (struct rx_tpa_end_cmp *)rxcmp,
				   (struct rx_tpa_end_cmp_ext *)rxcmp1, event);

		if (IS_ERR(skb))
			return -EBUSY;

		rc = -ENOMEM;
		if (likely(skb)) {
			bnxt_deliver_skb(bp, bnapi, skb);
			rc = 1;
		}
		*event |= BNXT_RX_EVENT;
		goto next_rx_no_prod_no_len;
	}

	cons = rxcmp->rx_cmp_opaque;
	if (unlikely(cons != rxr->rx_next_cons)) {
		int rc1 = bnxt_discard_rx(bp, cpr, raw_cons, rxcmp);

		netdev_warn(bp->dev, "RX cons %x != expected cons %x\n",
			    cons, rxr->rx_next_cons);
		bnxt_sched_reset(bp, rxr);
		return rc1;
	}
	rx_buf = &rxr->rx_buf_ring[cons];
	data = rx_buf->data;
	data_ptr = rx_buf->data_ptr;
	prefetch(data_ptr);

	misc = le32_to_cpu(rxcmp->rx_cmp_misc_v1);
	agg_bufs = (misc & RX_CMP_AGG_BUFS) >> RX_CMP_AGG_BUFS_SHIFT;

	if (agg_bufs) {
		if (!bnxt_agg_bufs_valid(bp, cpr, agg_bufs, &tmp_raw_cons))
			return -EBUSY;

		cp_cons = NEXT_CMP(cp_cons);
		*event |= BNXT_AGG_EVENT;
	}
	*event |= BNXT_RX_EVENT;

	rx_buf->data = NULL;
	if (rxcmp1->rx_cmp_cfa_code_errors_v2 & RX_CMP_L2_ERRORS) {
		u32 rx_err = le32_to_cpu(rxcmp1->rx_cmp_cfa_code_errors_v2);

		bnxt_reuse_rx_data(rxr, cons, data);
		if (agg_bufs)
			bnxt_reuse_rx_agg_bufs(cpr, cp_cons, 0, agg_bufs,
					       false);

		rc = -EIO;
		if (rx_err & RX_CMPL_ERRORS_BUFFER_ERROR_MASK) {
			netdev_warn(bp->dev, "RX buffer error %x\n", rx_err);
			bnxt_sched_reset(bp, rxr);
		}
		goto next_rx_no_len;
	}

	len = le32_to_cpu(rxcmp->rx_cmp_len_flags_type) >> RX_CMP_LEN_SHIFT;
	dma_addr = rx_buf->mapping;

	if (bnxt_rx_xdp(bp, rxr, cons, data, &data_ptr, &len, event)) {
		rc = 1;
		goto next_rx;
	}

	if (len <= bp->rx_copy_thresh) {
		skb = bnxt_copy_skb(bnapi, data_ptr, len, dma_addr);
		bnxt_reuse_rx_data(rxr, cons, data);
		if (!skb) {
			if (agg_bufs)
				bnxt_reuse_rx_agg_bufs(cpr, cp_cons, 0,
						       agg_bufs, false);
			rc = -ENOMEM;
			goto next_rx;
		}
	} else {
		u32 payload;

		if (rx_buf->data_ptr == data_ptr)
			payload = misc & RX_CMP_PAYLOAD_OFFSET;
		else
			payload = 0;
		skb = bp->rx_skb_func(bp, rxr, cons, data, data_ptr, dma_addr,
				      payload | len);
		if (!skb) {
			rc = -ENOMEM;
			goto next_rx;
		}
	}

	if (agg_bufs) {
		skb = bnxt_rx_pages(bp, cpr, skb, cp_cons, agg_bufs, false);
		if (!skb) {
			rc = -ENOMEM;
			goto next_rx;
		}
	}

	if (RX_CMP_HASH_VALID(rxcmp)) {
		u32 hash_type = RX_CMP_HASH_TYPE(rxcmp);
		enum pkt_hash_types type = PKT_HASH_TYPE_L4;

		/* RSS profiles 1 and 3 with extract code 0 for inner 4-tuple */
		if (hash_type != 1 && hash_type != 3)
			type = PKT_HASH_TYPE_L3;
		skb_set_hash(skb, le32_to_cpu(rxcmp->rx_cmp_rss_hash), type);
	}

	cfa_code = RX_CMP_CFA_CODE(rxcmp1);
	skb->protocol = eth_type_trans(skb, bnxt_get_pkt_dev(bp, cfa_code));

	if ((rxcmp1->rx_cmp_flags2 &
	     cpu_to_le32(RX_CMP_FLAGS2_META_FORMAT_VLAN)) &&
	    (skb->dev->features & NETIF_F_HW_VLAN_CTAG_RX)) {
		u32 meta_data = le32_to_cpu(rxcmp1->rx_cmp_meta_data);
		u16 vtag = meta_data & RX_CMP_FLAGS2_METADATA_TCI_MASK;
		u16 vlan_proto = meta_data >> RX_CMP_FLAGS2_METADATA_TPID_SFT;

		__vlan_hwaccel_put_tag(skb, htons(vlan_proto), vtag);
	}

	skb_checksum_none_assert(skb);
	if (RX_CMP_L4_CS_OK(rxcmp1)) {
		if (dev->features & NETIF_F_RXCSUM) {
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			skb->csum_level = RX_CMP_ENCAP(rxcmp1);
		}
	} else {
		if (rxcmp1->rx_cmp_cfa_code_errors_v2 & RX_CMP_L4_CS_ERR_BITS) {
			if (dev->features & NETIF_F_RXCSUM)
				bnapi->cp_ring.rx_l4_csum_errors++;
		}
	}

	bnxt_deliver_skb(bp, bnapi, skb);
	rc = 1;

next_rx:
	cpr->rx_packets += 1;
	cpr->rx_bytes += len;

next_rx_no_len:
	rxr->rx_prod = NEXT_RX(prod);
	rxr->rx_next_cons = NEXT_RX(cons);

next_rx_no_prod_no_len:
	*raw_cons = tmp_raw_cons;

	return rc;
}