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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ protocol; int data; int /*<<< orphan*/  encapsulation; } ;
struct ipv6hdr {int version; int /*<<< orphan*/  nexthdr; } ;
struct iphdr {int version; int /*<<< orphan*/  protocol; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_skip_exthdr (struct sk_buff*,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* skb_inner_network_header (struct sk_buff*) ; 
 unsigned char* skb_inner_transport_header (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 
 unsigned char* skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static int hns3_get_l4_protocol(struct sk_buff *skb, u8 *ol4_proto,
				u8 *il4_proto)
{
	union {
		struct iphdr *v4;
		struct ipv6hdr *v6;
		unsigned char *hdr;
	} l3;
	unsigned char *l4_hdr;
	unsigned char *exthdr;
	u8 l4_proto_tmp;
	__be16 frag_off;

	/* find outer header point */
	l3.hdr = skb_network_header(skb);
	l4_hdr = skb_transport_header(skb);

	if (skb->protocol == htons(ETH_P_IPV6)) {
		exthdr = l3.hdr + sizeof(*l3.v6);
		l4_proto_tmp = l3.v6->nexthdr;
		if (l4_hdr != exthdr)
			ipv6_skip_exthdr(skb, exthdr - skb->data,
					 &l4_proto_tmp, &frag_off);
	} else if (skb->protocol == htons(ETH_P_IP)) {
		l4_proto_tmp = l3.v4->protocol;
	} else {
		return -EINVAL;
	}

	*ol4_proto = l4_proto_tmp;

	/* tunnel packet */
	if (!skb->encapsulation) {
		*il4_proto = 0;
		return 0;
	}

	/* find inner header point */
	l3.hdr = skb_inner_network_header(skb);
	l4_hdr = skb_inner_transport_header(skb);

	if (l3.v6->version == 6) {
		exthdr = l3.hdr + sizeof(*l3.v6);
		l4_proto_tmp = l3.v6->nexthdr;
		if (l4_hdr != exthdr)
			ipv6_skip_exthdr(skb, exthdr - skb->data,
					 &l4_proto_tmp, &frag_off);
	} else if (l3.v4->version == 4) {
		l4_proto_tmp = l3.v4->protocol;
	}

	*il4_proto = l4_proto_tmp;

	return 0;
}