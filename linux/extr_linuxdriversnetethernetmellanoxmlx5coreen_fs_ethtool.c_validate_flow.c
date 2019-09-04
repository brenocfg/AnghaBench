#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ num_channels; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_2__ channels; } ;
struct TYPE_6__ {int /*<<< orphan*/  h_dest; } ;
struct ethtool_rx_flow_spec {scalar_t__ location; scalar_t__ ring_cookie; int flow_type; TYPE_3__ m_ext; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int ENOTSUPP ; 
#define  ETHER_FLOW 134 
 int FLOW_EXT ; 
 int FLOW_MAC_EXT ; 
#define  IPV6_USER_FLOW 133 
#define  IP_USER_FLOW 132 
 scalar_t__ MAX_NUM_OF_ETHTOOL_RULES ; 
 scalar_t__ RX_CLS_FLOW_DISC ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int validate_ethter (struct ethtool_rx_flow_spec*) ; 
 int validate_ip4 (struct ethtool_rx_flow_spec*) ; 
 int validate_ip6 (struct ethtool_rx_flow_spec*) ; 
 int validate_tcpudp4 (struct ethtool_rx_flow_spec*) ; 
 int validate_tcpudp6 (struct ethtool_rx_flow_spec*) ; 
 int validate_vlan (struct ethtool_rx_flow_spec*) ; 

__attribute__((used)) static int validate_flow(struct mlx5e_priv *priv,
			 struct ethtool_rx_flow_spec *fs)
{
	int num_tuples = 0;
	int ret = 0;

	if (fs->location >= MAX_NUM_OF_ETHTOOL_RULES)
		return -ENOSPC;

	if (fs->ring_cookie >= priv->channels.params.num_channels &&
	    fs->ring_cookie != RX_CLS_FLOW_DISC)
		return -EINVAL;

	switch (fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) {
	case ETHER_FLOW:
		num_tuples += validate_ethter(fs);
		break;
	case TCP_V4_FLOW:
	case UDP_V4_FLOW:
		ret = validate_tcpudp4(fs);
		if (ret < 0)
			return ret;
		num_tuples += ret;
		break;
	case IP_USER_FLOW:
		ret = validate_ip4(fs);
		if (ret < 0)
			return ret;
		num_tuples += ret;
		break;
	case TCP_V6_FLOW:
	case UDP_V6_FLOW:
		ret = validate_tcpudp6(fs);
		if (ret < 0)
			return ret;
		num_tuples += ret;
		break;
	case IPV6_USER_FLOW:
		ret = validate_ip6(fs);
		if (ret < 0)
			return ret;
		num_tuples += ret;
		break;
	default:
		return -ENOTSUPP;
	}
	if ((fs->flow_type & FLOW_EXT)) {
		ret = validate_vlan(fs);
		if (ret < 0)
			return ret;
		num_tuples += ret;
	}

	if (fs->flow_type & FLOW_MAC_EXT &&
	    !is_zero_ether_addr(fs->m_ext.h_dest))
		num_tuples++;

	return num_tuples;
}