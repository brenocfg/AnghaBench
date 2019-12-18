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
struct sk_buff {scalar_t__ ip_summed; scalar_t__ protocol; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct aq_ring_s {unsigned int sw_tail; struct aq_ring_buff_s* buff_ring; } ;
struct aq_ring_buff_s {unsigned int flags; unsigned int is_gso; int eop_index; unsigned int is_ipv6; unsigned int is_vlan; unsigned int len; unsigned int is_sop; unsigned int is_mapped; unsigned int is_ip_cso; unsigned int is_tcp_cso; unsigned int is_udp_cso; unsigned int is_eop; scalar_t__ pa; struct sk_buff* skb; int /*<<< orphan*/  len_pkt; int /*<<< orphan*/  vlan_tx_tag; int /*<<< orphan*/  len_l4; int /*<<< orphan*/  len_l3; int /*<<< orphan*/  len_l2; int /*<<< orphan*/  mss; } ;
struct TYPE_5__ {scalar_t__ is_vlan_tx_insert; } ;
struct aq_nic_s {TYPE_1__ aq_nic_cfg; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_8__ {int version; scalar_t__ protocol; } ;
struct TYPE_7__ {scalar_t__ nexthdr; } ;
struct TYPE_6__ {unsigned int nr_frags; int /*<<< orphan*/ * frags; int /*<<< orphan*/  gso_size; } ;

/* Variables and functions */
 unsigned int AQ_CFG_TX_FRAME_MAX ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ NEXTHDR_TCP ; 
 scalar_t__ NEXTHDR_UDP ; 
 int /*<<< orphan*/  aq_nic_get_dev (struct aq_nic_s*) ; 
 unsigned int aq_ring_next_dx (struct aq_ring_s*,unsigned int) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int dma_mapping_error (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_hdrlen (struct sk_buff*) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int skb_frag_size (int /*<<< orphan*/ *) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 unsigned int skb_is_gso (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static unsigned int aq_nic_map_skb(struct aq_nic_s *self,
				   struct sk_buff *skb,
				   struct aq_ring_s *ring)
{
	unsigned int ret = 0U;
	unsigned int nr_frags = skb_shinfo(skb)->nr_frags;
	unsigned int frag_count = 0U;
	unsigned int dx = ring->sw_tail;
	struct aq_ring_buff_s *first = NULL;
	struct aq_ring_buff_s *dx_buff = &ring->buff_ring[dx];
	bool need_context_tag = false;

	dx_buff->flags = 0U;

	if (unlikely(skb_is_gso(skb))) {
		dx_buff->mss = skb_shinfo(skb)->gso_size;
		dx_buff->is_gso = 1U;
		dx_buff->len_pkt = skb->len;
		dx_buff->len_l2 = ETH_HLEN;
		dx_buff->len_l3 = ip_hdrlen(skb);
		dx_buff->len_l4 = tcp_hdrlen(skb);
		dx_buff->eop_index = 0xffffU;
		dx_buff->is_ipv6 =
			(ip_hdr(skb)->version == 6) ? 1U : 0U;
		need_context_tag = true;
	}

	if (self->aq_nic_cfg.is_vlan_tx_insert && skb_vlan_tag_present(skb)) {
		dx_buff->vlan_tx_tag = skb_vlan_tag_get(skb);
		dx_buff->len_pkt = skb->len;
		dx_buff->is_vlan = 1U;
		need_context_tag = true;
	}

	if (need_context_tag) {
		dx = aq_ring_next_dx(ring, dx);
		dx_buff = &ring->buff_ring[dx];
		dx_buff->flags = 0U;
		++ret;
	}

	dx_buff->len = skb_headlen(skb);
	dx_buff->pa = dma_map_single(aq_nic_get_dev(self),
				     skb->data,
				     dx_buff->len,
				     DMA_TO_DEVICE);

	if (unlikely(dma_mapping_error(aq_nic_get_dev(self), dx_buff->pa)))
		goto exit;

	first = dx_buff;
	dx_buff->len_pkt = skb->len;
	dx_buff->is_sop = 1U;
	dx_buff->is_mapped = 1U;
	++ret;

	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		dx_buff->is_ip_cso = (htons(ETH_P_IP) == skb->protocol) ?
			1U : 0U;

		if (ip_hdr(skb)->version == 4) {
			dx_buff->is_tcp_cso =
				(ip_hdr(skb)->protocol == IPPROTO_TCP) ?
					1U : 0U;
			dx_buff->is_udp_cso =
				(ip_hdr(skb)->protocol == IPPROTO_UDP) ?
					1U : 0U;
		} else if (ip_hdr(skb)->version == 6) {
			dx_buff->is_tcp_cso =
				(ipv6_hdr(skb)->nexthdr == NEXTHDR_TCP) ?
					1U : 0U;
			dx_buff->is_udp_cso =
				(ipv6_hdr(skb)->nexthdr == NEXTHDR_UDP) ?
					1U : 0U;
		}
	}

	for (; nr_frags--; ++frag_count) {
		unsigned int frag_len = 0U;
		unsigned int buff_offset = 0U;
		unsigned int buff_size = 0U;
		dma_addr_t frag_pa;
		skb_frag_t *frag = &skb_shinfo(skb)->frags[frag_count];

		frag_len = skb_frag_size(frag);

		while (frag_len) {
			if (frag_len > AQ_CFG_TX_FRAME_MAX)
				buff_size = AQ_CFG_TX_FRAME_MAX;
			else
				buff_size = frag_len;

			frag_pa = skb_frag_dma_map(aq_nic_get_dev(self),
						   frag,
						   buff_offset,
						   buff_size,
						   DMA_TO_DEVICE);

			if (unlikely(dma_mapping_error(aq_nic_get_dev(self),
						       frag_pa)))
				goto mapping_error;

			dx = aq_ring_next_dx(ring, dx);
			dx_buff = &ring->buff_ring[dx];

			dx_buff->flags = 0U;
			dx_buff->len = buff_size;
			dx_buff->pa = frag_pa;
			dx_buff->is_mapped = 1U;
			dx_buff->eop_index = 0xffffU;

			frag_len -= buff_size;
			buff_offset += buff_size;

			++ret;
		}
	}

	first->eop_index = dx;
	dx_buff->is_eop = 1U;
	dx_buff->skb = skb;
	goto exit;

mapping_error:
	for (dx = ring->sw_tail;
	     ret > 0;
	     --ret, dx = aq_ring_next_dx(ring, dx)) {
		dx_buff = &ring->buff_ring[dx];

		if (!dx_buff->is_gso && !dx_buff->is_vlan && dx_buff->pa) {
			if (unlikely(dx_buff->is_sop)) {
				dma_unmap_single(aq_nic_get_dev(self),
						 dx_buff->pa,
						 dx_buff->len,
						 DMA_TO_DEVICE);
			} else {
				dma_unmap_page(aq_nic_get_dev(self),
					       dx_buff->pa,
					       dx_buff->len,
					       DMA_TO_DEVICE);
			}
		}
	}

exit:
	return ret;
}