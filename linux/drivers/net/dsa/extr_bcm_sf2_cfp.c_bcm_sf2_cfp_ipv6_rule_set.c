#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct flow_match_ports {TYPE_12__* key; TYPE_7__* mask; } ;
struct flow_match_ipv6_addrs {TYPE_15__* mask; TYPE_11__* key; } ;
struct ethtool_rx_flow_spec_input {struct ethtool_rx_flow_spec* fs; } ;
struct TYPE_22__ {int /*<<< orphan*/ * data; } ;
struct ethtool_rx_flow_spec {int flow_type; unsigned int location; TYPE_1__ m_ext; } ;
struct ethtool_rx_flow_rule {int /*<<< orphan*/  rule; } ;
struct cfp_udf_layout {TYPE_8__* udfs; } ;
struct TYPE_23__ {int /*<<< orphan*/  used; int /*<<< orphan*/  unique; } ;
struct bcm_sf2_priv {TYPE_2__ cfp; int /*<<< orphan*/  num_cfp_rules; } ;
struct TYPE_30__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_29__ {int mask_value; int /*<<< orphan*/  slices; } ;
struct TYPE_28__ {int /*<<< orphan*/  src; } ;
struct TYPE_26__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_27__ {TYPE_5__ in6_u; } ;
struct TYPE_24__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_25__ {TYPE_3__ in6_u; } ;
struct TYPE_20__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_19__ {TYPE_14__ in6_u; } ;
struct TYPE_21__ {TYPE_13__ dst; TYPE_6__ src; } ;
struct TYPE_18__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_16__ {TYPE_9__ in6_u; } ;
struct TYPE_17__ {TYPE_10__ dst; TYPE_4__ src; } ;

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
 int IP_FRAG_SHIFT ; 
 scalar_t__ IS_ERR (struct ethtool_rx_flow_rule*) ; 
 int L3_FRAMING_SHIFT ; 
 int OP_SEL_WRITE ; 
 int PTR_ERR (struct ethtool_rx_flow_rule*) ; 
 unsigned int RX_CLS_LOC_ANY ; 
 unsigned int SLICE_NUM_MASK ; 
 int TCAM_SEL ; 
#define  TCP_V6_FLOW 129 
 unsigned int UDF_NUM_SLICES ; 
