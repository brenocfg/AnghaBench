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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {int flags; int hw_features; TYPE_1__* pdev; struct i40e_hw hw; } ;
struct ethtool_rxnfc {int data; int flow_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 141 
#define  AH_ESP_V6_FLOW 140 
#define  AH_V4_FLOW 139 
#define  AH_V6_FLOW 138 
 int BIT_ULL (scalar_t__) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  ESP_V4_FLOW 137 
#define  ESP_V6_FLOW 136 
 scalar_t__ I40E_FILTER_PCTYPE_FRAG_IPV4 ; 
 scalar_t__ I40E_FILTER_PCTYPE_FRAG_IPV6 ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV4_OTHER ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV4_TCP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV4_UDP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV6_OTHER ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV6_TCP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV6_TCP_SYN_NO_ACK ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_IPV6_UDP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_MULTICAST_IPV4_UDP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_MULTICAST_IPV6_UDP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_UNICAST_IPV4_UDP ; 
 scalar_t__ I40E_FILTER_PCTYPE_NONF_UNICAST_IPV6_UDP ; 
 int I40E_FLAG_MFP_ENABLED ; 
 int /*<<< orphan*/  I40E_GLQF_HASH_INSET (int,scalar_t__) ; 
 int I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE ; 
 int /*<<< orphan*/  I40E_PFQF_HENA (int) ; 
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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i40e_flush (struct i40e_hw*) ; 
 int i40e_get_rss_hash_bits (struct ethtool_rxnfc*,int) ; 
 scalar_t__ i40e_read_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_write_rx_ctl (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_set_rss_hash_opt(struct i40e_pf *pf, struct ethtool_rxnfc *nfc)
{
	struct i40e_hw *hw = &pf->hw;
	u64 hena = (u64)i40e_read_rx_ctl(hw, I40E_PFQF_HENA(0)) |
		   ((u64)i40e_read_rx_ctl(hw, I40E_PFQF_HENA(1)) << 32);
	u8 flow_pctype = 0;
	u64 i_set, i_setc;

	if (pf->flags & I40E_FLAG_MFP_ENABLED) {
		dev_err(&pf->pdev->dev,
			"Change of RSS hash input set is not supported when MFP mode is enabled\n");
		return -EOPNOTSUPP;
	}

	/* RSS does not support anything other than hashing
	 * to queues on src and dst IPs and ports
	 */
	if (nfc->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		return -EINVAL;

	switch (nfc->flow_type) {
	case TCP_V4_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV4_TCP;
		if (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK);
		break;
	case TCP_V6_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV6_TCP;
		if (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_TCP_SYN_NO_ACK);
		if (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_TCP_SYN_NO_ACK);
		break;
	case UDP_V4_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV4_UDP;
		if (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_UNICAST_IPV4_UDP) |
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_MULTICAST_IPV4_UDP);

		hena |= BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV4);
		break;
	case UDP_V6_FLOW:
		flow_pctype = I40E_FILTER_PCTYPE_NONF_IPV6_UDP;
		if (pf->hw_features & I40E_HW_MULTIPLE_TCP_UDP_RSS_PCTYPE)
			hena |=
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_UNICAST_IPV6_UDP) |
			  BIT_ULL(I40E_FILTER_PCTYPE_NONF_MULTICAST_IPV6_UDP);

		hena |= BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV6);
		break;
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
	case SCTP_V4_FLOW:
		if ((nfc->data & RXH_L4_B_0_1) ||
		    (nfc->data & RXH_L4_B_2_3))
			return -EINVAL;
		hena |= BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_OTHER);
		break;
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
	case SCTP_V6_FLOW:
		if ((nfc->data & RXH_L4_B_0_1) ||
		    (nfc->data & RXH_L4_B_2_3))
			return -EINVAL;
		hena |= BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_OTHER);
		break;
	case IPV4_FLOW:
		hena |= BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV4_OTHER) |
			BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV4);
		break;
	case IPV6_FLOW:
		hena |= BIT_ULL(I40E_FILTER_PCTYPE_NONF_IPV6_OTHER) |
			BIT_ULL(I40E_FILTER_PCTYPE_FRAG_IPV6);
		break;
	default:
		return -EINVAL;
	}

	if (flow_pctype) {
		i_setc = (u64)i40e_read_rx_ctl(hw, I40E_GLQF_HASH_INSET(0,
					       flow_pctype)) |
			((u64)i40e_read_rx_ctl(hw, I40E_GLQF_HASH_INSET(1,
					       flow_pctype)) << 32);
		i_set = i40e_get_rss_hash_bits(nfc, i_setc);
		i40e_write_rx_ctl(hw, I40E_GLQF_HASH_INSET(0, flow_pctype),
				  (u32)i_set);
		i40e_write_rx_ctl(hw, I40E_GLQF_HASH_INSET(1, flow_pctype),
				  (u32)(i_set >> 32));
		hena |= BIT_ULL(flow_pctype);
	}

	i40e_write_rx_ctl(hw, I40E_PFQF_HENA(0), (u32)hena);
	i40e_write_rx_ctl(hw, I40E_PFQF_HENA(1), (u32)(hena >> 32));
	i40e_flush(hw);

	return 0;
}