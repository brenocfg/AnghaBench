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
typedef  int u8 ;
typedef  int u32 ;
struct iphdr {int tos; } ;

/* Variables and functions */

u8 ath6kl_wmi_determine_user_priority(u8 *pkt, u32 layer2_pri)
{
	struct iphdr *ip_hdr = (struct iphdr *) pkt;
	u8 ip_pri;

	/*
	 * Determine IPTOS priority
	 *
	 * IP-TOS - 8bits
	 *          : DSCP(6-bits) ECN(2-bits)
	 *          : DSCP - P2 P1 P0 X X X
	 * where (P2 P1 P0) form 802.1D
	 */
	ip_pri = ip_hdr->tos >> 5;
	ip_pri &= 0x7;

	if ((layer2_pri & 0x7) > ip_pri)
		return (u8) layer2_pri & 0x7;
	else
		return ip_pri;
}