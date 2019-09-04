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
typedef  int /*<<< orphan*/  u16 ;
struct ethtool_rxnfc {int flow_type; int /*<<< orphan*/  data; } ;
struct ena_com_dev {int dummy; } ;
typedef  enum ena_admin_flow_hash_proto { ____Placeholder_ena_admin_flow_hash_proto } ena_admin_flow_hash_proto ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 140 
#define  AH_V4_FLOW 139 
#define  AH_V6_FLOW 138 
 int EINVAL ; 
 int ENA_ADMIN_RSS_IP4 ; 
 int ENA_ADMIN_RSS_IP6 ; 
 int ENA_ADMIN_RSS_NOT_IP ; 
 int ENA_ADMIN_RSS_TCP4 ; 
 int ENA_ADMIN_RSS_TCP6 ; 
 int ENA_ADMIN_RSS_UDP4 ; 
 int ENA_ADMIN_RSS_UDP6 ; 
 int EOPNOTSUPP ; 
#define  ESP_V4_FLOW 137 
#define  ESP_V6_FLOW 136 
#define  ETHER_FLOW 135 
#define  IPV4_FLOW 134 
#define  IPV6_FLOW 133 
#define  SCTP_V4_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int ena_com_get_hash_ctrl (struct ena_com_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ena_flow_hash_to_flow_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ena_get_rss_hash(struct ena_com_dev *ena_dev,
			    struct ethtool_rxnfc *cmd)
{
	enum ena_admin_flow_hash_proto proto;
	u16 hash_fields;
	int rc;

	cmd->data = 0;

	switch (cmd->flow_type) {
	case TCP_V4_FLOW:
		proto = ENA_ADMIN_RSS_TCP4;
		break;
	case UDP_V4_FLOW:
		proto = ENA_ADMIN_RSS_UDP4;
		break;
	case TCP_V6_FLOW:
		proto = ENA_ADMIN_RSS_TCP6;
		break;
	case UDP_V6_FLOW:
		proto = ENA_ADMIN_RSS_UDP6;
		break;
	case IPV4_FLOW:
		proto = ENA_ADMIN_RSS_IP4;
		break;
	case IPV6_FLOW:
		proto = ENA_ADMIN_RSS_IP6;
		break;
	case ETHER_FLOW:
		proto = ENA_ADMIN_RSS_NOT_IP;
		break;
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
	case SCTP_V4_FLOW:
	case AH_ESP_V4_FLOW:
		return -EOPNOTSUPP;
	default:
		return -EINVAL;
	}

	rc = ena_com_get_hash_ctrl(ena_dev, proto, &hash_fields);
	if (rc)
		return rc;

	cmd->data = ena_flow_hash_to_flow_type(hash_fields);

	return 0;
}