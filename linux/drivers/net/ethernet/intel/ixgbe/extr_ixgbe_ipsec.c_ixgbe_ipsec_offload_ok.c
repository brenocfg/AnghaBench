#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ family; } ;
struct xfrm_state {TYPE_1__ props; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int ihl; } ;
struct TYPE_5__ {int /*<<< orphan*/  nexthdr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ipv6_ext_hdr (int /*<<< orphan*/ ) ; 
 TYPE_2__* ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static bool ixgbe_ipsec_offload_ok(struct sk_buff *skb, struct xfrm_state *xs)
{
	if (xs->props.family == AF_INET) {
		/* Offload with IPv4 options is not supported yet */
		if (ip_hdr(skb)->ihl != 5)
			return false;
	} else {
		/* Offload with IPv6 extension headers is not support yet */
		if (ipv6_ext_hdr(ipv6_hdr(skb)->nexthdr))
			return false;
	}

	return true;
}