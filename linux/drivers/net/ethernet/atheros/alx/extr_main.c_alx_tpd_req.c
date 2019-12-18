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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int nr_frags; int gso_type; } ;

/* Variables and functions */
 int SKB_GSO_TCPV6 ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static int alx_tpd_req(struct sk_buff *skb)
{
	int num;

	num = skb_shinfo(skb)->nr_frags + 1;
	/* we need one extra descriptor for LSOv2 */
	if (skb_is_gso(skb) && skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6)
		num++;

	return num;
}