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
typedef  int /*<<< orphan*/  u64 ;
struct ethtool_rxnfc {int data; scalar_t__ flow_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_L3_DST_MASK ; 
 int /*<<< orphan*/  I40E_L3_SRC_MASK ; 
 int /*<<< orphan*/  I40E_L3_V6_DST_MASK ; 
 int /*<<< orphan*/  I40E_L3_V6_SRC_MASK ; 
 int /*<<< orphan*/  I40E_L4_DST_MASK ; 
 int /*<<< orphan*/  I40E_L4_SRC_MASK ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
 scalar_t__ TCP_V4_FLOW ; 
 scalar_t__ TCP_V6_FLOW ; 
 scalar_t__ UDP_V4_FLOW ; 
 scalar_t__ UDP_V6_FLOW ; 

__attribute__((used)) static u64 i40e_get_rss_hash_bits(struct ethtool_rxnfc *nfc, u64 i_setc)
{
	u64 i_set = i_setc;
	u64 src_l3 = 0, dst_l3 = 0;

	if (nfc->data & RXH_L4_B_0_1)
		i_set |= I40E_L4_SRC_MASK;
	else
		i_set &= ~I40E_L4_SRC_MASK;
	if (nfc->data & RXH_L4_B_2_3)
		i_set |= I40E_L4_DST_MASK;
	else
		i_set &= ~I40E_L4_DST_MASK;

	if (nfc->flow_type == TCP_V6_FLOW || nfc->flow_type == UDP_V6_FLOW) {
		src_l3 = I40E_L3_V6_SRC_MASK;
		dst_l3 = I40E_L3_V6_DST_MASK;
	} else if (nfc->flow_type == TCP_V4_FLOW ||
		  nfc->flow_type == UDP_V4_FLOW) {
		src_l3 = I40E_L3_SRC_MASK;
		dst_l3 = I40E_L3_DST_MASK;
	} else {
		/* Any other flow type are not supported here */
		return i_set;
	}

	if (nfc->data & RXH_IP_SRC)
		i_set |= src_l3;
	else
		i_set &= ~src_l3;
	if (nfc->data & RXH_IP_DST)
		i_set |= dst_l3;
	else
		i_set &= ~dst_l3;

	return i_set;
}