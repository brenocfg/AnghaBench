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
struct ethtool_rxnfc {int flow_type; int data; } ;
struct TYPE_2__ {int udp_rss_v4; int udp_rss_v6; } ;
struct bnx2x {TYPE_1__ rss_conf_obj; int /*<<< orphan*/  state; } ;

/* Variables and functions */
#define  AH_ESP_V4_FLOW 143 
#define  AH_ESP_V6_FLOW 142 
#define  AH_V4_FLOW 141 
#define  AH_V6_FLOW 140 
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 int /*<<< orphan*/  BNX2X_STATE_OPEN ; 
 int /*<<< orphan*/  CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
#define  ESP_V4_FLOW 139 
#define  ESP_V6_FLOW 138 
#define  ETHER_FLOW 137 
#define  IPV4_FLOW 136 
#define  IPV6_FLOW 135 
#define  IP_USER_FLOW 134 
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
 int bnx2x_rss (struct bnx2x*,TYPE_1__*,int,int) ; 

__attribute__((used)) static int bnx2x_set_rss_flags(struct bnx2x *bp, struct ethtool_rxnfc *info)
{
	int udp_rss_requested;

	DP(BNX2X_MSG_ETHTOOL,
	   "Set rss flags command parameters: flow type = %d, data = %llu\n",
	   info->flow_type, info->data);

	switch (info->flow_type) {
	case TCP_V4_FLOW:
	case TCP_V6_FLOW:
		/* For TCP only 4-tupple hash is supported */
		if (info->data ^ (RXH_IP_SRC | RXH_IP_DST |
				  RXH_L4_B_0_1 | RXH_L4_B_2_3)) {
			DP(BNX2X_MSG_ETHTOOL,
			   "Command parameters not supported\n");
			return -EINVAL;
		}
		return 0;

	case UDP_V4_FLOW:
	case UDP_V6_FLOW:
		/* For UDP either 2-tupple hash or 4-tupple hash is supported */
		if (info->data == (RXH_IP_SRC | RXH_IP_DST |
				   RXH_L4_B_0_1 | RXH_L4_B_2_3))
			udp_rss_requested = 1;
		else if (info->data == (RXH_IP_SRC | RXH_IP_DST))
			udp_rss_requested = 0;
		else
			return -EINVAL;

		if (CHIP_IS_E1x(bp) && udp_rss_requested) {
			DP(BNX2X_MSG_ETHTOOL,
			   "57710, 57711 boards don't support RSS according to UDP 4-tuple\n");
			return -EINVAL;
		}

		if ((info->flow_type == UDP_V4_FLOW) &&
		    (bp->rss_conf_obj.udp_rss_v4 != udp_rss_requested)) {
			bp->rss_conf_obj.udp_rss_v4 = udp_rss_requested;
			DP(BNX2X_MSG_ETHTOOL,
			   "rss re-configured, UDP 4-tupple %s\n",
			   udp_rss_requested ? "enabled" : "disabled");
			if (bp->state == BNX2X_STATE_OPEN)
				return bnx2x_rss(bp, &bp->rss_conf_obj, false,
						 true);
		} else if ((info->flow_type == UDP_V6_FLOW) &&
			   (bp->rss_conf_obj.udp_rss_v6 != udp_rss_requested)) {
			bp->rss_conf_obj.udp_rss_v6 = udp_rss_requested;
			DP(BNX2X_MSG_ETHTOOL,
			   "rss re-configured, UDP 4-tupple %s\n",
			   udp_rss_requested ? "enabled" : "disabled");
			if (bp->state == BNX2X_STATE_OPEN)
				return bnx2x_rss(bp, &bp->rss_conf_obj, false,
						 true);
		}
		return 0;

	case IPV4_FLOW:
	case IPV6_FLOW:
		/* For IP only 2-tupple hash is supported */
		if (info->data ^ (RXH_IP_SRC | RXH_IP_DST)) {
			DP(BNX2X_MSG_ETHTOOL,
			   "Command parameters not supported\n");
			return -EINVAL;
		}
		return 0;

	case SCTP_V4_FLOW:
	case AH_ESP_V4_FLOW:
	case AH_V4_FLOW:
	case ESP_V4_FLOW:
	case SCTP_V6_FLOW:
	case AH_ESP_V6_FLOW:
	case AH_V6_FLOW:
	case ESP_V6_FLOW:
	case IP_USER_FLOW:
	case ETHER_FLOW:
		/* RSS is not supported for these protocols */
		if (info->data) {
			DP(BNX2X_MSG_ETHTOOL,
			   "Command parameters not supported\n");
			return -EINVAL;
		}
		return 0;

	default:
		return -EINVAL;
	}
}