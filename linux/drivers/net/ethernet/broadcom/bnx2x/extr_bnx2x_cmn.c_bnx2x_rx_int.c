#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct eth_fast_path_rx_cqe {int type_error_flags; size_t queue_index; size_t placement_offset; int /*<<< orphan*/  vlan_tag; TYPE_1__ pars_flags; int /*<<< orphan*/  pkt_len_or_gro_seg_len; int /*<<< orphan*/  rss_hash_result; int /*<<< orphan*/  status_flags; } ;
struct TYPE_11__ {size_t queue_index; int /*<<< orphan*/  pkt_len; } ;
union eth_rx_cqe {struct eth_fast_path_rx_cqe fast_path_cqe; TYPE_4__ end_agg_cqe; } ;
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct sw_rx_bd {int* data; } ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct bnx2x_fastpath {size_t rx_bd_cons; size_t rx_bd_prod; size_t rx_comp_cons; size_t rx_comp_prod; scalar_t__ mode; int /*<<< orphan*/  rx_sge_prod; union eth_rx_cqe* rx_comp_ring; int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_queue; int /*<<< orphan*/  rx_frag_size; int /*<<< orphan*/  rx_buf_size; struct bnx2x_agg_info* tpa_info; struct sw_rx_bd* rx_buf_ring; int /*<<< orphan*/  index; struct bnx2x* bp; } ;
struct bnx2x_agg_info {size_t len_on_bd; size_t full_page; } ;
struct bnx2x {int panic; TYPE_3__* dev; TYPE_2__* pdev; } ;
typedef  enum pkt_hash_types { ____Placeholder_pkt_hash_types } pkt_hash_types ;
typedef  enum eth_rx_cqe_type { ____Placeholder_eth_rx_cqe_type } eth_rx_cqe_type ;
struct TYPE_12__ {int /*<<< orphan*/  rx_skb_alloc_failed; int /*<<< orphan*/  rx_err_discard_pkt; } ;
struct TYPE_10__ {scalar_t__ mtu; int features; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ BNX2X_IS_CQE_COMPLETED (struct eth_fast_path_rx_cqe*) ; 
 int /*<<< orphan*/  BNX2X_SEED_CQE (struct eth_fast_path_rx_cqe*) ; 
 int /*<<< orphan*/  CQE_TYPE (int) ; 
 int /*<<< orphan*/  CQE_TYPE_FAST (int) ; 
 int CQE_TYPE_SLOW (int) ; 
 scalar_t__ CQE_TYPE_START (int) ; 
 scalar_t__ CQE_TYPE_STOP (int) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DP (int,char*,...) ; 
 int ETH_FAST_PATH_RX_CQE_PTP_PKT_SHIFT ; 
 int ETH_FAST_PATH_RX_CQE_TYPE ; 
 scalar_t__ ETH_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int ETH_RX_ERROR_FALGS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_MSG_RX_ERR ; 
 int NETIF_MSG_RX_STATUS ; 
 size_t NET_SKB_PAD ; 
 size_t NEXT_RCQ_IDX (size_t) ; 
 size_t NEXT_RX_IDX (size_t) ; 
 int PARSING_FLAGS_VLAN ; 
 size_t RCQ_BD (size_t) ; 
 size_t RX_BD (size_t) ; 
 size_t RX_COPY_THRESH ; 
 size_t SGE_PAGE_ALIGN (size_t) ; 
 size_t SGE_PAGE_SHIFT ; 
 scalar_t__ TPA_MODE_DISABLED ; 
 scalar_t__ TPA_MODE_GRO ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bnx2x_alloc_rx_data (struct bnx2x*,struct bnx2x_fastpath*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_csum_validate (struct sk_buff*,union eth_rx_cqe*,struct bnx2x_fastpath*,TYPE_6__*) ; 
 TYPE_6__* bnx2x_fp_qstats (struct bnx2x*,struct bnx2x_fastpath*) ; 
 int /*<<< orphan*/  bnx2x_frag_free (struct bnx2x_fastpath*,int*) ; 
 int /*<<< orphan*/  bnx2x_get_rxhash (struct bnx2x*,struct eth_fast_path_rx_cqe*,int*) ; 
 int /*<<< orphan*/  bnx2x_reuse_rx_data (struct bnx2x_fastpath*,size_t,size_t) ; 
 int /*<<< orphan*/  bnx2x_set_rx_ts (struct bnx2x*,struct sk_buff*) ; 
 int /*<<< orphan*/  bnx2x_sp_event (struct bnx2x_fastpath*,union eth_rx_cqe*) ; 
 int /*<<< orphan*/  bnx2x_tpa_start (struct bnx2x_fastpath*,size_t,size_t,size_t,struct eth_fast_path_rx_cqe*) ; 
 int /*<<< orphan*/  bnx2x_tpa_stop (struct bnx2x*,struct bnx2x_fastpath*,struct bnx2x_agg_info*,size_t,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  bnx2x_update_rx_prod (struct bnx2x*,struct bnx2x_fastpath*,size_t,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_update_sge_prod (struct bnx2x_fastpath*,size_t,TYPE_4__*) ; 
 struct sk_buff* build_skb (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct sw_rx_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_3__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,size_t) ; 
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  prefetch (int*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bnx2x_rx_int(struct bnx2x_fastpath *fp, int budget)
{
	struct bnx2x *bp = fp->bp;
	u16 bd_cons, bd_prod, bd_prod_fw, comp_ring_cons;
	u16 sw_comp_cons, sw_comp_prod;
	int rx_pkt = 0;
	union eth_rx_cqe *cqe;
	struct eth_fast_path_rx_cqe *cqe_fp;

#ifdef BNX2X_STOP_ON_ERROR
	if (unlikely(bp->panic))
		return 0;
#endif
	if (budget <= 0)
		return rx_pkt;

	bd_cons = fp->rx_bd_cons;
	bd_prod = fp->rx_bd_prod;
	bd_prod_fw = bd_prod;
	sw_comp_cons = fp->rx_comp_cons;
	sw_comp_prod = fp->rx_comp_prod;

	comp_ring_cons = RCQ_BD(sw_comp_cons);
	cqe = &fp->rx_comp_ring[comp_ring_cons];
	cqe_fp = &cqe->fast_path_cqe;

	DP(NETIF_MSG_RX_STATUS,
	   "queue[%d]: sw_comp_cons %u\n", fp->index, sw_comp_cons);

	while (BNX2X_IS_CQE_COMPLETED(cqe_fp)) {
		struct sw_rx_bd *rx_buf = NULL;
		struct sk_buff *skb;
		u8 cqe_fp_flags;
		enum eth_rx_cqe_type cqe_fp_type;
		u16 len, pad, queue;
		u8 *data;
		u32 rxhash;
		enum pkt_hash_types rxhash_type;

#ifdef BNX2X_STOP_ON_ERROR
		if (unlikely(bp->panic))
			return 0;
#endif

		bd_prod = RX_BD(bd_prod);
		bd_cons = RX_BD(bd_cons);

		/* A rmb() is required to ensure that the CQE is not read
		 * before it is written by the adapter DMA.  PCI ordering
		 * rules will make sure the other fields are written before
		 * the marker at the end of struct eth_fast_path_rx_cqe
		 * but without rmb() a weakly ordered processor can process
		 * stale data.  Without the barrier TPA state-machine might
		 * enter inconsistent state and kernel stack might be
		 * provided with incorrect packet description - these lead
		 * to various kernel crashed.
		 */
		rmb();

		cqe_fp_flags = cqe_fp->type_error_flags;
		cqe_fp_type = cqe_fp_flags & ETH_FAST_PATH_RX_CQE_TYPE;

		DP(NETIF_MSG_RX_STATUS,
		   "CQE type %x  err %x  status %x  queue %x  vlan %x  len %u\n",
		   CQE_TYPE(cqe_fp_flags),
		   cqe_fp_flags, cqe_fp->status_flags,
		   le32_to_cpu(cqe_fp->rss_hash_result),
		   le16_to_cpu(cqe_fp->vlan_tag),
		   le16_to_cpu(cqe_fp->pkt_len_or_gro_seg_len));

		/* is this a slowpath msg? */
		if (unlikely(CQE_TYPE_SLOW(cqe_fp_type))) {
			bnx2x_sp_event(fp, cqe);
			goto next_cqe;
		}

		rx_buf = &fp->rx_buf_ring[bd_cons];
		data = rx_buf->data;

		if (!CQE_TYPE_FAST(cqe_fp_type)) {
			struct bnx2x_agg_info *tpa_info;
			u16 frag_size, pages;
#ifdef BNX2X_STOP_ON_ERROR
			/* sanity check */
			if (fp->mode == TPA_MODE_DISABLED &&
			    (CQE_TYPE_START(cqe_fp_type) ||
			     CQE_TYPE_STOP(cqe_fp_type)))
				BNX2X_ERR("START/STOP packet while TPA disabled, type %x\n",
					  CQE_TYPE(cqe_fp_type));
#endif

			if (CQE_TYPE_START(cqe_fp_type)) {
				u16 queue = cqe_fp->queue_index;
				DP(NETIF_MSG_RX_STATUS,
				   "calling tpa_start on queue %d\n",
				   queue);

				bnx2x_tpa_start(fp, queue,
						bd_cons, bd_prod,
						cqe_fp);

				goto next_rx;
			}
			queue = cqe->end_agg_cqe.queue_index;
			tpa_info = &fp->tpa_info[queue];
			DP(NETIF_MSG_RX_STATUS,
			   "calling tpa_stop on queue %d\n",
			   queue);

			frag_size = le16_to_cpu(cqe->end_agg_cqe.pkt_len) -
				    tpa_info->len_on_bd;

			if (fp->mode == TPA_MODE_GRO)
				pages = (frag_size + tpa_info->full_page - 1) /
					 tpa_info->full_page;
			else
				pages = SGE_PAGE_ALIGN(frag_size) >>
					SGE_PAGE_SHIFT;

			bnx2x_tpa_stop(bp, fp, tpa_info, pages,
				       &cqe->end_agg_cqe, comp_ring_cons);
#ifdef BNX2X_STOP_ON_ERROR
			if (bp->panic)
				return 0;
#endif

			bnx2x_update_sge_prod(fp, pages, &cqe->end_agg_cqe);
			goto next_cqe;
		}
		/* non TPA */
		len = le16_to_cpu(cqe_fp->pkt_len_or_gro_seg_len);
		pad = cqe_fp->placement_offset;
		dma_sync_single_for_cpu(&bp->pdev->dev,
					dma_unmap_addr(rx_buf, mapping),
					pad + RX_COPY_THRESH,
					DMA_FROM_DEVICE);
		pad += NET_SKB_PAD;
		prefetch(data + pad); /* speedup eth_type_trans() */
		/* is this an error packet? */
		if (unlikely(cqe_fp_flags & ETH_RX_ERROR_FALGS)) {
			DP(NETIF_MSG_RX_ERR | NETIF_MSG_RX_STATUS,
			   "ERROR  flags %x  rx packet %u\n",
			   cqe_fp_flags, sw_comp_cons);
			bnx2x_fp_qstats(bp, fp)->rx_err_discard_pkt++;
			goto reuse_rx;
		}

		/* Since we don't have a jumbo ring
		 * copy small packets if mtu > 1500
		 */
		if ((bp->dev->mtu > ETH_MAX_PACKET_SIZE) &&
		    (len <= RX_COPY_THRESH)) {
			skb = napi_alloc_skb(&fp->napi, len);
			if (skb == NULL) {
				DP(NETIF_MSG_RX_ERR | NETIF_MSG_RX_STATUS,
				   "ERROR  packet dropped because of alloc failure\n");
				bnx2x_fp_qstats(bp, fp)->rx_skb_alloc_failed++;
				goto reuse_rx;
			}
			memcpy(skb->data, data + pad, len);
			bnx2x_reuse_rx_data(fp, bd_cons, bd_prod);
		} else {
			if (likely(bnx2x_alloc_rx_data(bp, fp, bd_prod,
						       GFP_ATOMIC) == 0)) {
				dma_unmap_single(&bp->pdev->dev,
						 dma_unmap_addr(rx_buf, mapping),
						 fp->rx_buf_size,
						 DMA_FROM_DEVICE);
				skb = build_skb(data, fp->rx_frag_size);
				if (unlikely(!skb)) {
					bnx2x_frag_free(fp, data);
					bnx2x_fp_qstats(bp, fp)->
							rx_skb_alloc_failed++;
					goto next_rx;
				}
				skb_reserve(skb, pad);
			} else {
				DP(NETIF_MSG_RX_ERR | NETIF_MSG_RX_STATUS,
				   "ERROR  packet dropped because of alloc failure\n");
				bnx2x_fp_qstats(bp, fp)->rx_skb_alloc_failed++;
reuse_rx:
				bnx2x_reuse_rx_data(fp, bd_cons, bd_prod);
				goto next_rx;
			}
		}

		skb_put(skb, len);
		skb->protocol = eth_type_trans(skb, bp->dev);

		/* Set Toeplitz hash for a none-LRO skb */
		rxhash = bnx2x_get_rxhash(bp, cqe_fp, &rxhash_type);
		skb_set_hash(skb, rxhash, rxhash_type);

		skb_checksum_none_assert(skb);

		if (bp->dev->features & NETIF_F_RXCSUM)
			bnx2x_csum_validate(skb, cqe, fp,
					    bnx2x_fp_qstats(bp, fp));

		skb_record_rx_queue(skb, fp->rx_queue);

		/* Check if this packet was timestamped */
		if (unlikely(cqe->fast_path_cqe.type_error_flags &
			     (1 << ETH_FAST_PATH_RX_CQE_PTP_PKT_SHIFT)))
			bnx2x_set_rx_ts(bp, skb);

		if (le16_to_cpu(cqe_fp->pars_flags.flags) &
		    PARSING_FLAGS_VLAN)
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       le16_to_cpu(cqe_fp->vlan_tag));

		napi_gro_receive(&fp->napi, skb);
next_rx:
		rx_buf->data = NULL;

		bd_cons = NEXT_RX_IDX(bd_cons);
		bd_prod = NEXT_RX_IDX(bd_prod);
		bd_prod_fw = NEXT_RX_IDX(bd_prod_fw);
		rx_pkt++;
next_cqe:
		sw_comp_prod = NEXT_RCQ_IDX(sw_comp_prod);
		sw_comp_cons = NEXT_RCQ_IDX(sw_comp_cons);

		/* mark CQE as free */
		BNX2X_SEED_CQE(cqe_fp);

		if (rx_pkt == budget)
			break;

		comp_ring_cons = RCQ_BD(sw_comp_cons);
		cqe = &fp->rx_comp_ring[comp_ring_cons];
		cqe_fp = &cqe->fast_path_cqe;
	} /* while */

	fp->rx_bd_cons = bd_cons;
	fp->rx_bd_prod = bd_prod_fw;
	fp->rx_comp_cons = sw_comp_cons;
	fp->rx_comp_prod = sw_comp_prod;

	/* Update producers */
	bnx2x_update_rx_prod(bp, fp, bd_prod_fw, sw_comp_prod,
			     fp->rx_sge_prod);

	return rx_pkt;
}