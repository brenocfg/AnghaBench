#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data; } ;
struct l2_fhdr {unsigned int l2_fhdr_pkt_len; int l2_fhdr_status; unsigned int l2_fhdr_ip_xsum; int /*<<< orphan*/  l2_fhdr_hash; int /*<<< orphan*/  l2_fhdr_vlan_tag; } ;
struct bnx2_sw_bd {int /*<<< orphan*/ * data; } ;
struct bnx2_rx_ring_info {scalar_t__ rx_cons; scalar_t__ rx_prod; scalar_t__ rx_pg_prod; int /*<<< orphan*/  rx_prod_bseq; int /*<<< orphan*/  rx_bseq_addr; int /*<<< orphan*/  rx_bidx_addr; int /*<<< orphan*/  rx_pg_bidx_addr; struct bnx2_sw_bd* rx_buf_ring; } ;
struct bnx2_napi {int /*<<< orphan*/  napi; struct bnx2_rx_ring_info rx_ring; } ;
struct bnx2 {unsigned int rx_jumbo_thresh; unsigned int rx_copy_thresh; int rx_mode; struct bnx2_napi* bnx2_napi; TYPE_2__* dev; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {unsigned int mtu; int features; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BNX2_EMAC_RX_MODE_KEEP_VLAN_TAG ; 
 scalar_t__ BNX2_NEXT_RX_BD (scalar_t__) ; 
 int BNX2_RX_COPY_THRESH ; 
 int BNX2_RX_OFFSET ; 
 scalar_t__ BNX2_RX_RING_IDX (scalar_t__) ; 
 int /*<<< orphan*/  BNX2_WR (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNX2_WR16 (struct bnx2*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 unsigned int ETH_HLEN ; 
 int ETH_P_8021AD ; 
 int ETH_P_8021Q ; 
 int L2_FHDR_ERRORS_ALIGNMENT ; 
 int L2_FHDR_ERRORS_BAD_CRC ; 
 int L2_FHDR_ERRORS_GIANT_FRAME ; 
 int L2_FHDR_ERRORS_PHY_DECODE ; 
 int L2_FHDR_ERRORS_TCP_XSUM ; 
 int L2_FHDR_ERRORS_TOO_SHORT ; 
 int L2_FHDR_ERRORS_UDP_XSUM ; 
 int L2_FHDR_STATUS_L2_VLAN_TAG ; 
 int L2_FHDR_STATUS_SPLIT ; 
 int L2_FHDR_STATUS_TCP_SEGMENT ; 
 int L2_FHDR_STATUS_UDP_DATAGRAM ; 
 int L2_FHDR_STATUS_USE_RXHASH ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_RXHASH ; 
 int PAGE_ALIGN (unsigned int) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2_get_hw_rx_cons (struct bnx2_napi*) ; 
 int /*<<< orphan*/  bnx2_reuse_rx_data (struct bnx2*,struct bnx2_rx_ring_info*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bnx2_reuse_rx_skb_pages (struct bnx2*,struct bnx2_rx_ring_info*,int /*<<< orphan*/ *,int) ; 
 struct sk_buff* bnx2_rx_skb (struct bnx2*,struct bnx2_rx_ring_info*,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct bnx2_sw_bd*,int /*<<< orphan*/ ) ; 
 scalar_t__ eth_type_trans (struct sk_buff*,TYPE_2__*) ; 
 struct l2_fhdr* get_l2_fhdr (int /*<<< orphan*/ *) ; 
 scalar_t__ htons (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mapping ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  prefetch (struct l2_fhdr*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
bnx2_rx_int(struct bnx2 *bp, struct bnx2_napi *bnapi, int budget)
{
	struct bnx2_rx_ring_info *rxr = &bnapi->rx_ring;
	u16 hw_cons, sw_cons, sw_ring_cons, sw_prod, sw_ring_prod;
	struct l2_fhdr *rx_hdr;
	int rx_pkt = 0, pg_ring_used = 0;

	if (budget <= 0)
		return rx_pkt;

	hw_cons = bnx2_get_hw_rx_cons(bnapi);
	sw_cons = rxr->rx_cons;
	sw_prod = rxr->rx_prod;

	/* Memory barrier necessary as speculative reads of the rx
	 * buffer can be ahead of the index in the status block
	 */
	rmb();
	while (sw_cons != hw_cons) {
		unsigned int len, hdr_len;
		u32 status;
		struct bnx2_sw_bd *rx_buf, *next_rx_buf;
		struct sk_buff *skb;
		dma_addr_t dma_addr;
		u8 *data;
		u16 next_ring_idx;

		sw_ring_cons = BNX2_RX_RING_IDX(sw_cons);
		sw_ring_prod = BNX2_RX_RING_IDX(sw_prod);

		rx_buf = &rxr->rx_buf_ring[sw_ring_cons];
		data = rx_buf->data;
		rx_buf->data = NULL;

		rx_hdr = get_l2_fhdr(data);
		prefetch(rx_hdr);

		dma_addr = dma_unmap_addr(rx_buf, mapping);

		dma_sync_single_for_cpu(&bp->pdev->dev, dma_addr,
			BNX2_RX_OFFSET + BNX2_RX_COPY_THRESH,
			PCI_DMA_FROMDEVICE);

		next_ring_idx = BNX2_RX_RING_IDX(BNX2_NEXT_RX_BD(sw_cons));
		next_rx_buf = &rxr->rx_buf_ring[next_ring_idx];
		prefetch(get_l2_fhdr(next_rx_buf->data));

		len = rx_hdr->l2_fhdr_pkt_len;
		status = rx_hdr->l2_fhdr_status;

		hdr_len = 0;
		if (status & L2_FHDR_STATUS_SPLIT) {
			hdr_len = rx_hdr->l2_fhdr_ip_xsum;
			pg_ring_used = 1;
		} else if (len > bp->rx_jumbo_thresh) {
			hdr_len = bp->rx_jumbo_thresh;
			pg_ring_used = 1;
		}

		if (unlikely(status & (L2_FHDR_ERRORS_BAD_CRC |
				       L2_FHDR_ERRORS_PHY_DECODE |
				       L2_FHDR_ERRORS_ALIGNMENT |
				       L2_FHDR_ERRORS_TOO_SHORT |
				       L2_FHDR_ERRORS_GIANT_FRAME))) {

			bnx2_reuse_rx_data(bp, rxr, data, sw_ring_cons,
					  sw_ring_prod);
			if (pg_ring_used) {
				int pages;

				pages = PAGE_ALIGN(len - hdr_len) >> PAGE_SHIFT;

				bnx2_reuse_rx_skb_pages(bp, rxr, NULL, pages);
			}
			goto next_rx;
		}

		len -= 4;

		if (len <= bp->rx_copy_thresh) {
			skb = netdev_alloc_skb(bp->dev, len + 6);
			if (!skb) {
				bnx2_reuse_rx_data(bp, rxr, data, sw_ring_cons,
						  sw_ring_prod);
				goto next_rx;
			}

			/* aligned copy */
			memcpy(skb->data,
			       (u8 *)rx_hdr + BNX2_RX_OFFSET - 6,
			       len + 6);
			skb_reserve(skb, 6);
			skb_put(skb, len);

			bnx2_reuse_rx_data(bp, rxr, data,
				sw_ring_cons, sw_ring_prod);

		} else {
			skb = bnx2_rx_skb(bp, rxr, data, len, hdr_len, dma_addr,
					  (sw_ring_cons << 16) | sw_ring_prod);
			if (!skb)
				goto next_rx;
		}
		if ((status & L2_FHDR_STATUS_L2_VLAN_TAG) &&
		    !(bp->rx_mode & BNX2_EMAC_RX_MODE_KEEP_VLAN_TAG))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), rx_hdr->l2_fhdr_vlan_tag);

		skb->protocol = eth_type_trans(skb, bp->dev);

		if (len > (bp->dev->mtu + ETH_HLEN) &&
		    skb->protocol != htons(0x8100) &&
		    skb->protocol != htons(ETH_P_8021AD)) {

			dev_kfree_skb(skb);
			goto next_rx;

		}

		skb_checksum_none_assert(skb);
		if ((bp->dev->features & NETIF_F_RXCSUM) &&
			(status & (L2_FHDR_STATUS_TCP_SEGMENT |
			L2_FHDR_STATUS_UDP_DATAGRAM))) {

			if (likely((status & (L2_FHDR_ERRORS_TCP_XSUM |
					      L2_FHDR_ERRORS_UDP_XSUM)) == 0))
				skb->ip_summed = CHECKSUM_UNNECESSARY;
		}
		if ((bp->dev->features & NETIF_F_RXHASH) &&
		    ((status & L2_FHDR_STATUS_USE_RXHASH) ==
		     L2_FHDR_STATUS_USE_RXHASH))
			skb_set_hash(skb, rx_hdr->l2_fhdr_hash,
				     PKT_HASH_TYPE_L3);

		skb_record_rx_queue(skb, bnapi - &bp->bnx2_napi[0]);
		napi_gro_receive(&bnapi->napi, skb);
		rx_pkt++;

next_rx:
		sw_cons = BNX2_NEXT_RX_BD(sw_cons);
		sw_prod = BNX2_NEXT_RX_BD(sw_prod);

		if (rx_pkt == budget)
			break;

		/* Refresh hw_cons to see if there is new work */
		if (sw_cons == hw_cons) {
			hw_cons = bnx2_get_hw_rx_cons(bnapi);
			rmb();
		}
	}
	rxr->rx_cons = sw_cons;
	rxr->rx_prod = sw_prod;

	if (pg_ring_used)
		BNX2_WR16(bp, rxr->rx_pg_bidx_addr, rxr->rx_pg_prod);

	BNX2_WR16(bp, rxr->rx_bidx_addr, sw_prod);

	BNX2_WR(bp, rxr->rx_bseq_addr, rxr->rx_prod_bseq);

	return rx_pkt;

}