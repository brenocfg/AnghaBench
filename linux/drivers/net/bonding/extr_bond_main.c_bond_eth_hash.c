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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct ethhdr {int* h_dest; int* h_source; int h_proto; } ;
typedef  int /*<<< orphan*/  hdr_tmp ;

/* Variables and functions */
 struct ethhdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct ethhdr*) ; 

__attribute__((used)) static inline u32 bond_eth_hash(struct sk_buff *skb)
{
	struct ethhdr *ep, hdr_tmp;

	ep = skb_header_pointer(skb, 0, sizeof(hdr_tmp), &hdr_tmp);
	if (ep)
		return ep->h_dest[5] ^ ep->h_source[5] ^ ep->h_proto;
	return 0;
}