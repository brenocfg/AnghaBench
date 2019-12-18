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
struct ethtool_rxnfc {int data; int flow_type; } ;
struct enic {int /*<<< orphan*/  devcmd_lock; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 141 
#define  AH_ESP_V6_FLOW 140 
#define  AH_V4_FLOW 139 
#define  AH_V6_FLOW 138 
 int EINVAL ; 
#define  ESP_V4_FLOW 137 
#define  ESP_V6_FLOW 136 
#define  IPV4_FLOW 135 
#define  IPV6_FLOW 134 
 int NIC_CFG_RSS_HASH_TYPE_UDP_IPV4 ; 
 int NIC_CFG_RSS_HASH_TYPE_UDP_IPV6 ; 
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
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnic_dev_capable_rss_hash_type (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int enic_get_rx_flow_hash(struct enic *enic, struct ethtool_rxnfc *cmd)
{
	u8 rss_hash_type = 0;
	cmd->data = 0;

	spin_lock_bh(&enic->devcmd_lock);
	(void)vnic_dev_capable_rss_hash_type(enic->vdev, &rss_hash_type);
	spin_unlock_bh(&enic->devcmd_lock);
	switch (cmd->flow_type) {
	case TCP_V6_FLOW:
	case TCP_V4_FLOW:
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3 |
			     RXH_IP_SRC | RXH_IP_DST;
		break;
	case UDP_V6_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		if (rss_hash_type & NIC_CFG_RSS_HASH_TYPE_UDP_IPV6)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	case UDP_V4_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		if (rss_hash_type & NIC_CFG_RSS_HASH_TYPE_UDP_IPV4)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	case SCTP_V4_FLOW:
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
	case SCTP_V6_FLOW:
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
	case IPV4_FLOW:
	case IPV6_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}