#define  UDP_V6_FLOW 128 
 int XCESS_ADDR_MASK ; 
 int bcm_sf2_cfp_act_pol_set (struct bcm_sf2_priv*,unsigned int,int,unsigned int,unsigned int,int) ; 
 int bcm_sf2_cfp_op (struct bcm_sf2_priv*,int) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_rule_addr_set (struct bcm_sf2_priv*,unsigned int) ; 
 unsigned int bcm_sf2_cfp_rule_size (struct bcm_sf2_priv*) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_slice_ipv6 (struct bcm_sf2_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  bcm_sf2_cfp_udf_set (struct bcm_sf2_priv*,struct cfp_udf_layout const*,unsigned int) ; 
 int bcm_sf2_get_num_udf_slices (int /*<<< orphan*/ ) ; 
 unsigned int bcm_sf2_get_slice_number (struct cfp_udf_layout const*,unsigned int) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int core_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_writel (struct bcm_sf2_priv*,int,int /*<<< orphan*/ ) ; 
 struct ethtool_rx_flow_rule* ethtool_rx_flow_rule_create (struct ethtool_rx_flow_spec_input*) ; 
 int /*<<< orphan*/  ethtool_rx_flow_rule_destroy (struct ethtool_rx_flow_rule*) ; 
 unsigned int find_first_zero_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_rule_match_ipv6_addrs (int /*<<< orphan*/ ,struct flow_match_ipv6_addrs*) ; 
 int /*<<< orphan*/  flow_rule_match_ports (int /*<<< orphan*/ ,struct flow_match_ports*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int udf_lower_bits (int) ; 
 struct cfp_udf_layout udf_tcpip6_layout ; 
 int udf_upper_bits (int) ; 

__attribute__((used)) static int bcm_sf2_cfp_ipv6_rule_set(struct bcm_sf2_priv *priv, int port,
				     unsigned int port_num,
				     unsigned int queue_num,
				     struct ethtool_rx_flow_spec *fs)
{
	struct ethtool_rx_flow_spec_input input = {};
	unsigned int slice_num, rule_index[2];
	const struct cfp_udf_layout *layout;
	struct ethtool_rx_flow_rule *flow;
	struct flow_match_ipv6_addrs ipv6;
	struct flow_match_ports ports;
	u8 ip_proto, ip_frag;
	int ret = 0;
	u8 num_udf;
	u32 reg;

	switch (fs->flow_type & ~FLOW_EXT) {
	case TCP_V6_FLOW:
		ip_proto = IPPROTO_TCP;
		break;
	case UDP_V6_FLOW:
		ip_proto = IPPROTO_UDP;
		break;
	default:
		return -EINVAL;
	}

	ip_frag = be32_to_cpu(fs->m_ext.data[0]);

	layout = &udf_tcpip6_layout;
	slice_num = bcm_sf2_get_slice_number(layout, 0);
	if (slice_num == UDF_NUM_SLICES)
		return -EINVAL;

	num_udf = bcm_sf2_get_num_udf_slices(layout->udfs[slice_num].slices);

	/* Negotiate two indexes, one for the second half which we are chained
	 * from, which is what we will return to user-space, and a second one
	 * which is used to store its first half. That first half does not
	 * allow any choice of placement, so it just needs to find the next
	 * available bit. We return the second half as fs->location because
	 * that helps with the rule lookup later on since the second half is
	 * chained from its first half, we can easily identify IPv6 CFP rules
	 * by looking whether they carry a CHAIN_ID.
	 *
	 * We also want the second half to have a lower rule_index than its
	 * first half because the HW search is by incrementing addresses.
	 */
	if (fs->location == RX_CLS_LOC_ANY)
		rule_index[1] = find_first_zero_bit(priv->cfp.used,
						    priv->num_cfp_rules);
	else
		rule_index[1] = fs->location;
	if (rule_index[1] > bcm_sf2_cfp_rule_size(priv))
		return -ENOSPC;

	/* Flag it as used (cleared on error path) such that we can immediately
	 * obtain a second one to chain from.
	 */
	set_bit(rule_index[1], priv->cfp.used);

	rule_index[0] = find_first_zero_bit(priv->cfp.used,
					    priv->num_cfp_rules);
	if (rule_index[0] > bcm_sf2_cfp_rule_size(priv)) {
		ret = -ENOSPC;
		goto out_err;
	}

	input.fs = fs;
	flow = ethtool_rx_flow_rule_create(&input);
	if (IS_ERR(flow)) {
		ret = PTR_ERR(flow);
		goto out_err;
	}
	flow_rule_match_ipv6_addrs(flow->rule, &ipv6);
	flow_rule_match_ports(flow->rule, &ports);

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
	reg = 1 << L3_FRAMING_SHIFT | ip_proto << IPPROTO_SHIFT |
		ip_frag << IP_FRAG_SHIFT | udf_upper_bits(num_udf);
	core_writel(priv, reg, CORE_CFP_DATA_PORT(6));

	/* Mask with the specific layout for IPv6 packets including
	 * UDF_Valid[8]
	 */
	reg = layout->udfs[slice_num].mask_value | udf_upper_bits(num_udf);
	core_writel(priv, reg, CORE_CFP_MASK_PORT(6));

	/* UDF_Valid[7:0]	[31:24]
	 * S-Tag		[23:8]
	 * C-Tag		[7:0]
	 */
	core_writel(priv, udf_lower_bits(num_udf) << 24, CORE_CFP_DATA_PORT(5));

	/* Mask all but valid UDFs */
	core_writel(priv, udf_lower_bits(num_udf) << 24, CORE_CFP_MASK_PORT(5));

	/* Slice the IPv6 source address and port */
	bcm_sf2_cfp_slice_ipv6(priv, ipv6.key->src.in6_u.u6_addr32,
			       ports.key->src, slice_num, false);
	bcm_sf2_cfp_slice_ipv6(priv, ipv6.mask->src.in6_u.u6_addr32,
			       ports.mask->src, SLICE_NUM_MASK, true);

	/* Insert into TCAM now because we need to insert a second rule */
	bcm_sf2_cfp_rule_addr_set(priv, rule_index[0]);

	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | TCAM_SEL);
	if (ret) {
		pr_err("TCAM entry at addr %d failed\n", rule_index[0]);
		goto out_err_flow_rule;
	}

	/* Insert into Action and policer RAMs now */
	ret = bcm_sf2_cfp_act_pol_set(priv, rule_index[0], port, port_num,
				      queue_num, false);
	if (ret)
		goto out_err_flow_rule;

	/* Now deal with the second slice to chain this rule */
	slice_num = bcm_sf2_get_slice_number(layout, slice_num + 1);
	if (slice_num == UDF_NUM_SLICES) {
		ret = -EINVAL;
		goto out_err_flow_rule;
	}

	num_udf = bcm_sf2_get_num_udf_slices(layout->udfs[slice_num].slices);

	/* Apply the UDF layout for this filter */
	bcm_sf2_cfp_udf_set(priv, layout, slice_num);

	/* Chained rule, source port match is coming from the rule we are
	 * chained from.
	 */
	core_writel(priv, 0, CORE_CFP_DATA_PORT(7));
	core_writel(priv, 0, CORE_CFP_MASK_PORT(7));

	/*
	 * CHAIN ID		[31:24] chain to previous slice
	 * Reserved		[23:20]
	 * UDF_Valid[11:8]	[19:16]
	 * UDF_Valid[7:0]	[15:8]
	 * UDF_n_D11		[7:0]
	 */
	reg = rule_index[0] << 24 | udf_upper_bits(num_udf) << 16 |
		udf_lower_bits(num_udf) << 8;
	core_writel(priv, reg, CORE_CFP_DATA_PORT(6));

	/* Mask all except chain ID, UDF Valid[8] and UDF Valid[7:0] */
	reg = XCESS_ADDR_MASK << 24 | udf_upper_bits(num_udf) << 16 |
		udf_lower_bits(num_udf) << 8;
	core_writel(priv, reg, CORE_CFP_MASK_PORT(6));

	/* Don't care */
	core_writel(priv, 0, CORE_CFP_DATA_PORT(5));

	/* Mask all */
	core_writel(priv, 0, CORE_CFP_MASK_PORT(5));

	bcm_sf2_cfp_slice_ipv6(priv, ipv6.key->dst.in6_u.u6_addr32,
			       ports.key->dst, slice_num, false);
	bcm_sf2_cfp_slice_ipv6(priv, ipv6.mask->dst.in6_u.u6_addr32,
			       ports.key->dst, SLICE_NUM_MASK, true);

	/* Insert into TCAM now */
	bcm_sf2_cfp_rule_addr_set(priv, rule_index[1]);

	ret = bcm_sf2_cfp_op(priv, OP_SEL_WRITE | TCAM_SEL);
	if (ret) {
		pr_err("TCAM entry at addr %d failed\n", rule_index[1]);
		goto out_err_flow_rule;
	}

	/* Insert into Action and policer RAMs now, set chain ID to
	 * the one we are chained to
	 */
	ret = bcm_sf2_cfp_act_pol_set(priv, rule_index[1], port, port_num,
				      queue_num, true);
	if (ret)
		goto out_err_flow_rule;

	/* Turn on CFP for this rule now */
	reg = core_readl(priv, CORE_CFP_CTL_REG);
	reg |= BIT(port);
	core_writel(priv, reg, CORE_CFP_CTL_REG);

	/* Flag the second half rule as being used now, return it as the
	 * location, and flag it as unique while dumping rules
	 */
	set_bit(rule_index[0], priv->cfp.used);
	set_bit(rule_index[1], priv->cfp.unique);
	fs->location = rule_index[1];

	return ret;

out_err_flow_rule:
	ethtool_rx_flow_rule_destroy(flow);
out_err:
	clear_bit(rule_index[1], priv->cfp.used);
	return ret;
}