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
typedef  int u64 ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {struct i40e_hw hw; } ;
struct ethtool_rxnfc {int data; int flow_type; } ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 141 
#define  AH_ESP_V6_FLOW 140 
#define  AH_V4_FLOW 139 
#define  AH_V6_FLOW 138 
 int EINVAL ; 
#define  ESP_V4_FLOW 137 
#define  ESP_V6_FLOW 136 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV4_TCP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV4_UDP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV6_TCP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV6_UDP ; 
 int /*<<< orphan*/  I40E_GLQF_HASH_INSET (int,scalar_t__) ; 
 int I40E_L3_DST_MASK ; 
 int I40E_L3_SRC_MASK ; 
 int I40E_L3_V6_DST_MASK ; 
 int I40E_L3_V6_SRC_MASK ; 
 int I40E_L4_DST_MASK ; 
 int I40E_L4_SRC_MASK ; 
#define  IPV4_FLOW 135 
#define  IPV6_FLOW 134 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 scalar_t__ i40e_read_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_get_rss_hash_opts(struct i40e_pf *pf, struct ethtool_rxnfc *cmd)
{
	struct i40e_hw *hw = &pf->hw;
	u8 flow_pctype = 0;
	u64 i_set = 0;

	cmd->data = 0;

	switch (cmd->flow_type) {
	case TCP_V4_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV4_TCP;
		break;
	case UDP_V4_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV4_UDP;
		break;
	case TCP_V6_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV6_TCP;
		break;
	case UDP_V6_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV6_UDP;
		break;
	case SCTP_V4_FLOW:
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
	case IPV4_FLOW:
	case SCTP_V6_FLOW:
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
	case IPV6_FLOW:
		/* Default is src/dest for IP, no matter the L4 hashing */
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		break;
	default:
		return -EINVAL;
	}

	/* Read flow based hash input set register */
	if (flow_pctype) {
		i_set = (u64)i40e_read_rx_ctl(hw, I40E_GLQF_HASH_INSET(0,
					      flow_pctype)) |
			((u64)i40e_read_rx_ctl(hw, I40E_GLQF_HASH_INSET(1,
					       flow_pctype)) << 32);
	}

	/* Process bits of hash input set */
	if (i_set) {
		if (i_set & I40E_L4_SRC_MASK)
			cmd->data |= RXH_L4_B_0_1;
		if (i_set & I40E_L4_DST_MASK)
			cmd->data |= RXH_L4_B_2_3;

		if (cmd->flow_type == TCP_V4_FLOW ||
		    cmd->flow_type == UDP_V4_FLOW) {
			if (i_set & I40E_L3_SRC_MASK)
				cmd->data |= RXH_IP_SRC;
			if (i_set & I40E_L3_DST_MASK)
				cmd->data |= RXH_IP_DST;
		} else if (cmd->flow_type == TCP_V6_FLOW ||
			  cmd->flow_type == UDP_V6_FLOW) {
			if (i_set & I40E_L3_V6_SRC_MASK)
				cmd->data |= RXH_IP_SRC;
			if (i_set & I40E_L3_V6_DST_MASK)
				cmd->data |= RXH_IP_DST;
		}
	}

	return 0;
}