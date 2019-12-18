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
struct gfar_private {int /*<<< orphan*/  ndev; } ;
struct TYPE_4__ {scalar_t__ ip_ver; } ;
struct TYPE_5__ {TYPE_1__ usr_ip4_spec; } ;
struct TYPE_6__ {int vlan_etype; int /*<<< orphan*/ * data; } ;
struct ethtool_rx_flow_spec {int flow_type; TYPE_2__ h_u; TYPE_3__ m_ext; } ;

/* Variables and functions */
 scalar_t__ ETH_RX_NFC_IP4 ; 
 int FLOW_EXT ; 
 int IP_USER_FLOW ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int gfar_check_capability(struct ethtool_rx_flow_spec *flow,
				 struct gfar_private *priv)
{

	if (flow->flow_type & FLOW_EXT)	{
		if (~flow->m_ext.data[0] || ~flow->m_ext.data[1])
			netdev_warn(priv->ndev,
				    "User-specific data not supported!\n");
		if (~flow->m_ext.vlan_etype)
			netdev_warn(priv->ndev,
				    "VLAN-etype not supported!\n");
	}
	if (flow->flow_type == IP_USER_FLOW)
		if (flow->h_u.usr_ip4_spec.ip_ver != ETH_RX_NFC_IP4)
			netdev_warn(priv->ndev,
				    "IP-Version differing from IPv4 not supported!\n");

	return 0;
}