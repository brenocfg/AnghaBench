#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_82__   TYPE_9__ ;
typedef  struct TYPE_81__   TYPE_8__ ;
typedef  struct TYPE_80__   TYPE_7__ ;
typedef  struct TYPE_79__   TYPE_6__ ;
typedef  struct TYPE_78__   TYPE_5__ ;
typedef  struct TYPE_77__   TYPE_4__ ;
typedef  struct TYPE_76__   TYPE_41__ ;
typedef  struct TYPE_75__   TYPE_40__ ;
typedef  struct TYPE_74__   TYPE_3__ ;
typedef  struct TYPE_73__   TYPE_39__ ;
typedef  struct TYPE_72__   TYPE_38__ ;
typedef  struct TYPE_71__   TYPE_37__ ;
typedef  struct TYPE_70__   TYPE_36__ ;
typedef  struct TYPE_69__   TYPE_35__ ;
typedef  struct TYPE_68__   TYPE_34__ ;
typedef  struct TYPE_67__   TYPE_33__ ;
typedef  struct TYPE_66__   TYPE_32__ ;
typedef  struct TYPE_65__   TYPE_31__ ;
typedef  struct TYPE_64__   TYPE_30__ ;
typedef  struct TYPE_63__   TYPE_2__ ;
typedef  struct TYPE_62__   TYPE_29__ ;
typedef  struct TYPE_61__   TYPE_28__ ;
typedef  struct TYPE_60__   TYPE_27__ ;
typedef  struct TYPE_59__   TYPE_26__ ;
typedef  struct TYPE_58__   TYPE_25__ ;
typedef  struct TYPE_57__   TYPE_24__ ;
typedef  struct TYPE_56__   TYPE_23__ ;
typedef  struct TYPE_55__   TYPE_22__ ;
typedef  struct TYPE_54__   TYPE_21__ ;
typedef  struct TYPE_53__   TYPE_20__ ;
typedef  struct TYPE_52__   TYPE_1__ ;
typedef  struct TYPE_51__   TYPE_19__ ;
typedef  struct TYPE_50__   TYPE_18__ ;
typedef  struct TYPE_49__   TYPE_17__ ;
typedef  struct TYPE_48__   TYPE_16__ ;
typedef  struct TYPE_47__   TYPE_15__ ;
typedef  struct TYPE_46__   TYPE_14__ ;
typedef  struct TYPE_45__   TYPE_13__ ;
typedef  struct TYPE_44__   TYPE_12__ ;
typedef  struct TYPE_43__   TYPE_11__ ;
typedef  struct TYPE_42__   TYPE_10__ ;

