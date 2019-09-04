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
typedef  void* u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ protocol; scalar_t__ len; } ;
struct ipv6hdr {scalar_t__ nexthdr; } ;
struct iphdr {scalar_t__ protocol; } ;
struct hnae_ring {size_t next_to_use; TYPE_2__* q; struct hnae_desc_cb* desc_cb; struct hnae_desc* desc; } ;
struct hnae_desc_cb {int length; int type; int /*<<< orphan*/  dma; void* priv; } ;
struct TYPE_7__ {void* ra_ri_cs_fe_vld; void* bn_pid; void* paylen; void* l4_len; void* mss; void* tse_vlan_snap_v6_sctp_nth; void* ip_offset; void* send_size; } ;
struct hnae_desc {TYPE_3__ tx; int /*<<< orphan*/  addr; } ;
typedef  enum hns_desc_type { ____Placeholder_hns_desc_type } hns_desc_type ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  scalar_t__ __be16 ;
struct TYPE_8__ {scalar_t__ gso_size; } ;
struct TYPE_6__ {TYPE_1__* handle; } ;
struct TYPE_5__ {int dport_id; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int DESC_TYPE_SKB ; 
 void* ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  HNSV2_TXD_BUFNUM_M ; 
 int /*<<< orphan*/  HNSV2_TXD_FE_B ; 
 int /*<<< orphan*/  HNSV2_TXD_IPV6_B ; 
 int /*<<< orphan*/  HNSV2_TXD_L3CS_B ; 
 int /*<<< orphan*/  HNSV2_TXD_L4CS_B ; 
 int /*<<< orphan*/  HNSV2_TXD_PORTID_M ; 
 int /*<<< orphan*/  HNSV2_TXD_PORTID_S ; 
 int /*<<< orphan*/  HNSV2_TXD_TSE_B ; 
 int /*<<< orphan*/  HNSV2_TXD_VLD_B ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ SKB_TMP_LEN (struct sk_buff*) ; 
 scalar_t__ VLAN_HLEN ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hnae_set_bit (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hnae_set_field (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 struct ipv6hdr* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  next_to_use ; 
 int /*<<< orphan*/  ring_ptr_move_fw (struct hnae_ring*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_is_gso_v6 (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_mac_len (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 void* tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static void fill_v2_desc_hw(struct hnae_ring *ring, void *priv, int size,
			    int send_sz, dma_addr_t dma, int frag_end,
			    int buf_num, enum hns_desc_type type, int mtu)
{
	struct hnae_desc *desc = &ring->desc[ring->next_to_use];
	struct hnae_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_use];
	struct iphdr *iphdr;
	struct ipv6hdr *ipv6hdr;
	struct sk_buff *skb;
	__be16 protocol;
	u8 bn_pid = 0;
	u8 rrcfv = 0;
	u8 ip_offset = 0;
	u8 tvsvsn = 0;
	u16 mss = 0;
	u8 l4_len = 0;
	u16 paylen = 0;

	desc_cb->priv = priv;
	desc_cb->length = size;
	desc_cb->dma = dma;
	desc_cb->type = type;

	desc->addr = cpu_to_le64(dma);
	desc->tx.send_size = cpu_to_le16((u16)send_sz);

	/* config bd buffer end */
	hnae_set_bit(rrcfv, HNSV2_TXD_VLD_B, 1);
	hnae_set_field(bn_pid, HNSV2_TXD_BUFNUM_M, 0, buf_num - 1);

	/* fill port_id in the tx bd for sending management pkts */
	hnae_set_field(bn_pid, HNSV2_TXD_PORTID_M,
		       HNSV2_TXD_PORTID_S, ring->q->handle->dport_id);

	if (type == DESC_TYPE_SKB) {
		skb = (struct sk_buff *)priv;

		if (skb->ip_summed == CHECKSUM_PARTIAL) {
			skb_reset_mac_len(skb);
			protocol = skb->protocol;
			ip_offset = ETH_HLEN;

			if (protocol == htons(ETH_P_8021Q)) {
				ip_offset += VLAN_HLEN;
				protocol = vlan_get_protocol(skb);
				skb->protocol = protocol;
			}

			if (skb->protocol == htons(ETH_P_IP)) {
				iphdr = ip_hdr(skb);
				hnae_set_bit(rrcfv, HNSV2_TXD_L3CS_B, 1);
				hnae_set_bit(rrcfv, HNSV2_TXD_L4CS_B, 1);

				/* check for tcp/udp header */
				if (iphdr->protocol == IPPROTO_TCP &&
				    skb_is_gso(skb)) {
					hnae_set_bit(tvsvsn,
						     HNSV2_TXD_TSE_B, 1);
					l4_len = tcp_hdrlen(skb);
					mss = skb_shinfo(skb)->gso_size;
					paylen = skb->len - SKB_TMP_LEN(skb);
				}
			} else if (skb->protocol == htons(ETH_P_IPV6)) {
				hnae_set_bit(tvsvsn, HNSV2_TXD_IPV6_B, 1);
				ipv6hdr = ipv6_hdr(skb);
				hnae_set_bit(rrcfv, HNSV2_TXD_L4CS_B, 1);

				/* check for tcp/udp header */
				if (ipv6hdr->nexthdr == IPPROTO_TCP &&
				    skb_is_gso(skb) && skb_is_gso_v6(skb)) {
					hnae_set_bit(tvsvsn,
						     HNSV2_TXD_TSE_B, 1);
					l4_len = tcp_hdrlen(skb);
					mss = skb_shinfo(skb)->gso_size;
					paylen = skb->len - SKB_TMP_LEN(skb);
				}
			}
			desc->tx.ip_offset = ip_offset;
			desc->tx.tse_vlan_snap_v6_sctp_nth = tvsvsn;
			desc->tx.mss = cpu_to_le16(mss);
			desc->tx.l4_len = l4_len;
			desc->tx.paylen = cpu_to_le16(paylen);
		}
	}

	hnae_set_bit(rrcfv, HNSV2_TXD_FE_B, frag_end);

	desc->tx.bn_pid = bn_pid;
	desc->tx.ra_ri_cs_fe_vld = rrcfv;

	ring_ptr_move_fw(ring, next_to_use);
}