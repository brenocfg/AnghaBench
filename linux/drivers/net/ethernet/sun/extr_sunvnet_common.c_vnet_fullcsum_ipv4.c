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
struct udphdr {void* check; } ;
struct tcphdr {void* check; } ;
struct sk_buff {scalar_t__ protocol; int csum_level; void* csum; scalar_t__ len; int /*<<< orphan*/  ip_summed; } ;
struct iphdr {scalar_t__ protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 void* csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 void* skb_checksum (struct sk_buff*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 struct tcphdr* tcp_hdr (struct sk_buff*) ; 
 struct udphdr* udp_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void vnet_fullcsum_ipv4(struct sk_buff *skb)
{
	struct iphdr *iph = ip_hdr(skb);
	int offset = skb_transport_offset(skb);

	if (skb->protocol != htons(ETH_P_IP))
		return;
	if (iph->protocol != IPPROTO_TCP &&
	    iph->protocol != IPPROTO_UDP)
		return;
	skb->ip_summed = CHECKSUM_NONE;
	skb->csum_level = 1;
	skb->csum = 0;
	if (iph->protocol == IPPROTO_TCP) {
		struct tcphdr *ptcp = tcp_hdr(skb);

		ptcp->check = 0;
		skb->csum = skb_checksum(skb, offset, skb->len - offset, 0);
		ptcp->check = csum_tcpudp_magic(iph->saddr, iph->daddr,
						skb->len - offset, IPPROTO_TCP,
						skb->csum);
	} else if (iph->protocol == IPPROTO_UDP) {
		struct udphdr *pudp = udp_hdr(skb);

		pudp->check = 0;
		skb->csum = skb_checksum(skb, offset, skb->len - offset, 0);
		pudp->check = csum_tcpudp_magic(iph->saddr, iph->daddr,
						skb->len - offset, IPPROTO_UDP,
						skb->csum);
	}
}