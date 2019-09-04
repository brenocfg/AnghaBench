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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ protocol; } ;
struct TYPE_4__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/  nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* ip_hdr (struct sk_buff const*) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff const*) ; 

__attribute__((used)) static u8 arfs_get_ip_proto(const struct sk_buff *skb)
{
	return (skb->protocol == htons(ETH_P_IP)) ?
		ip_hdr(skb)->protocol : ipv6_hdr(skb)->nexthdr;
}