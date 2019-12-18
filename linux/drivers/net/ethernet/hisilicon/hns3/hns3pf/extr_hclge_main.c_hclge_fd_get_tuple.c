#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_21__ {int ether_proto; int ip_proto; int /*<<< orphan*/  dst_mac; void* vlan_tag1; int /*<<< orphan*/  src_mac; void** dst_ip; void** src_ip; void* dst_port; void* src_port; int /*<<< orphan*/  ip_tos; } ;
struct TYPE_18__ {int /*<<< orphan*/  dst_mac; void* vlan_tag1; int /*<<< orphan*/  ip_proto; void* ether_proto; int /*<<< orphan*/  src_mac; void** dst_ip; void** src_ip; void* dst_port; void* src_port; int /*<<< orphan*/  ip_tos; } ;
struct hclge_fd_rule {TYPE_14__ tuples_mask; TYPE_11__ tuples; } ;
struct hclge_dev {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  vlan_tci; } ;
struct TYPE_32__ {int /*<<< orphan*/  h_dest; int /*<<< orphan*/  vlan_tci; } ;
struct TYPE_31__ {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
struct TYPE_29__ {int l4_proto; int /*<<< orphan*/  ip6dst; int /*<<< orphan*/  ip6src; } ;
struct TYPE_27__ {int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip6dst; int /*<<< orphan*/  ip6src; } ;
struct TYPE_25__ {int proto; int /*<<< orphan*/  tos; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_22__ {int /*<<< orphan*/  tos; int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_23__ {TYPE_8__ ether_spec; TYPE_6__ usr_ip6_spec; TYPE_4__ tcp_ip6_spec; TYPE_2__ usr_ip4_spec; TYPE_15__ tcp_ip4_spec; } ;
struct TYPE_30__ {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
struct TYPE_28__ {int /*<<< orphan*/  l4_proto; int /*<<< orphan*/  ip6dst; int /*<<< orphan*/  ip6src; } ;
struct TYPE_26__ {int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip6dst; int /*<<< orphan*/  ip6src; } ;
struct TYPE_24__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  tos; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_19__ {int /*<<< orphan*/  tos; int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; } ;
struct TYPE_20__ {TYPE_7__ ether_spec; TYPE_5__ usr_ip6_spec; TYPE_3__ tcp_ip6_spec; TYPE_1__ usr_ip4_spec; TYPE_12__ tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {int flow_type; TYPE_10__ m_ext; TYPE_9__ h_ext; TYPE_16__ m_u; TYPE_13__ h_u; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHER_FLOW 136 
 void* ETH_P_IP ; 
 void* ETH_P_IPV6 ; 
 int FLOW_EXT ; 
 int FLOW_MAC_EXT ; 
 int /*<<< orphan*/  IPPROTO_SCTP ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 size_t IPV4_INDEX ; 
 int /*<<< orphan*/  IPV6_SIZE ; 
#define  IPV6_USER_FLOW 135 
#define  IP_USER_FLOW 134 
#define  SCTP_V4_FLOW 133 
#define  SCTP_V6_FLOW 132 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu_array (void**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hclge_fd_get_tuple(struct hclge_dev *hdev,
			      struct ethtool_rx_flow_spec *fs,
			      struct hclge_fd_rule *rule)
{
	u32 flow_type = fs->flow_type & ~(FLOW_EXT | FLOW_MAC_EXT);

