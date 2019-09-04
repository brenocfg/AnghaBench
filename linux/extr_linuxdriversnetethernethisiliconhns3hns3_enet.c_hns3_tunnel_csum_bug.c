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
struct udphdr {scalar_t__ dest; } ;
struct tcphdr {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  encapsulation; } ;
struct gre_base_hdr {int dummy; } ;

/* Variables and functions */
 scalar_t__ htons (int) ; 
 int /*<<< orphan*/  skb_checksum_help (struct sk_buff*) ; 
 unsigned char* skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static bool hns3_tunnel_csum_bug(struct sk_buff *skb)
{
#define IANA_VXLAN_PORT	4789
	union {
		struct tcphdr *tcp;
		struct udphdr *udp;
		struct gre_base_hdr *gre;
		unsigned char *hdr;
	} l4;

	l4.hdr = skb_transport_header(skb);

	if (!(!skb->encapsulation && l4.udp->dest == htons(IANA_VXLAN_PORT)))
		return false;

	skb_checksum_help(skb);

	return true;
}