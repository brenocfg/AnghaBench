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
typedef  int /*<<< orphan*/  u8 ;
struct ethtool_rxnfc {int data; scalar_t__ flow_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_D_IP_BIT ; 
 int /*<<< orphan*/  HCLGEVF_D_PORT_BIT ; 
 int /*<<< orphan*/  HCLGEVF_S_IP_BIT ; 
 int /*<<< orphan*/  HCLGEVF_S_PORT_BIT ; 
 int /*<<< orphan*/  HCLGEVF_V_TAG_BIT ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
 scalar_t__ SCTP_V4_FLOW ; 
 scalar_t__ SCTP_V6_FLOW ; 

__attribute__((used)) static u8 hclgevf_get_rss_hash_bits(struct ethtool_rxnfc *nfc)
{
	u8 hash_sets = nfc->data & RXH_L4_B_0_1 ? HCLGEVF_S_PORT_BIT : 0;

	if (nfc->data & RXH_L4_B_2_3)
		hash_sets |= HCLGEVF_D_PORT_BIT;
	else
		hash_sets &= ~HCLGEVF_D_PORT_BIT;

	if (nfc->data & RXH_IP_SRC)
		hash_sets |= HCLGEVF_S_IP_BIT;
	else
		hash_sets &= ~HCLGEVF_S_IP_BIT;

	if (nfc->data & RXH_IP_DST)
		hash_sets |= HCLGEVF_D_IP_BIT;
	else
		hash_sets &= ~HCLGEVF_D_IP_BIT;

	if (nfc->flow_type == SCTP_V4_FLOW || nfc->flow_type == SCTP_V6_FLOW)
		hash_sets |= HCLGEVF_V_TAG_BIT;

	return hash_sets;
}