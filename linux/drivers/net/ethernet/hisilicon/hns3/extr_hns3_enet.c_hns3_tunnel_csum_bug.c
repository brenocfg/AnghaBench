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
union l4_hdr_info {TYPE_1__* udp; int /*<<< orphan*/  hdr; } ;
struct sk_buff {int /*<<< orphan*/  encapsulation; } ;
struct TYPE_2__ {scalar_t__ dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  IANA_VXLAN_UDP_PORT ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_help (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_transport_header (struct sk_buff*) ; 

__attribute__((used)) static bool hns3_tunnel_csum_bug(struct sk_buff *skb)
{
	union l4_hdr_info l4;

	l4.hdr = skb_transport_header(skb);

	if (!(!skb->encapsulation &&
	      l4.udp->dest == htons(IANA_VXLAN_UDP_PORT)))
		return false;

	skb_checksum_help(skb);

	return true;
}