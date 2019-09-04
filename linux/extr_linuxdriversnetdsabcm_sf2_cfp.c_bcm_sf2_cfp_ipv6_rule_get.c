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
struct ethtool_tcpip6_spec {int /*<<< orphan*/  psrc; int /*<<< orphan*/  ip6src; int /*<<< orphan*/  pdst; int /*<<< orphan*/  ip6dst; } ;
struct TYPE_4__ {struct ethtool_tcpip6_spec tcp_ip6_spec; } ;
struct TYPE_3__ {struct ethtool_tcpip6_spec tcp_ip6_spec; } ;
struct ethtool_rx_flow_spec {int /*<<< orphan*/  flow_type; TYPE_2__ m_u; TYPE_1__ h_u; } ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_CFP_DATA_PORT (int) ; 
 int EINVAL ; 
 int IPPROTO_MASK ; 
 int IPPROTO_SHIFT ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int OP_SEL_READ ; 
 int TCAM_SEL ; 
 int /*<<< orphan*/  TCP_V6_FLOW ; 
 int /*<<< orphan*/  UDP_V6_FLOW ; 
 int bcm_sf2_cfp_op (struct bcm_sf2_priv*,int) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_rule_addr_set (struct bcm_sf2_priv*,int) ; 
 int bcm_sf2_cfp_unslice_ipv6 (struct bcm_sf2_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm_sf2_cfp_ipv6_rule_get(struct bcm_sf2_priv *priv, int port,
				     struct ethtool_rx_flow_spec *fs,
				     u32 next_loc)
{
	struct ethtool_tcpip6_spec *v6_spec = NULL, *v6_m_spec = NULL;
	u32 reg;
	int ret;

	/* UDPv6 and TCPv6 both use ethtool_tcpip6_spec so we are fine
	 * assuming tcp_ip6_spec here being an union.
	 */
	v6_spec = &fs->h_u.tcp_ip6_spec;
	v6_m_spec = &fs->m_u.tcp_ip6_spec;

	/* Read the second half first */
	ret = bcm_sf2_cfp_unslice_ipv6(priv, v6_spec->ip6dst, &v6_spec->pdst,
				       false);
	if (ret)
		return ret;

	ret = bcm_sf2_cfp_unslice_ipv6(priv, v6_m_spec->ip6dst,
				       &v6_m_spec->pdst, true);
	if (ret)
		return ret;

	/* Read last to avoid next entry clobbering the results during search
	 * operations. We would not have the port enabled for this rule, so
	 * don't bother checking it.
	 */
	(void)core_readl(priv, CORE_CFP_DATA_PORT(7));

	/* The slice number is valid, so read the rule we are chained from now
	 * which is our first half.
	 */
	bcm_sf2_cfp_rule_addr_set(priv, next_loc);
	ret = bcm_sf2_cfp_op(priv, OP_SEL_READ | TCAM_SEL);
	if (ret)
		return ret;

	reg = core_readl(priv, CORE_CFP_DATA_PORT(6));

	switch ((reg & IPPROTO_MASK) >> IPPROTO_SHIFT) {
	case IPPROTO_TCP:
		fs->flow_type = TCP_V6_FLOW;
		break;
	case IPPROTO_UDP:
		fs->flow_type = UDP_V6_FLOW;
		break;
	default:
		return -EINVAL;
	}

	ret = bcm_sf2_cfp_unslice_ipv6(priv, v6_spec->ip6src, &v6_spec->psrc,
				       false);
	if (ret)
		return ret;

	return bcm_sf2_cfp_unslice_ipv6(priv, v6_m_spec->ip6src,
					&v6_m_spec->psrc, true);
}