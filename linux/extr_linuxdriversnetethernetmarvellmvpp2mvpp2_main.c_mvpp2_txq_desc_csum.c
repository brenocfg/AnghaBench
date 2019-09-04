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
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int MVPP2_TXD_IP_CSUM_DISABLE ; 
 int MVPP2_TXD_IP_HLEN_SHIFT ; 
 int MVPP2_TXD_L3_IP6 ; 
 int MVPP2_TXD_L3_OFF_SHIFT ; 
 int MVPP2_TXD_L4_CSUM_FRAG ; 
 int MVPP2_TXD_L4_CSUM_NOT ; 
 int MVPP2_TXD_L4_UDP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mvpp2_txq_desc_csum(int l3_offs, __be16 l3_proto,
			       int ip_hdr_len, int l4_proto)
{
	u32 command;

	/* fields: L3_offset, IP_hdrlen, L3_type, G_IPv4_chk,
	 * G_L4_chk, L4_type required only for checksum calculation
	 */
	command = (l3_offs << MVPP2_TXD_L3_OFF_SHIFT);
	command |= (ip_hdr_len << MVPP2_TXD_IP_HLEN_SHIFT);
	command |= MVPP2_TXD_IP_CSUM_DISABLE;

	if (l3_proto == htons(ETH_P_IP)) {
		command &= ~MVPP2_TXD_IP_CSUM_DISABLE;	/* enable IPv4 csum */
		command &= ~MVPP2_TXD_L3_IP6;		/* enable IPv4 */
	} else {
		command |= MVPP2_TXD_L3_IP6;		/* enable IPv6 */
	}

	if (l4_proto == IPPROTO_TCP) {
		command &= ~MVPP2_TXD_L4_UDP;		/* enable TCP */
		command &= ~MVPP2_TXD_L4_CSUM_FRAG;	/* generate L4 csum */
	} else if (l4_proto == IPPROTO_UDP) {
		command |= MVPP2_TXD_L4_UDP;		/* enable UDP */
		command &= ~MVPP2_TXD_L4_CSUM_FRAG;	/* generate L4 csum */
	} else {
		command |= MVPP2_TXD_L4_CSUM_NOT;
	}

	return command;
}