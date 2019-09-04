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
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int version; } ;
struct TYPE_3__ {int /*<<< orphan*/  nexthdr; } ;

/* Variables and functions */
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int ipv6_ext_hdr (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline bool is_ipv6_ext_hdr(struct sk_buff *skb)
{
	if (ip_hdr(skb)->version == 6)
		return ipv6_ext_hdr(ipv6_hdr(skb)->nexthdr);
	else
		return false;
}