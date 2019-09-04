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
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int cmd; int data; int /*<<< orphan*/  flow_type; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_GRXFH 135 
#define  ETHTOOL_GRXRINGS 134 
#define  IPV4_FLOW 133 
#define  IPV6_FLOW 132 
 int LAN743X_USED_RX_CHANNELS ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 

__attribute__((used)) static int lan743x_ethtool_get_rxnfc(struct net_device *netdev,
				     struct ethtool_rxnfc *rxnfc,
				     u32 *rule_locs)
{
	switch (rxnfc->cmd) {
	case ETHTOOL_GRXFH:
		rxnfc->data = 0;
		switch (rxnfc->flow_type) {
		case TCP_V4_FLOW:case UDP_V4_FLOW:
		case TCP_V6_FLOW:case UDP_V6_FLOW:
			rxnfc->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
			/* fall through */
		case IPV4_FLOW: case IPV6_FLOW:
			rxnfc->data |= RXH_IP_SRC | RXH_IP_DST;
			return 0;
		}
		break;
	case ETHTOOL_GRXRINGS:
		rxnfc->data = LAN743X_USED_RX_CHANNELS;
		return 0;
	}
	return -EOPNOTSUPP;
}