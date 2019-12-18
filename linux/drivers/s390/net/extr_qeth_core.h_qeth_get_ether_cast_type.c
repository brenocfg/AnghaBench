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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * h_dest; } ;

/* Variables and functions */
 int RTN_BROADCAST ; 
 int RTN_MULTICAST ; 
 int RTN_UNICAST ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ *) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int qeth_get_ether_cast_type(struct sk_buff *skb)
{
	u8 *addr = eth_hdr(skb)->h_dest;

	if (is_multicast_ether_addr(addr))
		return is_broadcast_ether_addr(addr) ? RTN_BROADCAST :
						       RTN_MULTICAST;
	return RTN_UNICAST;
}