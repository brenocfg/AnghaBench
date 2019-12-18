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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ ETHER_STD_PACKET ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ INGRESS_CRC ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool xgene_enet_errata_10GE_10(struct sk_buff *skb, u32 len, u8 status)
{
	if (status == INGRESS_CRC &&
	    len >= (ETHER_STD_PACKET + 1) &&
	    len <= (ETHER_STD_PACKET + 4) &&
	    skb->protocol == htons(ETH_P_8021Q))
		return true;

	return false;
}