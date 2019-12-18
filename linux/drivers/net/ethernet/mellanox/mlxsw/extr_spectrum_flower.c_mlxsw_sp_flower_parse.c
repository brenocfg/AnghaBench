#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct mlxsw_sp_acl_rule_info {int egress_bind_blocker; } ;
struct mlxsw_sp_acl_block {int dummy; } ;
struct mlxsw_sp {TYPE_2__* bus_info; } ;
struct TYPE_14__ {struct flow_dissector* dissector; } ;
struct flow_rule {TYPE_1__ match; } ;
struct flow_match_vlan {TYPE_9__* mask; TYPE_8__* key; } ;
struct flow_match_eth_addrs {TYPE_7__* mask; TYPE_6__* key; } ;
struct flow_match_control {TYPE_3__* key; } ;
struct flow_match_basic {TYPE_5__* mask; TYPE_4__* key; } ;
struct flow_dissector {int used_keys; } ;
struct TYPE_13__ {int /*<<< orphan*/  extack; int /*<<< orphan*/  prio; } ;
struct flow_cls_offload {TYPE_11__ common; TYPE_10__* rule; } ;
struct TYPE_22__ {scalar_t__ vlan_id; scalar_t__ vlan_priority; } ;
struct TYPE_21__ {scalar_t__ vlan_id; scalar_t__ vlan_priority; } ;
struct TYPE_20__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_19__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_18__ {scalar_t__ ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_17__ {scalar_t__ ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_16__ {scalar_t__ addr_type; } ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int EOPNOTSUPP ; 
 scalar_t__ ETH_P_ALL ; 
 scalar_t__ FLOW_DISSECTOR_KEY_BASIC ; 
 scalar_t__ FLOW_DISSECTOR_KEY_CONTROL ; 
 scalar_t__ FLOW_DISSECTOR_KEY_ETH_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IP ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_META ; 
 scalar_t__ FLOW_DISSECTOR_KEY_PORTS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_TCP ; 
 scalar_t__ FLOW_DISSECTOR_KEY_VLAN ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DMAC_0_31 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_DMAC_32_47 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_ETHERTYPE ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_IP_PROTO ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_PCP ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SMAC_0_31 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_SMAC_32_47 ; 
 int /*<<< orphan*/  MLXSW_AFK_ELEMENT_VID ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_basic (struct flow_rule*,struct flow_match_basic*) ; 
 int /*<<< orphan*/  flow_rule_match_control (struct flow_rule*,struct flow_match_control*) ; 
 int /*<<< orphan*/  flow_rule_match_eth_addrs (struct flow_rule*,struct flow_match_eth_addrs*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,scalar_t__) ; 
 int /*<<< orphan*/  flow_rule_match_vlan (struct flow_rule*,struct flow_match_vlan*) ; 
 scalar_t__ mlxsw_sp_acl_block_is_egress_bound (struct mlxsw_sp_acl_block*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_keymask_buf (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_keymask_u32 (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_rulei_priority (struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_flower_parse_actions (struct mlxsw_sp*,struct mlxsw_sp_acl_block*,struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_flower_parse_ip (struct mlxsw_sp*,struct mlxsw_sp_acl_rule_info*,struct flow_cls_offload*,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_sp_flower_parse_ipv4 (struct mlxsw_sp_acl_rule_info*,struct flow_cls_offload*) ; 
 int /*<<< orphan*/  mlxsw_sp_flower_parse_ipv6 (struct mlxsw_sp_acl_rule_info*,struct flow_cls_offload*) ; 
 int mlxsw_sp_flower_parse_meta (struct mlxsw_sp_acl_rule_info*,struct flow_cls_offload*,struct mlxsw_sp_acl_block*) ; 
 int mlxsw_sp_flower_parse_ports (struct mlxsw_sp*,struct mlxsw_sp_acl_rule_info*,struct flow_cls_offload*,scalar_t__) ; 
 int mlxsw_sp_flower_parse_tcp (struct mlxsw_sp*,struct mlxsw_sp_acl_rule_info*,struct flow_cls_offload*,scalar_t__) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_flower_parse(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_acl_block *block,
				 struct mlxsw_sp_acl_rule_info *rulei,
				 struct flow_cls_offload *f)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(f);
	struct flow_dissector *dissector = rule->match.dissector;
	u16 n_proto_mask = 0;
	u16 n_proto_key = 0;
	u16 addr_type = 0;
	u8 ip_proto = 0;
	int err;

	if (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_META) |
	      BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_TCP) |
	      BIT(FLOW_DISSECTOR_KEY_IP) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN))) {
		dev_err(mlxsw_sp->bus_info->dev, "Unsupported key\n");
		NL_SET_ERR_MSG_MOD(f->common.extack, "Unsupported key");
		return -EOPNOTSUPP;
	}

	mlxsw_sp_acl_rulei_priority(rulei, f->common.prio);

	err = mlxsw_sp_flower_parse_meta(rulei, f, block);
	if (err)
		return err;

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) {
		struct flow_match_control match;

		flow_rule_match_control(rule, &match);
		addr_type = match.key->addr_type;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		n_proto_key = ntohs(match.key->n_proto);
		n_proto_mask = ntohs(match.mask->n_proto);

		if (n_proto_key == ETH_P_ALL) {
			n_proto_key = 0;
			n_proto_mask = 0;
		}
		mlxsw_sp_acl_rulei_keymask_u32(rulei,
					       MLXSW_AFK_ELEMENT_ETHERTYPE,
					       n_proto_key, n_proto_mask);

		ip_proto = match.key->ip_proto;
		mlxsw_sp_acl_rulei_keymask_u32(rulei,
					       MLXSW_AFK_ELEMENT_IP_PROTO,
					       match.key->ip_proto,
					       match.mask->ip_proto);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		struct flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		mlxsw_sp_acl_rulei_keymask_buf(rulei,
					       MLXSW_AFK_ELEMENT_DMAC_32_47,
					       match.key->dst,
					       match.mask->dst, 2);
		mlxsw_sp_acl_rulei_keymask_buf(rulei,
					       MLXSW_AFK_ELEMENT_DMAC_0_31,
					       match.key->dst + 2,
					       match.mask->dst + 2, 4);
		mlxsw_sp_acl_rulei_keymask_buf(rulei,
					       MLXSW_AFK_ELEMENT_SMAC_32_47,
					       match.key->src,
					       match.mask->src, 2);
		mlxsw_sp_acl_rulei_keymask_buf(rulei,
					       MLXSW_AFK_ELEMENT_SMAC_0_31,
					       match.key->src + 2,
					       match.mask->src + 2, 4);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		if (mlxsw_sp_acl_block_is_egress_bound(block)) {
			NL_SET_ERR_MSG_MOD(f->common.extack, "vlan_id key is not supported on egress");
			return -EOPNOTSUPP;
		}

		/* Forbid block with this rulei to be bound
		 * to egress in future.
		 */
		rulei->egress_bind_blocker = 1;

		if (match.mask->vlan_id != 0)
			mlxsw_sp_acl_rulei_keymask_u32(rulei,
						       MLXSW_AFK_ELEMENT_VID,
						       match.key->vlan_id,
						       match.mask->vlan_id);
		if (match.mask->vlan_priority != 0)
			mlxsw_sp_acl_rulei_keymask_u32(rulei,
						       MLXSW_AFK_ELEMENT_PCP,
						       match.key->vlan_priority,
						       match.mask->vlan_priority);
	}

	if (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS)
		mlxsw_sp_flower_parse_ipv4(rulei, f);

	if (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS)
		mlxsw_sp_flower_parse_ipv6(rulei, f);

	err = mlxsw_sp_flower_parse_ports(mlxsw_sp, rulei, f, ip_proto);
	if (err)
		return err;
	err = mlxsw_sp_flower_parse_tcp(mlxsw_sp, rulei, f, ip_proto);
	if (err)
		return err;

	err = mlxsw_sp_flower_parse_ip(mlxsw_sp, rulei, f, n_proto_key & n_proto_mask);
	if (err)
		return err;

	return mlxsw_sp_flower_parse_actions(mlxsw_sp, block, rulei,
					     &f->rule->action,
					     f->common.extack);
}