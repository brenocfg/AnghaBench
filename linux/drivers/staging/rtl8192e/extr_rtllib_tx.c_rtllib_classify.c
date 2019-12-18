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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct iphdr {int tos; } ;
struct ethhdr {scalar_t__ h_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtllib_classify(struct sk_buff *skb, u8 bIsAmsdu)
{
	struct ethhdr *eth;
	struct iphdr *ip;

	eth = (struct ethhdr *)skb->data;
	if (eth->h_proto != htons(ETH_P_IP))
		return 0;

#ifdef VERBOSE_DEBUG
	print_hex_dump_bytes("rtllib_classify(): ", DUMP_PREFIX_NONE, skb->data,
			     skb->len);
#endif
	ip = ip_hdr(skb);
	switch (ip->tos & 0xfc) {
	case 0x20:
		return 2;
	case 0x40:
		return 1;
	case 0x60:
		return 3;
	case 0x80:
		return 4;
	case 0xa0:
		return 5;
	case 0xc0:
		return 6;
	case 0xe0:
		return 7;
	default:
		return 0;
	}
}