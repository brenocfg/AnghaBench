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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int MVNETA_TXD_IP_CSUM ; 
 int MVNETA_TX_IP_HLEN_SHIFT ; 
 int MVNETA_TX_L3_IP6 ; 
 int MVNETA_TX_L3_OFF_SHIFT ; 
 int MVNETA_TX_L4_CSUM_FULL ; 
 int MVNETA_TX_L4_CSUM_NOT ; 
 int MVNETA_TX_L4_UDP ; 
 int htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mvneta_txq_desc_csum(int l3_offs, int l3_proto,
				int ip_hdr_len, int l4_proto)
{
	u32 command;

	/* Fields: L3_offset, IP_hdrlen, L3_type, G_IPv4_chk,
	 * G_L4_chk, L4_type; required only for checksum
	 * calculation
	 */
	command =  l3_offs    << MVNETA_TX_L3_OFF_SHIFT;
	command |= ip_hdr_len << MVNETA_TX_IP_HLEN_SHIFT;

	if (l3_proto == htons(ETH_P_IP))
		command |= MVNETA_TXD_IP_CSUM;
	else
		command |= MVNETA_TX_L3_IP6;

	if (l4_proto == IPPROTO_TCP)
		command |=  MVNETA_TX_L4_CSUM_FULL;
	else if (l4_proto == IPPROTO_UDP)
		command |= MVNETA_TX_L4_UDP | MVNETA_TX_L4_CSUM_FULL;
	else
		command |= MVNETA_TX_L4_CSUM_NOT;

	return command;
}