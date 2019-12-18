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
struct ethtool_rxnfc {int data; int flow_type; } ;
struct bnxt {int rss_hash_cfg; } ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 141 
#define  AH_ESP_V6_FLOW 140 
#define  AH_V4_FLOW 139 
#define  AH_V6_FLOW 138 
#define  ESP_V4_FLOW 137 
#define  ESP_V6_FLOW 136 
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
 int VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4 ; 
 int VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6 ; 
 int VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4 ; 
 int VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6 ; 
 int get_ethtool_ipv4_rss (struct bnxt*) ; 
 int get_ethtool_ipv6_rss (struct bnxt*) ; 

__attribute__((used)) static int bnxt_grxfh(struct bnxt *bp, struct ethtool_rxnfc *cmd)
{
	cmd->data = 0;
	switch (cmd->flow_type) {
	case TCP_V4_FLOW:
		if (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		cmd->data |= get_ethtool_ipv4_rss(bp);
		break;
	case UDP_V4_FLOW:
		if (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		/* fall through */
	case SCTP_V4_FLOW:
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
	case IPV4_FLOW:
		cmd->data |= get_ethtool_ipv4_rss(bp);
		break;

	case TCP_V6_FLOW:
		if (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		cmd->data |= get_ethtool_ipv6_rss(bp);
		break;
	case UDP_V6_FLOW:
		if (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		/* fall through */
	case SCTP_V6_FLOW:
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
	case IPV6_FLOW:
		cmd->data |= get_ethtool_ipv6_rss(bp);
		break;
	}
	return 0;
}