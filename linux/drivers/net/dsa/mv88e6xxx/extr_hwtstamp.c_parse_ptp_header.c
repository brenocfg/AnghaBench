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
struct sk_buff {unsigned int len; } ;

/* Variables and functions */
 unsigned int ETH_HLEN ; 
 int /*<<< orphan*/  IP6_HLEN ; 
 int /*<<< orphan*/  IPV4_HLEN (int /*<<< orphan*/ *) ; 
#define  PTP_CLASS_IPV4 130 
#define  PTP_CLASS_IPV6 129 
#define  PTP_CLASS_L2 128 
 unsigned int PTP_CLASS_PMASK ; 
 unsigned int PTP_CLASS_VLAN ; 
 unsigned int UDP_HLEN ; 
 scalar_t__ VLAN_HLEN ; 
 int /*<<< orphan*/ * skb_mac_header (struct sk_buff*) ; 

__attribute__((used)) static u8 *parse_ptp_header(struct sk_buff *skb, unsigned int type)
{
	u8 *data = skb_mac_header(skb);
	unsigned int offset = 0;

	if (type & PTP_CLASS_VLAN)
		offset += VLAN_HLEN;

	switch (type & PTP_CLASS_PMASK) {
	case PTP_CLASS_IPV4:
		offset += ETH_HLEN + IPV4_HLEN(data + offset) + UDP_HLEN;
		break;
	case PTP_CLASS_IPV6:
		offset += ETH_HLEN + IP6_HLEN + UDP_HLEN;
		break;
	case PTP_CLASS_L2:
		offset += ETH_HLEN;
		break;
	default:
		return NULL;
	}

	/* Ensure that the entire header is present in this packet. */
	if (skb->len + ETH_HLEN < offset + 34)
		return NULL;

	return data + offset;
}