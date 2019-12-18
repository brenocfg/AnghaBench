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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ ip_summed; } ;
struct ena_com_tx_meta {int /*<<< orphan*/  l3_hdr_offset; int /*<<< orphan*/  l3_hdr_len; scalar_t__ mss; scalar_t__ l4_hdr_len; } ;
struct ena_com_tx_ctx {int l4_csum_enable; int tso_enable; int l4_csum_partial; int df; int l3_csum_enable; int meta_valid; int /*<<< orphan*/  l4_proto; int /*<<< orphan*/  l3_proto; struct ena_com_tx_meta ena_meta; } ;
struct TYPE_8__ {int version; int frag_off; scalar_t__ protocol; } ;
struct TYPE_7__ {scalar_t__ nexthdr; } ;
struct TYPE_6__ {scalar_t__ gso_size; } ;
struct TYPE_5__ {scalar_t__ doff; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  ENA_ETH_IO_L3_PROTO_IPV4 ; 
 int /*<<< orphan*/  ENA_ETH_IO_L3_PROTO_IPV6 ; 
 int /*<<< orphan*/  ENA_ETH_IO_L4_PROTO_TCP ; 
 int /*<<< orphan*/  ENA_ETH_IO_L4_PROTO_UDP ; 
 scalar_t__ IPPROTO_TCP ; 
#define  IPVERSION 128 
 int /*<<< orphan*/  IP_DF ; 
 int htons (int /*<<< orphan*/ ) ; 
 TYPE_4__* ip_hdr (struct sk_buff*) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 

__attribute__((used)) static void ena_tx_csum(struct ena_com_tx_ctx *ena_tx_ctx, struct sk_buff *skb)
{
	u32 mss = skb_shinfo(skb)->gso_size;
	struct ena_com_tx_meta *ena_meta = &ena_tx_ctx->ena_meta;
	u8 l4_protocol = 0;

	if ((skb->ip_summed == CHECKSUM_PARTIAL) || mss) {
		ena_tx_ctx->l4_csum_enable = 1;
		if (mss) {
			ena_tx_ctx->tso_enable = 1;
			ena_meta->l4_hdr_len = tcp_hdr(skb)->doff;
			ena_tx_ctx->l4_csum_partial = 0;
		} else {
			ena_tx_ctx->tso_enable = 0;
			ena_meta->l4_hdr_len = 0;
			ena_tx_ctx->l4_csum_partial = 1;
		}

		switch (ip_hdr(skb)->version) {
		case IPVERSION:
			ena_tx_ctx->l3_proto = ENA_ETH_IO_L3_PROTO_IPV4;
			if (ip_hdr(skb)->frag_off & htons(IP_DF))
				ena_tx_ctx->df = 1;
			if (mss)
				ena_tx_ctx->l3_csum_enable = 1;
			l4_protocol = ip_hdr(skb)->protocol;
			break;
		case 6:
			ena_tx_ctx->l3_proto = ENA_ETH_IO_L3_PROTO_IPV6;
			l4_protocol = ipv6_hdr(skb)->nexthdr;
			break;
		default:
			break;
		}

		if (l4_protocol == IPPROTO_TCP)
			ena_tx_ctx->l4_proto = ENA_ETH_IO_L4_PROTO_TCP;
		else
			ena_tx_ctx->l4_proto = ENA_ETH_IO_L4_PROTO_UDP;

		ena_meta->mss = mss;
		ena_meta->l3_hdr_len = skb_network_header_len(skb);
		ena_meta->l3_hdr_offset = skb_network_offset(skb);
		ena_tx_ctx->meta_valid = 1;

	} else {
		ena_tx_ctx->meta_valid = 0;
	}
}