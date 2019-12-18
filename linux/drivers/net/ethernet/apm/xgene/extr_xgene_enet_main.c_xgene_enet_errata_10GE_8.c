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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  h_proto; } ;

/* Variables and functions */
 scalar_t__ ETHER_MIN_PACKET ; 
 scalar_t__ INGRESS_PKT_LEN ; 
 TYPE_1__* eth_hdr (struct sk_buff*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool xgene_enet_errata_10GE_8(struct sk_buff *skb, u32 len, u8 status)
{
	if (status == INGRESS_PKT_LEN && len == ETHER_MIN_PACKET) {
		if (ntohs(eth_hdr(skb)->h_proto) < 46)
			return true;
	}

	return false;
}