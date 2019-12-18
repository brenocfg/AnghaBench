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
typedef  int u64 ;
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;

/* Variables and functions */
 int AQ_RX_PD_L3_ERR ; 
 int AQ_RX_PD_L4_ERR ; 
 int AQ_RX_PD_L4_TCP ; 
 int AQ_RX_PD_L4_TYPE_MASK ; 
 int AQ_RX_PD_L4_UDP ; 
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 

__attribute__((used)) static void aqc111_rx_checksum(struct sk_buff *skb, u64 pkt_desc)
{
	u32 pkt_type = 0;

	skb->ip_summed = CHECKSUM_NONE;
	/* checksum error bit is set */
	if (pkt_desc & AQ_RX_PD_L4_ERR || pkt_desc & AQ_RX_PD_L3_ERR)
		return;

	pkt_type = pkt_desc & AQ_RX_PD_L4_TYPE_MASK;
	/* It must be a TCP or UDP packet with a valid checksum */
	if (pkt_type == AQ_RX_PD_L4_TCP || pkt_type == AQ_RX_PD_L4_UDP)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
}