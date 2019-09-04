#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct vlan_ethhdr {int dummy; } ;
struct udphdr {int dummy; } ;
struct sk_buff {scalar_t__ protocol; int /*<<< orphan*/  dev; } ;
struct ipv6hdr {int dummy; } ;
struct ethhdr {int dummy; } ;
struct TYPE_4__ {int ihl; scalar_t__ protocol; } ;
struct TYPE_3__ {scalar_t__ nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_ARP ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int arp_hdr_len (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int* skb_mac_header (struct sk_buff*) ; 
 int* skb_network_header (struct sk_buff*) ; 
 int* skb_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tagged (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 

__attribute__((used)) static int build_hdr_data(u8 hdr_field, struct sk_buff *skb,
			  int *hdr_len, u8 *hdr_data)
{
	int len = 0;
	u8 *hdr;

	if (skb_vlan_tagged(skb) && !skb_vlan_tag_present(skb))
		hdr_len[0] = sizeof(struct vlan_ethhdr);
	else
		hdr_len[0] = sizeof(struct ethhdr);

	if (skb->protocol == htons(ETH_P_IP)) {
		hdr_len[1] = ip_hdr(skb)->ihl * 4;
		if (ip_hdr(skb)->protocol == IPPROTO_TCP)
			hdr_len[2] = tcp_hdrlen(skb);
		else if (ip_hdr(skb)->protocol == IPPROTO_UDP)
			hdr_len[2] = sizeof(struct udphdr);
	} else if (skb->protocol == htons(ETH_P_IPV6)) {
		hdr_len[1] = sizeof(struct ipv6hdr);
		if (ipv6_hdr(skb)->nexthdr == IPPROTO_TCP)
			hdr_len[2] = tcp_hdrlen(skb);
		else if (ipv6_hdr(skb)->nexthdr == IPPROTO_UDP)
			hdr_len[2] = sizeof(struct udphdr);
	} else if (skb->protocol == htons(ETH_P_ARP)) {
		hdr_len[1] = arp_hdr_len(skb->dev);
		hdr_len[2] = 0;
	}

	memset(hdr_data, 0, 120);
	if ((hdr_field >> 6) & 1) {
		hdr = skb_mac_header(skb);
		memcpy(hdr_data, hdr, hdr_len[0]);
		len += hdr_len[0];
	}

	if ((hdr_field >> 5) & 1) {
		hdr = skb_network_header(skb);
		memcpy(hdr_data + len, hdr, hdr_len[1]);
		len += hdr_len[1];
	}

	if ((hdr_field >> 4) & 1) {
		hdr = skb_transport_header(skb);
		memcpy(hdr_data + len, hdr, hdr_len[2]);
		len += hdr_len[2];
	}
	return len;
}