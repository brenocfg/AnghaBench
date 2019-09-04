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
struct xfrm_state {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int ihl; } ;

/* Variables and functions */
 TYPE_1__* ip_hdr (struct sk_buff*) ; 

__attribute__((used)) static bool chcr_ipsec_offload_ok(struct sk_buff *skb, struct xfrm_state *x)
{
	/* Offload with IP options is not supported yet */
	if (ip_hdr(skb)->ihl > 5)
		return false;

	return true;
}