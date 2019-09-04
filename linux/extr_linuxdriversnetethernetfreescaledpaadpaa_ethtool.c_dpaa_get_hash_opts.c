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
struct net_device {int dummy; } ;
struct ethtool_rxnfc {int data; int flow_type; } ;
struct dpaa_priv {int /*<<< orphan*/  keygen_in_use; } ;

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
 struct dpaa_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dpaa_get_hash_opts(struct net_device *dev,
			      struct ethtool_rxnfc *cmd)
{
	struct dpaa_priv *priv = netdev_priv(dev);

	cmd->data = 0;

	switch (cmd->flow_type) {
	case TCP_V4_FLOW:
	case TCP_V6_FLOW:
	case UDP_V4_FLOW:
	case UDP_V6_FLOW:
		if (priv->keygen_in_use)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		/* Fall through */
	case IPV4_FLOW:
	case IPV6_FLOW:
	case SCTP_V4_FLOW:
	case SCTP_V6_FLOW:
	case AH_ESP_V4_FLOW:
	case AH_ESP_V6_FLOW:
	case AH_V4_FLOW:
	case AH_V6_FLOW:
	case ESP_V4_FLOW:
	case ESP_V6_FLOW:
		if (priv->keygen_in_use)
			cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		break;
	default:
		cmd->data = 0;
		break;
	}

	return 0;
}