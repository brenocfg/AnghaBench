#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  vlan_tci; } ;
struct TYPE_3__ {int vlan_tci; int /*<<< orphan*/  h_dest; } ;
struct ethtool_rx_flow_spec {int flow_type; TYPE_2__ h_ext; TYPE_1__ m_ext; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHER_FLOW 134 
 int /*<<< orphan*/  ETH_ALEN ; 
 int FLOW_EXT ; 
 int FLOW_MAC_EXT ; 
#define  IPV6_USER_FLOW 133 
#define  IP_USER_FLOW 132 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int /*<<< orphan*/  VLAN_VID_MASK ; 
 int cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mask_spec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outer_headers ; 
 int /*<<< orphan*/  parse_ether (void*,void*,struct ethtool_rx_flow_spec*) ; 
 int /*<<< orphan*/  parse_ip4 (void*,void*,struct ethtool_rx_flow_spec*) ; 
 int /*<<< orphan*/  parse_ip6 (void*,void*,struct ethtool_rx_flow_spec*) ; 
 int /*<<< orphan*/  parse_tcp4 (void*,void*,struct ethtool_rx_flow_spec*) ; 
 int /*<<< orphan*/  parse_tcp6 (void*,void*,struct ethtool_rx_flow_spec*) ; 
 int /*<<< orphan*/  parse_udp4 (void*,void*,struct ethtool_rx_flow_spec*) ; 
 int /*<<< orphan*/  parse_udp6 (void*,void*,struct ethtool_rx_flow_spec*) ; 
 int /*<<< orphan*/  set_cvlan (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dmac (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_flow_attrs(u32 *match_c, u32 *match_v,
			  struct ethtool_rx_flow_spec *fs)
{
	void *outer_headers_c = MLX5_ADDR_OF(fte_match_param, match_c,
					     outer_headers);
	void *outer_headers_v = MLX5_ADDR_OF(fte_match_param, match_v,
					     outer_headers);
	u32 flow_type = fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT);

	switch (flow_type) {
	case TCP_V4_FLOW:
		parse_tcp4(outer_headers_c, outer_headers_v, fs);
		break;
	case UDP_V4_FLOW:
		parse_udp4(outer_headers_c, outer_headers_v, fs);
		break;
	case IP_USER_FLOW:
		parse_ip4(outer_headers_c, outer_headers_v, fs);
		break;
	case TCP_V6_FLOW:
		parse_tcp6(outer_headers_c, outer_headers_v, fs);
		break;
	case UDP_V6_FLOW:
		parse_udp6(outer_headers_c, outer_headers_v, fs);
		break;
	case IPV6_USER_FLOW:
		parse_ip6(outer_headers_c, outer_headers_v, fs);
		break;
	case ETHER_FLOW:
		parse_ether(outer_headers_c, outer_headers_v, fs);
		break;
	default:
		return -EINVAL;
	}

	if ((fs->flow_type & FLOW_EXT) &&
	    (fs->m_ext.vlan_tci & cpu_to_be16(VLAN_VID_MASK)))
		set_cvlan(outer_headers_c, outer_headers_v, fs->h_ext.vlan_tci);

	if (fs->flow_type & FLOW_MAC_EXT &&
	    !is_zero_ether_addr(fs->m_ext.h_dest)) {
		mask_spec(fs->m_ext.h_dest, fs->h_ext.h_dest, ETH_ALEN);
		set_dmac(outer_headers_c, outer_headers_v, fs->m_ext.h_dest,
			 fs->h_ext.h_dest);
	}

	return 0;
}