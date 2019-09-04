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
typedef  int u32 ;
struct ethtool_tcpip4_spec {int tos; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {struct ethtool_tcpip4_spec udp_ip4_spec; struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct TYPE_4__ {struct ethtool_tcpip4_spec udp_ip4_spec; struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {TYPE_3__ m_ext; TYPE_2__ m_u; TYPE_1__ h_u; int /*<<< orphan*/  flow_type; } ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_CFP_DATA_PORT (int) ; 
 int EINVAL ; 
 int IPPROTO_MASK ; 
 int IPPROTO_SHIFT ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int IPTOS_MASK ; 
 int IPTOS_SHIFT ; 
 int IP_FRAG_SHIFT ; 
 int /*<<< orphan*/  TCP_V4_FLOW ; 
 int /*<<< orphan*/  UDP_V4_FLOW ; 
 int bcm_sf2_cfp_unslice_ipv4 (struct bcm_sf2_priv*,struct ethtool_tcpip4_spec*,int) ; 
 int core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static int bcm_sf2_cfp_ipv4_rule_get(struct bcm_sf2_priv *priv, int port,
				     struct ethtool_rx_flow_spec *fs)
{
	struct ethtool_tcpip4_spec *v4_spec = NULL, *v4_m_spec = NULL;
	u32 reg;
	int ret;

	reg = core_readl(priv, CORE_CFP_DATA_PORT(6));

	switch ((reg & IPPROTO_MASK) >> IPPROTO_SHIFT) {
	case IPPROTO_TCP:
		fs->flow_type = TCP_V4_FLOW;
		v4_spec = &fs->h_u.tcp_ip4_spec;
		v4_m_spec = &fs->m_u.tcp_ip4_spec;
		break;
	case IPPROTO_UDP:
		fs->flow_type = UDP_V4_FLOW;
		v4_spec = &fs->h_u.udp_ip4_spec;
		v4_m_spec = &fs->m_u.udp_ip4_spec;
		break;
	default:
		return -EINVAL;
	}

	fs->m_ext.data[0] = cpu_to_be32((reg >> IP_FRAG_SHIFT) & 1);
	v4_spec->tos = (reg >> IPTOS_SHIFT) & IPTOS_MASK;

	ret = bcm_sf2_cfp_unslice_ipv4(priv, v4_spec, false);
	if (ret)
		return ret;

	return bcm_sf2_cfp_unslice_ipv4(priv, v4_m_spec, true);
}