	switch (flow_type) {
	case SCTP_V4_FLOW:
	case TCP_V4_FLOW:
	case UDP_V4_FLOW:
		rule->tuples.src_ip[IPV4_INDEX] =
				be32_to_cpu(fs->h_u.tcp_ip4_spec.ip4src);
		rule->tuples_mask.src_ip[IPV4_INDEX] =
				be32_to_cpu(fs->m_u.tcp_ip4_spec.ip4src);

		rule->tuples.dst_ip[IPV4_INDEX] =
				be32_to_cpu(fs->h_u.tcp_ip4_spec.ip4dst);
		rule->tuples_mask.dst_ip[IPV4_INDEX] =
				be32_to_cpu(fs->m_u.tcp_ip4_spec.ip4dst);

		rule->tuples.src_port = be16_to_cpu(fs->h_u.tcp_ip4_spec.psrc);
		rule->tuples_mask.src_port =
				be16_to_cpu(fs->m_u.tcp_ip4_spec.psrc);

		rule->tuples.dst_port = be16_to_cpu(fs->h_u.tcp_ip4_spec.pdst);
		rule->tuples_mask.dst_port =
				be16_to_cpu(fs->m_u.tcp_ip4_spec.pdst);

		rule->tuples.ip_tos = fs->h_u.tcp_ip4_spec.tos;
		rule->tuples_mask.ip_tos = fs->m_u.tcp_ip4_spec.tos;

		rule->tuples.ether_proto = ETH_P_IP;
		rule->tuples_mask.ether_proto = 0xFFFF;

		break;
	case IP_USER_FLOW:
		rule->tuples.src_ip[IPV4_INDEX] =
				be32_to_cpu(fs->h_u.usr_ip4_spec.ip4src);
		rule->tuples_mask.src_ip[IPV4_INDEX] =
				be32_to_cpu(fs->m_u.usr_ip4_spec.ip4src);

		rule->tuples.dst_ip[IPV4_INDEX] =
				be32_to_cpu(fs->h_u.usr_ip4_spec.ip4dst);
		rule->tuples_mask.dst_ip[IPV4_INDEX] =
				be32_to_cpu(fs->m_u.usr_ip4_spec.ip4dst);

		rule->tuples.ip_tos = fs->h_u.usr_ip4_spec.tos;
		rule->tuples_mask.ip_tos = fs->m_u.usr_ip4_spec.tos;

		rule->tuples.ip_proto = fs->h_u.usr_ip4_spec.proto;
		rule->tuples_mask.ip_proto = fs->m_u.usr_ip4_spec.proto;

		rule->tuples.ether_proto = ETH_P_IP;
		rule->tuples_mask.ether_proto = 0xFFFF;

		break;
	case SCTP_V6_FLOW:
	case TCP_V6_FLOW:
	case UDP_V6_FLOW:
		be32_to_cpu_array(rule->tuples.src_ip,
				  fs->h_u.tcp_ip6_spec.ip6src, IPV6_SIZE);
		be32_to_cpu_array(rule->tuples_mask.src_ip,
				  fs->m_u.tcp_ip6_spec.ip6src, IPV6_SIZE);

		be32_to_cpu_array(rule->tuples.dst_ip,
				  fs->h_u.tcp_ip6_spec.ip6dst, IPV6_SIZE);
		be32_to_cpu_array(rule->tuples_mask.dst_ip,
				  fs->m_u.tcp_ip6_spec.ip6dst, IPV6_SIZE);

		rule->tuples.src_port = be16_to_cpu(fs->h_u.tcp_ip6_spec.psrc);
		rule->tuples_mask.src_port =
				be16_to_cpu(fs->m_u.tcp_ip6_spec.psrc);

		rule->tuples.dst_port = be16_to_cpu(fs->h_u.tcp_ip6_spec.pdst);
		rule->tuples_mask.dst_port =
				be16_to_cpu(fs->m_u.tcp_ip6_spec.pdst);

		rule->tuples.ether_proto = ETH_P_IPV6;
		rule->tuples_mask.ether_proto = 0xFFFF;

		break;
	case IPV6_USER_FLOW:
		be32_to_cpu_array(rule->tuples.src_ip,
				  fs->h_u.usr_ip6_spec.ip6src, IPV6_SIZE);
		be32_to_cpu_array(rule->tuples_mask.src_ip,
				  fs->m_u.usr_ip6_spec.ip6src, IPV6_SIZE);

		be32_to_cpu_array(rule->tuples.dst_ip,
				  fs->h_u.usr_ip6_spec.ip6dst, IPV6_SIZE);
		be32_to_cpu_array(rule->tuples_mask.dst_ip,
				  fs->m_u.usr_ip6_spec.ip6dst, IPV6_SIZE);

		rule->tuples.ip_proto = fs->h_u.usr_ip6_spec.l4_proto;
		rule->tuples_mask.ip_proto = fs->m_u.usr_ip6_spec.l4_proto;

		rule->tuples.ether_proto = ETH_P_IPV6;
		rule->tuples_mask.ether_proto = 0xFFFF;

		break;
	case ETHER_FLOW:
		ether_addr_copy(rule->tuples.src_mac,
				fs->h_u.ether_spec.h_source);
		ether_addr_copy(rule->tuples_mask.src_mac,
				fs->m_u.ether_spec.h_source);

		ether_addr_copy(rule->tuples.dst_mac,
				fs->h_u.ether_spec.h_dest);
		ether_addr_copy(rule->tuples_mask.dst_mac,
				fs->m_u.ether_spec.h_dest);

		rule->tuples.ether_proto =
				be16_to_cpu(fs->h_u.ether_spec.h_proto);
		rule->tuples_mask.ether_proto =
				be16_to_cpu(fs->m_u.ether_spec.h_proto);

		break;
	default:
		return -EOPNOTSUPP;
	}

	switch (flow_type) {
	case SCTP_V4_FLOW:
	case SCTP_V6_FLOW:
		rule->tuples.ip_proto = IPPROTO_SCTP;
		rule->tuples_mask.ip_proto = 0xFF;
		break;
	case TCP_V4_FLOW:
	case TCP_V6_FLOW:
		rule->tuples.ip_proto = IPPROTO_TCP;
		rule->tuples_mask.ip_proto = 0xFF;
		break;
	case UDP_V4_FLOW:
	case UDP_V6_FLOW:
		rule->tuples.ip_proto = IPPROTO_UDP;
		rule->tuples_mask.ip_proto = 0xFF;
		break;
	default:
		break;
	}

	if ((fs->flow_type & FLOW_EXT)) {
		rule->tuples.vlan_tag1 = be16_to_cpu(fs->h_ext.vlan_tci);
		rule->tuples_mask.vlan_tag1 = be16_to_cpu(fs->m_ext.vlan_tci);
	}

	if (fs->flow_type & FLOW_MAC_EXT) {
		ether_addr_copy(rule->tuples.dst_mac, fs->h_ext.h_dest);
		ether_addr_copy(rule->tuples_mask.dst_mac, fs->m_ext.h_dest);
	}

	return 0;
}