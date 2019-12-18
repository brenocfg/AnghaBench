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
struct hinic_rss_type {int /*<<< orphan*/  udp_ipv6; int /*<<< orphan*/  udp_ipv4; int /*<<< orphan*/  tcp_ipv6; int /*<<< orphan*/  tcp_ipv4; int /*<<< orphan*/  member_0; } ;
struct hinic_dev {int flags; int /*<<< orphan*/  rss_tmpl_idx; } ;
struct ethtool_rxnfc {int data; int flow_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int HINIC_RSS_ENABLE ; 
#define  IPV4_FLOW 133 
#define  IPV6_FLOW 132 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int hinic_get_rss_type (struct hinic_dev*,int /*<<< orphan*/ ,struct hinic_rss_type*) ; 

__attribute__((used)) static int hinic_get_rss_hash_opts(struct hinic_dev *nic_dev,
				   struct ethtool_rxnfc *cmd)
{
	struct hinic_rss_type rss_type = { 0 };
	int err;

	cmd->data = 0;

	if (!(nic_dev->flags & HINIC_RSS_ENABLE))
		return 0;

	err = hinic_get_rss_type(nic_dev, nic_dev->rss_tmpl_idx,
				 &rss_type);
	if (err)
		return err;

	cmd->data = RXH_IP_SRC | RXH_IP_DST;
	switch (cmd->flow_type) {
	case TCP_V4_FLOW:
		if (rss_type.tcp_ipv4)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	case TCP_V6_FLOW:
		if (rss_type.tcp_ipv6)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	case UDP_V4_FLOW:
		if (rss_type.udp_ipv4)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	case UDP_V6_FLOW:
		if (rss_type.udp_ipv6)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		break;
	case IPV4_FLOW:
	case IPV6_FLOW:
		break;
	default:
		cmd->data = 0;
		return -EINVAL;
	}

	return 0;
}