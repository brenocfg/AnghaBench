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
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct udphdr {int dummy; } ;
struct sk_buff {scalar_t__ len; scalar_t__ ip_summed; } ;
struct bnad {TYPE_1__* netdev; int /*<<< orphan*/  run_flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  frame_length; void* flags; void* l4_hdr_size_n_offset; void* lso_mss; void* opcode; void* vlan_tag; } ;
struct TYPE_9__ {TYPE_2__ wi; } ;
struct bna_txq_entry {TYPE_3__ hdr; } ;
struct bna_tcb {int priority; } ;
typedef  void* __be16 ;
struct TYPE_12__ {scalar_t__ protocol; } ;
struct TYPE_11__ {scalar_t__ nexthdr; } ;
struct TYPE_10__ {int gso_size; } ;
struct TYPE_7__ {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RF_CEE_RUNNING ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 int BNA_TXQ_WI_CF_INS_PRIO ; 
 int BNA_TXQ_WI_CF_INS_VLAN ; 
 int BNA_TXQ_WI_CF_IP_CKSUM ; 
 int BNA_TXQ_WI_CF_TCP_CKSUM ; 
 int BNA_TXQ_WI_CF_UDP_CKSUM ; 
 int BNA_TXQ_WI_L4_HDR_N_OFFSET (int,scalar_t__) ; 
 int BNA_TXQ_WI_SEND ; 
 int BNA_TXQ_WI_SEND_LSO ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int EINVAL ; 
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 int VLAN_PRIO_SHIFT ; 
 scalar_t__ bnad_tso_prepare (struct bnad*,struct sk_buff*) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 void* htons (int) ; 
 TYPE_6__* ip_hdr (struct sk_buff*) ; 
 TYPE_5__* ipv6_hdr (struct sk_buff*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  tcpcsum_offload ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_skb_csum_err ; 
 int /*<<< orphan*/  tx_skb_mss_too_long ; 
 int /*<<< orphan*/  tx_skb_non_tso_too_long ; 
 int /*<<< orphan*/  tx_skb_tcp_hdr ; 
 int /*<<< orphan*/  tx_skb_tso_prepare ; 
 int /*<<< orphan*/  tx_skb_tso_too_short ; 
 int /*<<< orphan*/  tx_skb_udp_hdr ; 
 int /*<<< orphan*/  udpcsum_offload ; 
 scalar_t__ unlikely (int) ; 
 void* vlan_get_protocol (struct sk_buff*) ; 

__attribute__((used)) static int
bnad_txq_wi_prepare(struct bnad *bnad, struct bna_tcb *tcb,
		    struct sk_buff *skb, struct bna_txq_entry *txqent)
{
	u16 flags = 0;
	u32 gso_size;
	u16 vlan_tag = 0;

	if (skb_vlan_tag_present(skb)) {
		vlan_tag = (u16)skb_vlan_tag_get(skb);
		flags |= (BNA_TXQ_WI_CF_INS_PRIO | BNA_TXQ_WI_CF_INS_VLAN);
	}
	if (test_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags)) {
		vlan_tag = ((tcb->priority & 0x7) << VLAN_PRIO_SHIFT)
				| (vlan_tag & 0x1fff);
		flags |= (BNA_TXQ_WI_CF_INS_PRIO | BNA_TXQ_WI_CF_INS_VLAN);
	}
	txqent->hdr.wi.vlan_tag = htons(vlan_tag);

	if (skb_is_gso(skb)) {
		gso_size = skb_shinfo(skb)->gso_size;
		if (unlikely(gso_size > bnad->netdev->mtu)) {
			BNAD_UPDATE_CTR(bnad, tx_skb_mss_too_long);
			return -EINVAL;
		}
		if (unlikely((gso_size + skb_transport_offset(skb) +
			      tcp_hdrlen(skb)) >= skb->len)) {
			txqent->hdr.wi.opcode = htons(BNA_TXQ_WI_SEND);
			txqent->hdr.wi.lso_mss = 0;
			BNAD_UPDATE_CTR(bnad, tx_skb_tso_too_short);
		} else {
			txqent->hdr.wi.opcode = htons(BNA_TXQ_WI_SEND_LSO);
			txqent->hdr.wi.lso_mss = htons(gso_size);
		}

		if (bnad_tso_prepare(bnad, skb)) {
			BNAD_UPDATE_CTR(bnad, tx_skb_tso_prepare);
			return -EINVAL;
		}

		flags |= (BNA_TXQ_WI_CF_IP_CKSUM | BNA_TXQ_WI_CF_TCP_CKSUM);
		txqent->hdr.wi.l4_hdr_size_n_offset =
			htons(BNA_TXQ_WI_L4_HDR_N_OFFSET(
			tcp_hdrlen(skb) >> 2, skb_transport_offset(skb)));
	} else  {
		txqent->hdr.wi.opcode =	htons(BNA_TXQ_WI_SEND);
		txqent->hdr.wi.lso_mss = 0;

		if (unlikely(skb->len > (bnad->netdev->mtu + VLAN_ETH_HLEN))) {
			BNAD_UPDATE_CTR(bnad, tx_skb_non_tso_too_long);
			return -EINVAL;
		}

		if (skb->ip_summed == CHECKSUM_PARTIAL) {
			__be16 net_proto = vlan_get_protocol(skb);
			u8 proto = 0;

			if (net_proto == htons(ETH_P_IP))
				proto = ip_hdr(skb)->protocol;
#ifdef NETIF_F_IPV6_CSUM
			else if (net_proto == htons(ETH_P_IPV6)) {
				/* nexthdr may not be TCP immediately. */
				proto = ipv6_hdr(skb)->nexthdr;
			}
#endif
			if (proto == IPPROTO_TCP) {
				flags |= BNA_TXQ_WI_CF_TCP_CKSUM;
				txqent->hdr.wi.l4_hdr_size_n_offset =
					htons(BNA_TXQ_WI_L4_HDR_N_OFFSET
					      (0, skb_transport_offset(skb)));

				BNAD_UPDATE_CTR(bnad, tcpcsum_offload);

				if (unlikely(skb_headlen(skb) <
					    skb_transport_offset(skb) +
				    tcp_hdrlen(skb))) {
					BNAD_UPDATE_CTR(bnad, tx_skb_tcp_hdr);
					return -EINVAL;
				}
			} else if (proto == IPPROTO_UDP) {
				flags |= BNA_TXQ_WI_CF_UDP_CKSUM;
				txqent->hdr.wi.l4_hdr_size_n_offset =
					htons(BNA_TXQ_WI_L4_HDR_N_OFFSET
					      (0, skb_transport_offset(skb)));

				BNAD_UPDATE_CTR(bnad, udpcsum_offload);
				if (unlikely(skb_headlen(skb) <
					    skb_transport_offset(skb) +
				    sizeof(struct udphdr))) {
					BNAD_UPDATE_CTR(bnad, tx_skb_udp_hdr);
					return -EINVAL;
				}
			} else {

				BNAD_UPDATE_CTR(bnad, tx_skb_csum_err);
				return -EINVAL;
			}
		} else
			txqent->hdr.wi.l4_hdr_size_n_offset = 0;
	}

	txqent->hdr.wi.flags = htons(flags);
	txqent->hdr.wi.frame_length = htonl(skb->len);

	return 0;
}