/* Type definitions */
struct TYPE_67__ {struct flow_dissector* dissector; } ;
struct flow_rule {int /*<<< orphan*/  action; TYPE_33__ match; } ;
struct flow_match_vlan {TYPE_2__* mask; TYPE_1__* key; } ;
struct flow_match_ports {TYPE_32__* mask; TYPE_30__* key; } ;
struct flow_match_ipv6_addrs {TYPE_14__* mask; TYPE_11__* key; } ;
struct flow_match_ipv4_addrs {TYPE_26__* mask; TYPE_23__* key; } ;
struct flow_match_icmp {TYPE_20__* mask; TYPE_18__* key; } ;
struct flow_match_eth_addrs {TYPE_40__* mask; TYPE_38__* key; } ;
struct flow_match_enc_keyid {TYPE_28__* mask; TYPE_27__* key; } ;
struct flow_match_basic {TYPE_37__* mask; TYPE_35__* key; } ;
struct flow_dissector {int used_keys; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_57__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_58__ {TYPE_24__ ipv4; } ;
struct TYPE_65__ {int /*<<< orphan*/  tp_src; int /*<<< orphan*/  tp_dst; void* tun_id; TYPE_25__ u; } ;
struct TYPE_54__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_55__ {TYPE_21__ ipv4; } ;
struct TYPE_62__ {int /*<<< orphan*/  tp_src; int /*<<< orphan*/  tp_dst; void* tun_id; TYPE_22__ u; } ;
struct TYPE_51__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct TYPE_48__ {int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; } ;
struct TYPE_70__ {TYPE_19__ icmp; TYPE_16__ ports; int /*<<< orphan*/  ip_proto; } ;
struct TYPE_49__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct TYPE_47__ {int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; } ;
struct TYPE_68__ {TYPE_17__ icmp; TYPE_15__ ports; int /*<<< orphan*/  ip_proto; } ;
struct TYPE_44__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_80__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_77__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_81__ {TYPE_7__ saddr; TYPE_4__ daddr; } ;
struct TYPE_45__ {TYPE_12__ ipv6; TYPE_8__ ipv4; } ;
struct TYPE_82__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_78__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_74__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_79__ {TYPE_5__ saddr; TYPE_3__ daddr; } ;
struct TYPE_42__ {TYPE_9__ ipv6; TYPE_6__ ipv4; } ;
struct TYPE_76__ {scalar_t__ ether_type; int num_vlans; scalar_t__ inner_vlan_tpid; void* inner_vlan_tci; int /*<<< orphan*/  smac; int /*<<< orphan*/  dmac; } ;
struct TYPE_73__ {scalar_t__ inner_vlan_tpid; void* inner_vlan_tci; int /*<<< orphan*/  smac; int /*<<< orphan*/  dmac; int /*<<< orphan*/  ether_type; } ;
struct bnxt_tc_flow {int /*<<< orphan*/  actions; TYPE_31__ tun_mask; TYPE_29__ tun_key; int /*<<< orphan*/  flags; TYPE_36__ l4_mask; TYPE_34__ l4_key; TYPE_13__ l3_mask; TYPE_10__ l3_key; TYPE_41__ l2_key; TYPE_39__ l2_mask; } ;
struct bnxt {int /*<<< orphan*/  dev; } ;
struct TYPE_75__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_72__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_71__ {int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_69__ {scalar_t__ n_proto; int /*<<< orphan*/  ip_proto; } ;
struct TYPE_66__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_64__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_63__ {int /*<<< orphan*/  vlan_priority; int /*<<< orphan*/  vlan_id; } ;
struct TYPE_61__ {int /*<<< orphan*/  keyid; } ;
struct TYPE_60__ {int /*<<< orphan*/  keyid; } ;
struct TYPE_59__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_56__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_53__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct TYPE_52__ {int /*<<< orphan*/  vlan_priority; int /*<<< orphan*/  vlan_id; } ;
struct TYPE_50__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct TYPE_46__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_43__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNXT_TC_FLOW_FLAGS_ETH_ADDRS ; 
 int /*<<< orphan*/  BNXT_TC_FLOW_FLAGS_ICMP ; 
 int /*<<< orphan*/  BNXT_TC_FLOW_FLAGS_IPV4_ADDRS ; 
 int /*<<< orphan*/  BNXT_TC_FLOW_FLAGS_IPV6_ADDRS ; 
 int /*<<< orphan*/  BNXT_TC_FLOW_FLAGS_PORTS ; 
 int /*<<< orphan*/  BNXT_TC_FLOW_FLAGS_TUNL_ID ; 
 int /*<<< orphan*/  BNXT_TC_FLOW_FLAGS_TUNL_IPV4_ADDRS ; 
 int /*<<< orphan*/  BNXT_TC_FLOW_FLAGS_TUNL_PORTS ; 
 int EOPNOTSUPP ; 
 int ETH_P_8021Q ; 
 int ETH_P_IP ; 
 int ETH_P_IPV6 ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_CONTROL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_KEYID ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_PORTS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ETH_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ICMP ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_PORTS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_VLAN ; 
 int /*<<< orphan*/  VLAN_TCI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnxt_tc_parse_actions (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_basic (struct flow_rule*,struct flow_match_basic*) ; 
 int /*<<< orphan*/  flow_rule_match_enc_ipv4_addrs (struct flow_rule*,struct flow_match_ipv4_addrs*) ; 
 int /*<<< orphan*/  flow_rule_match_enc_keyid (struct flow_rule*,struct flow_match_enc_keyid*) ; 
 int /*<<< orphan*/  flow_rule_match_enc_ports (struct flow_rule*,struct flow_match_ports*) ; 
 int /*<<< orphan*/  flow_rule_match_eth_addrs (struct flow_rule*,struct flow_match_eth_addrs*) ; 
 int /*<<< orphan*/  flow_rule_match_icmp (struct flow_rule*,struct flow_match_icmp*) ; 
 int /*<<< orphan*/  flow_rule_match_ipv4_addrs (struct flow_rule*,struct flow_match_ipv4_addrs*) ; 
 int /*<<< orphan*/  flow_rule_match_ipv6_addrs (struct flow_rule*,struct flow_match_ipv6_addrs*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_rule_match_ports (struct flow_rule*,struct flow_match_ports*) ; 
 int /*<<< orphan*/  flow_rule_match_vlan (struct flow_rule*,struct flow_match_vlan*) ; 
 scalar_t__ htons (int) ; 
 void* key32_to_tunnel_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bnxt_tc_parse_flow(struct bnxt *bp,
			      struct flow_cls_offload *tc_flow_cmd,
			      struct bnxt_tc_flow *flow)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(tc_flow_cmd);
	struct flow_dissector *dissector = rule->match.dissector;

	/* KEY_CONTROL and KEY_BASIC are needed for forming a meaningful key */
	if ((dissector->used_keys & BIT(FLOW_DISSECTOR_KEY_CONTROL)) == 0 ||
	    (dissector->used_keys & BIT(FLOW_DISSECTOR_KEY_BASIC)) == 0) {
		netdev_info(bp->dev, "cannot form TC key: used_keys = 0x%x",
			    dissector->used_keys);
		return -EOPNOTSUPP;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		flow->l2_key.ether_type = match.key->n_proto;
		flow->l2_mask.ether_type = match.mask->n_proto;

		if (match.key->n_proto == htons(ETH_P_IP) ||
		    match.key->n_proto == htons(ETH_P_IPV6)) {
			flow->l4_key.ip_proto = match.key->ip_proto;
			flow->l4_mask.ip_proto = match.mask->ip_proto;
		}
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		struct flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_ETH_ADDRS;
		ether_addr_copy(flow->l2_key.dmac, match.key->dst);
		ether_addr_copy(flow->l2_mask.dmac, match.mask->dst);
		ether_addr_copy(flow->l2_key.smac, match.key->src);
		ether_addr_copy(flow->l2_mask.smac, match.mask->src);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		flow->l2_key.inner_vlan_tci =
			cpu_to_be16(VLAN_TCI(match.key->vlan_id,
					     match.key->vlan_priority));
		flow->l2_mask.inner_vlan_tci =
			cpu_to_be16((VLAN_TCI(match.mask->vlan_id,
					      match.mask->vlan_priority)));
		flow->l2_key.inner_vlan_tpid = htons(ETH_P_8021Q);
		flow->l2_mask.inner_vlan_tpid = htons(0xffff);
		flow->l2_key.num_vlans = 1;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) {
		struct flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_IPV4_ADDRS;
		flow->l3_key.ipv4.daddr.s_addr = match.key->dst;
		flow->l3_mask.ipv4.daddr.s_addr = match.mask->dst;
		flow->l3_key.ipv4.saddr.s_addr = match.key->src;
		flow->l3_mask.ipv4.saddr.s_addr = match.mask->src;
	} else if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS)) {
		struct flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_IPV6_ADDRS;
		flow->l3_key.ipv6.daddr = match.key->dst;
		flow->l3_mask.ipv6.daddr = match.mask->dst;
		flow->l3_key.ipv6.saddr = match.key->src;
		flow->l3_mask.ipv6.saddr = match.mask->src;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_PORTS;
		flow->l4_key.ports.dport = match.key->dst;
		flow->l4_mask.ports.dport = match.mask->dst;
		flow->l4_key.ports.sport = match.key->src;
		flow->l4_mask.ports.sport = match.mask->src;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ICMP)) {
		struct flow_match_icmp match;

		flow_rule_match_icmp(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_ICMP;
		flow->l4_key.icmp.type = match.key->type;
		flow->l4_key.icmp.code = match.key->code;
		flow->l4_mask.icmp.type = match.mask->type;
		flow->l4_mask.icmp.code = match.mask->code;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS)) {
		struct flow_match_ipv4_addrs match;

		flow_rule_match_enc_ipv4_addrs(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_IPV4_ADDRS;
		flow->tun_key.u.ipv4.dst = match.key->dst;
		flow->tun_mask.u.ipv4.dst = match.mask->dst;
		flow->tun_key.u.ipv4.src = match.key->src;
		flow->tun_mask.u.ipv4.src = match.mask->src;
	} else if (flow_rule_match_key(rule,
				      FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS)) {
		return -EOPNOTSUPP;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		struct flow_match_enc_keyid match;

		flow_rule_match_enc_keyid(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_ID;
		flow->tun_key.tun_id = key32_to_tunnel_id(match.key->keyid);
		flow->tun_mask.tun_id = key32_to_tunnel_id(match.mask->keyid);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_PORTS)) {
		struct flow_match_ports match;

		flow_rule_match_enc_ports(rule, &match);
		flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_PORTS;
		flow->tun_key.tp_dst = match.key->dst;
		flow->tun_mask.tp_dst = match.mask->dst;
		flow->tun_key.tp_src = match.key->src;
		flow->tun_mask.tp_src = match.mask->src;
	}

	return bnxt_tc_parse_actions(bp, &flow->actions, &rule->action);
}