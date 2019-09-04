#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct bnxt_tpa_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct sk_buff *bnxt_gro_func_5730x(struct bnxt_tpa_info *tpa_info,
					   int payload_off, int tcp_ts,
					   struct sk_buff *skb)
{
#ifdef CONFIG_INET
	struct tcphdr *th;
	int len, nw_off, tcp_opt_len = 0;

	if (tcp_ts)
		tcp_opt_len = 12;

	if (tpa_info->gso_type == SKB_GSO_TCPV4) {
		struct iphdr *iph;

		nw_off = payload_off - BNXT_IPV4_HDR_SIZE - tcp_opt_len -
			 ETH_HLEN;
		skb_set_network_header(skb, nw_off);
		iph = ip_hdr(skb);
		skb_set_transport_header(skb, nw_off + sizeof(struct iphdr));
		len = skb->len - skb_transport_offset(skb);
		th = tcp_hdr(skb);
		th->check = ~tcp_v4_check(len, iph->saddr, iph->daddr, 0);
	} else if (tpa_info->gso_type == SKB_GSO_TCPV6) {
		struct ipv6hdr *iph;

		nw_off = payload_off - BNXT_IPV6_HDR_SIZE - tcp_opt_len -
			 ETH_HLEN;
		skb_set_network_header(skb, nw_off);
		iph = ipv6_hdr(skb);
		skb_set_transport_header(skb, nw_off + sizeof(struct ipv6hdr));
		len = skb->len - skb_transport_offset(skb);
		th = tcp_hdr(skb);
		th->check = ~tcp_v6_check(len, &iph->saddr, &iph->daddr, 0);
	} else {
		dev_kfree_skb_any(skb);
		return NULL;
	}

	if (nw_off) { /* tunnel */
		struct udphdr *uh = NULL;

		if (skb->protocol == htons(ETH_P_IP)) {
			struct iphdr *iph = (struct iphdr *)skb->data;

			if (iph->protocol == IPPROTO_UDP)
				uh = (struct udphdr *)(iph + 1);
		} else {
			struct ipv6hdr *iph = (struct ipv6hdr *)skb->data;

			if (iph->nexthdr == IPPROTO_UDP)
				uh = (struct udphdr *)(iph + 1);
		}
		if (uh) {
			if (uh->check)
				skb_shinfo(skb)->gso_type |=
					SKB_GSO_UDP_TUNNEL_CSUM;
			else
				skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEL;
		}
	}
#endif
	return skb;
}