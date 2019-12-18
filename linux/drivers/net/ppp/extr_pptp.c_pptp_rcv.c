#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ pkt_type; scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ protocol; int flags; } ;
struct pptp_gre_header {int /*<<< orphan*/  call_id; TYPE_1__ gre_hd; } ;
struct pppox_sock {int dummy; } ;
struct iphdr {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int GRE_FLAGS ; 
 scalar_t__ GRE_IS_CSUM (int) ; 
 int /*<<< orphan*/  GRE_IS_KEY (int) ; 
 scalar_t__ GRE_IS_ROUTING (int) ; 
 scalar_t__ GRE_PROTO_PPP ; 
 int NET_RX_DROP ; 
 scalar_t__ PACKET_HOST ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct pppox_sock* lookup_chan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  sk_pppox (struct pppox_sock*) ; 
 int sk_receive_skb (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 

__attribute__((used)) static int pptp_rcv(struct sk_buff *skb)
{
	struct pppox_sock *po;
	struct pptp_gre_header *header;
	struct iphdr *iph;

	if (skb->pkt_type != PACKET_HOST)
		goto drop;

	if (!pskb_may_pull(skb, 12))
		goto drop;

	iph = ip_hdr(skb);

	header = (struct pptp_gre_header *)skb->data;

	if (header->gre_hd.protocol != GRE_PROTO_PPP || /* PPTP-GRE protocol for PPTP */
		GRE_IS_CSUM(header->gre_hd.flags) ||    /* flag CSUM should be clear */
		GRE_IS_ROUTING(header->gre_hd.flags) || /* flag ROUTING should be clear */
		!GRE_IS_KEY(header->gre_hd.flags) ||    /* flag KEY should be set */
		(header->gre_hd.flags & GRE_FLAGS))     /* flag Recursion Ctrl should be clear */
		/* if invalid, discard this packet */
		goto drop;

	po = lookup_chan(htons(header->call_id), iph->saddr);
	if (po) {
		skb_dst_drop(skb);
		nf_reset_ct(skb);
		return sk_receive_skb(sk_pppox(po), skb, 0);
	}
drop:
	kfree_skb(skb);
	return NET_RX_DROP;
}