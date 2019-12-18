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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ ip_summed; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 scalar_t__ skb_is_gso (struct sk_buff const*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 

__attribute__((used)) static unsigned tx_le_req(const struct sk_buff *skb)
{
	unsigned count;

	count = (skb_shinfo(skb)->nr_frags + 1)
		* (sizeof(dma_addr_t) / sizeof(u32));

	if (skb_is_gso(skb))
		++count;
	else if (sizeof(dma_addr_t) == sizeof(u32))
		++count;	/* possible vlan */

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		++count;

	return count;
}