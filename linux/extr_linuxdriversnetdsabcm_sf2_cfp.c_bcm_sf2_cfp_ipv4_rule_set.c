#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ethtool_tcpip4_spec {int tos; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {struct ethtool_tcpip4_spec udp_ip4_spec; struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct TYPE_6__ {struct ethtool_tcpip4_spec udp_ip4_spec; struct ethtool_tcpip4_spec tcp_ip4_spec; } ;
struct ethtool_rx_flow_spec {int flow_type; unsigned int location; TYPE_3__ m_ext; TYPE_2__ m_u; TYPE_1__ h_u; } ;
struct cfp_udf_layout {TYPE_4__* udfs; } ;
struct TYPE_10__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  used; } ;
struct bcm_sf2_priv {TYPE_5__ cfp; int /*<<< orphan*/  num_cfp_rules; } ;
struct TYPE_9__ {int mask_value; int /*<<< orphan*/  slices; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CORE_CFP_CTL_REG ; 
 int /*<<< orphan*/  CORE_CFP_DATA_PORT (int) ; 
 int /*<<< orphan*/  CORE_CFP_MASK_PORT (int) ; 
 int EINVAL ; 
 int ENOSPC ; 
 int FLOW_EXT ; 
 int IPPROTO_SHIFT ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int IPTOS_SHIFT ; 
 int IP_FRAG_SHIFT ; 
 int OP_SEL_WRITE ; 
 unsigned int RX_CLS_LOC_ANY ; 
 unsigned int SLICE_NUM_MASK ; 
 int TCAM_SEL ; 
#define  TCP_V4_FLOW 129 
 unsigned int UDF_NUM_SLICES ; 
#define  UDP_V4_FLOW 128 
 int bcm_sf2_cfp_act_pol_set (struct bcm_sf2_priv*,unsigned int,unsigned int,unsigned int,int) ; 
 int bcm_sf2_cfp_op (struct bcm_sf2_priv*,int) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_rule_addr_set (struct bcm_sf2_priv*,unsigned int) ; 
 unsigned int bcm_sf2_cfp_rule_size (struct bcm_sf2_priv*) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_slice_ipv4 (struct bcm_sf2_priv*,struct ethtool_tcpip4_spec*,unsigned int,int) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_udf_set (struct bcm_sf2_priv*,struct cfp_udf_layout const*,unsigned int) ; 
 int bcm_sf2_get_num_udf_slices (int /*<<< orphan*/ ) ; 
 unsigned int bcm_sf2_get_slice_number (struct cfp_udf_layout const*,int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int udf_lower_bits (int) ; 
 struct cfp_udf_layout udf_tcpip4_layout ; 
 int udf_upper_bits (int) ; 

__attribute__((used)) static int bcm_sf2_cfp_ipv4_rule_set(struct bcm_sf2_priv *priv, int port,
				     unsigned int port_num,
				     unsigned int queue_num,
				     struct ethtool_rx_flow_spec *fs)
{
	struct ethtool_tcpip4_spec *v4_spec, *v4_m_spec;
	const struct cfp_udf_layout *layout;
	unsigned int slice_num, rule_index;
	u8 ip_proto, ip_frag;
	u8 num_udf;
	u32 reg;
	int ret;

	switch (fs->flow_type & ~FLOW_EXT) {
	case TCP_V4_FLOW:
		ip_proto = IPPROTO_TCP;
		v4_spec = &fs->h_u.tcp_ip4_spec;
		v4_m_spec = &fs->m_u.tcp_ip4_spec;
		break;
	case UDP_V4_FLOW:
		ip_proto = IPPROTO_UDP;
		v4_spec = &fs->h_u.udp_ip4_spec;
		v4_m_spec = &fs->m_u.udp_ip4_spec;
		break;
	default:
		return -EINVAL;
	}

	ip_frag = be32_to_cpu(fs->m_ext.data[0]);

	/* Locate the first rule available */
	if (fs->location == RX_CLS_LOC_ANY)
		rule_index = find_first_zero_bit(priv->cfp.used,
						 priv->num_cfp_rules);
	else
		rule_index = fs->location;

	if (rule_index > bcm_sf2_cfp_rule_size(priv))
		return -ENOSPC;

	layout = &udf_tcpip4_layout;
	/* We only use one UDF slice for now */
	slice_num = bcm_sf2_get_slice_number(layout, 0);
	if (slice_num == UDF_NUM_SLICES)
		return -EINVAL;

	num_udf = bcm_sf2_get_num_udf_slices(layout->udfs[slice_num].slices);

	/* Apply the UDF layout for this filter */
	bcm_sf2_cfp_udf_set(priv, layout, slice_num);

	/* Apply to all packets received through this port */
	core_writel(priv, BIT(port), CORE_CFP_DATA_PORT(7));

	/* Source port map match */
	core_writel(priv, 0xff, CORE_CFP_MASK_PORT(7));

	/* S-Tag status		[31:30]
	 * C-Tag status		[29:28]
	 * L2 framing		[27:26]
	 * L3 framing		[25:24]
	 * IP ToS		[23:16]
	 * IP proto		[15:08]
	 * IP Fragm		[7]
	 * Non 1st frag		[6]
	 * IP Authen		[5]
	 * TTL range		[4:3]
	 * PPPoE session	[2]
	 * Reserved		[1]
	 * UDF_Valid[8]		[0]
	 */
	core_writel(priv, v4_spec->tos << IPTOS_SHIFT |
		    ip_proto << IPPROTO_SHIFT | ip_frag << IP_FRAG_SHIFT |
		    udf_upper_bits(num_udf),
		    CORE_CFP_DATA_PORT(6));

	/* Mask with the specific layout for IPv4 packets */
	core_writel(priv, layout->udfs[slice_num].mask_value |
		    udf_upper_bits(num_udf), CORE_CFP_MASK_PORT(6));

	/* UDF_Valid[7:0]	[31:24]
	 * S-Tag		[23:8]
	 * C-Tag		[7:0]
	 */
	core_writel(priv, udf_lower_bits(num_udf) << 24, CORE_CFP_DATA_PORT(5));

	/* Mask all but valid UDFs */
	core_writel(priv, udf_lower_bits(num_udf) << 24, CORE_CFP_MASK_PORT(5));

	/* Program the match and the mask */
	bcm_sf2_cfp_slice_ipv4(priv, v4_spec, slice_num, false);
	bcm_sf2_cfp_slice_ipv4(priv, v4_m_spec, SLICE_NUM_MASK, true);

	/* Insert into TCAM now */
	bcm_sf2_cfp_rule_addr_set(priv, rule_index);

	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | TCAM_SEL);
	if (ret) {
		pr_err("TCAM entry at addr %d failed\n", rule_index);
		return ret;
	}

	/* Insert into Action and policer RAMs now */
	ret = bcm_sf2_cfp_act_pol_set(priv, rule_index, port_num,
				      queue_num, true);
	if (ret)
		return ret;

	/* Turn on CFP for this rule now */
	reg = core_readl(priv, CORE_CFP_CTL_REG);
	reg |= BIT(port);
	core_writel(priv, reg, CORE_CFP_CTL_REG);

	/* Flag the rule as being used and return it */
	set_bit(rule_index, priv->cfp.used);
	set_bit(rule_index, priv->cfp.unique);
	fs->location = rule_index;

	return 0;
}