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
typedef  int /*<<< orphan*/  u32 ;
struct ethtool_rxnfc {scalar_t__ data; int flow_type; } ;
struct bnxt {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  rss_hash_cfg; } ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 141 
#define  AH_ESP_V6_FLOW 140 
#define  AH_V4_FLOW 139 
#define  AH_V6_FLOW 138 
 int BNXT_FLAG_UDP_RSS_CAP ; 
 int EINVAL ; 
#define  ESP_V4_FLOW 137 
#define  ESP_V6_FLOW 136 
#define  IPV4_FLOW 135 
#define  IPV6_FLOW 134 
 scalar_t__ RXH_2TUPLE ; 
 scalar_t__ RXH_4TUPLE ; 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int /*<<< orphan*/  VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4 ; 
 int /*<<< orphan*/  VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6 ; 
 int /*<<< orphan*/  VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4 ; 
 int /*<<< orphan*/  VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6 ; 
 int /*<<< orphan*/  VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4 ; 
 int /*<<< orphan*/  VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6 ; 
 int /*<<< orphan*/  bnxt_close_nic (struct bnxt*,int,int) ; 
 int bnxt_open_nic (struct bnxt*,int,int) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_srxfh(struct bnxt *bp, struct ethtool_rxnfc *cmd)
{
	u32 rss_hash_cfg = bp->rss_hash_cfg;
	int tuple, rc = 0;

	if (cmd->data == RXH_4TUPLE)
		tuple = 4;
	else if (cmd->data == RXH_2TUPLE)
		tuple = 2;
	else if (!cmd->data)
		tuple = 0;
	else
		return -EINVAL;

	if (cmd->flow_type == TCP_V4_FLOW) {
		rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4;
		if (tuple == 4)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV4;
	} else if (cmd->flow_type == UDP_V4_FLOW) {
		if (tuple == 4 && !(bp->flags & BNXT_FLAG_UDP_RSS_CAP))
			return -EINVAL;
		rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4;
		if (tuple == 4)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV4;
	} else if (cmd->flow_type == TCP_V6_FLOW) {
		rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6;
		if (tuple == 4)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_TCP_IPV6;
	} else if (cmd->flow_type == UDP_V6_FLOW) {
		if (tuple == 4 && !(bp->flags & BNXT_FLAG_UDP_RSS_CAP))
			return -EINVAL;
		rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6;
		if (tuple == 4)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_UDP_IPV6;
	} else if (tuple == 4) {
		return -EINVAL;
	}

	switch (cmd->flow_type) {
	case TCP_V4_FLOW:
	case UDP_V4_FLOW:
	case SCTP_V4_FLOW:
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
	case IPV4_FLOW:
		if (tuple == 2)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4;
		else if (!tuple)
			rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_IPV4;
		break;

	case TCP_V6_FLOW:
	case UDP_V6_FLOW:
	case SCTP_V6_FLOW:
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
	case IPV6_FLOW:
		if (tuple == 2)
			rss_hash_cfg |= VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6;
		else if (!tuple)
			rss_hash_cfg &= ~VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6;
		break;
	}

	if (bp->rss_hash_cfg == rss_hash_cfg)
		return 0;

	bp->rss_hash_cfg = rss_hash_cfg;
	if (netif_running(bp->dev)) {
		bnxt_close_nic(bp, false, false);
		rc = bnxt_open_nic(bp, false, false);
	}
	return rc;
}