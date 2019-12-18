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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int version; int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/  nexthdr; } ;

/* Variables and functions */
 TYPE_2__* inner_ip_hdr (struct sk_buff*) ; 
 TYPE_1__* inner_ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static u16 skb_inner_ip_proto(struct sk_buff *skb)
{
	return (inner_ip_hdr(skb)->version == 4) ?
		inner_ip_hdr(skb)->protocol : inner_ipv6_hdr(skb)->nexthdr;
}