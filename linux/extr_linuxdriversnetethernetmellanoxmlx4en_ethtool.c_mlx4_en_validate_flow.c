#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ethtool_usrip4_spec {int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; int /*<<< orphan*/  proto; int /*<<< orphan*/  tos; int /*<<< orphan*/  l4_4_bytes; } ;
struct ethtool_tcpip4_spec {int /*<<< orphan*/  pdst; int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip4dst; int /*<<< orphan*/  ip4src; int /*<<< orphan*/  tos; } ;
struct TYPE_11__ {int /*<<< orphan*/  vlan_tci; } ;
struct TYPE_10__ {int vlan_tci; scalar_t__ vlan_etype; int /*<<< orphan*/  h_dest; } ;
struct ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_dest; int /*<<< orphan*/  h_source; } ;
struct TYPE_9__ {struct ethhdr ether_spec; struct ethtool_usrip4_spec usr_ip4_spec; struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct TYPE_7__ {int /*<<< orphan*/  ip_ver; } ;
struct TYPE_8__ {TYPE_1__ usr_ip4_spec; } ;
struct TYPE_12__ {scalar_t__ location; int flow_type; TYPE_5__ h_ext; TYPE_4__ m_ext; TYPE_3__ m_u; TYPE_2__ h_u; } ;
struct ethtool_rxnfc {TYPE_6__ fs; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETHER_FLOW 131 
 int /*<<< orphan*/  ETH_RX_NFC_IP4 ; 
 int FLOW_EXT ; 
 int FLOW_MAC_EXT ; 
#define  IP_USER_FLOW 130 
 scalar_t__ MAX_NUM_OF_FS_RULES ; 
#define  TCP_V4_FLOW 129 
#define  UDP_V4_FLOW 128 
 scalar_t__ VLAN_N_VID ; 
 int /*<<< orphan*/  VLAN_VID_MASK ; 
 int /*<<< orphan*/  all_zeros_or_all_ones (int /*<<< orphan*/ ) ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_en_validate_flow(struct net_device *dev,
				 struct ethtool_rxnfc *cmd)
{
	struct ethtool_usrip4_spec *l3_mask;
	struct ethtool_tcpip4_spec *l4_mask;
	struct ethhdr *eth_mask;

	if (cmd->fs.location >= MAX_NUM_OF_FS_RULES)
		return -EINVAL;

	if (cmd->fs.flow_type & FLOW_MAC_EXT) {
		/* dest mac mask must be ff:ff:ff:ff:ff:ff */
		if (!is_broadcast_ether_addr(cmd->fs.m_ext.h_dest))
			return -EINVAL;
	}

	switch (cmd->fs.flow_type & ~(FLOW_EXT | FLOW_MAC_EXT)) {
	case TCP_V4_FLOW:
	case UDP_V4_FLOW:
		if (cmd->fs.m_u.tcp_ip4_spec.tos)
			return -EINVAL;
		l4_mask = &cmd->fs.m_u.tcp_ip4_spec;
		/* don't allow mask which isn't all 0 or 1 */
		if (!all_zeros_or_all_ones(l4_mask->ip4src) ||
		    !all_zeros_or_all_ones(l4_mask->ip4dst) ||
		    !all_zeros_or_all_ones(l4_mask->psrc) ||
		    !all_zeros_or_all_ones(l4_mask->pdst))
			return -EINVAL;
		break;
	case IP_USER_FLOW:
		l3_mask = &cmd->fs.m_u.usr_ip4_spec;
		if (l3_mask->l4_4_bytes || l3_mask->tos || l3_mask->proto ||
		    cmd->fs.h_u.usr_ip4_spec.ip_ver != ETH_RX_NFC_IP4 ||
		    (!l3_mask->ip4src && !l3_mask->ip4dst) ||
		    !all_zeros_or_all_ones(l3_mask->ip4src) ||
		    !all_zeros_or_all_ones(l3_mask->ip4dst))
			return -EINVAL;
		break;
	case ETHER_FLOW:
		eth_mask = &cmd->fs.m_u.ether_spec;
		/* source mac mask must not be set */
		if (!is_zero_ether_addr(eth_mask->h_source))
			return -EINVAL;

		/* dest mac mask must be ff:ff:ff:ff:ff:ff */
		if (!is_broadcast_ether_addr(eth_mask->h_dest))
			return -EINVAL;

		if (!all_zeros_or_all_ones(eth_mask->h_proto))
			return -EINVAL;
		break;
	default:
		return -EINVAL;
	}

	if ((cmd->fs.flow_type & FLOW_EXT)) {
		if (cmd->fs.m_ext.vlan_etype ||
		    !((cmd->fs.m_ext.vlan_tci & cpu_to_be16(VLAN_VID_MASK)) ==
		      0 ||
		      (cmd->fs.m_ext.vlan_tci & cpu_to_be16(VLAN_VID_MASK)) ==
		      cpu_to_be16(VLAN_VID_MASK)))
			return -EINVAL;

		if (cmd->fs.m_ext.vlan_tci) {
			if (be16_to_cpu(cmd->fs.h_ext.vlan_tci) >= VLAN_N_VID)
				return -EINVAL;

		}
	}

	return 0;
}