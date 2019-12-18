#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_62__   TYPE_9__ ;
typedef  struct TYPE_61__   TYPE_8__ ;
typedef  struct TYPE_60__   TYPE_7__ ;
typedef  struct TYPE_59__   TYPE_6__ ;
typedef  struct TYPE_58__   TYPE_5__ ;
typedef  struct TYPE_57__   TYPE_4__ ;
typedef  struct TYPE_56__   TYPE_3__ ;
typedef  struct TYPE_55__   TYPE_31__ ;
typedef  struct TYPE_54__   TYPE_30__ ;
typedef  struct TYPE_53__   TYPE_2__ ;
typedef  struct TYPE_52__   TYPE_29__ ;
typedef  struct TYPE_51__   TYPE_28__ ;
typedef  struct TYPE_50__   TYPE_27__ ;
typedef  struct TYPE_49__   TYPE_26__ ;
typedef  struct TYPE_48__   TYPE_25__ ;
typedef  struct TYPE_47__   TYPE_24__ ;
typedef  struct TYPE_46__   TYPE_23__ ;
typedef  struct TYPE_45__   TYPE_22__ ;
typedef  struct TYPE_44__   TYPE_21__ ;
typedef  struct TYPE_43__   TYPE_20__ ;
typedef  struct TYPE_42__   TYPE_1__ ;
typedef  struct TYPE_41__   TYPE_19__ ;
typedef  struct TYPE_40__   TYPE_18__ ;
typedef  struct TYPE_39__   TYPE_17__ ;
typedef  struct TYPE_38__   TYPE_16__ ;
typedef  struct TYPE_37__   TYPE_15__ ;
typedef  struct TYPE_36__   TYPE_14__ ;
typedef  struct TYPE_35__   TYPE_13__ ;
typedef  struct TYPE_34__   TYPE_12__ ;
typedef  struct TYPE_33__   TYPE_11__ ;
typedef  struct TYPE_32__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_33__ {int /*<<< orphan*/ * mask; int /*<<< orphan*/ * value; } ;
struct TYPE_62__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  value; } ;
struct TYPE_34__ {TYPE_11__ pcp; TYPE_9__ vid; } ;
struct TYPE_60__ {scalar_t__ mask; scalar_t__ value; } ;
struct TYPE_58__ {scalar_t__ mask; scalar_t__ value; } ;
struct TYPE_53__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_42__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_56__ {TYPE_2__ mask; TYPE_1__ value; } ;
struct TYPE_51__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_49__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_52__ {TYPE_28__ mask; TYPE_26__ value; } ;
struct TYPE_43__ {int /*<<< orphan*/ * mask; int /*<<< orphan*/ * value; } ;
struct TYPE_54__ {TYPE_7__ dport; TYPE_5__ sport; TYPE_3__ dip; TYPE_29__ sip; TYPE_20__ proto; } ;
struct TYPE_45__ {int /*<<< orphan*/ * mask; int /*<<< orphan*/ * value; } ;
struct TYPE_46__ {TYPE_22__ proto; } ;
struct TYPE_39__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  value; } ;
struct TYPE_38__ {int /*<<< orphan*/  mask; int /*<<< orphan*/  value; } ;
struct TYPE_40__ {TYPE_17__ smac; TYPE_16__ dmac; } ;
struct TYPE_55__ {TYPE_30__ ipv4; TYPE_23__ ipv6; TYPE_18__ etype; } ;
struct ocelot_ace_rule {int /*<<< orphan*/  id; int /*<<< orphan*/  prio; TYPE_12__ vlan; int /*<<< orphan*/  type; TYPE_31__ frame; } ;
struct TYPE_36__ {struct flow_dissector* dissector; } ;
struct flow_rule {TYPE_14__ match; } ;
struct flow_match_vlan {TYPE_13__* mask; TYPE_10__* key; } ;
struct flow_match_ports {TYPE_8__* mask; TYPE_6__* key; } ;
struct flow_match_ipv4_addrs {TYPE_4__* mask; TYPE_27__* key; } ;
struct flow_match_eth_addrs {TYPE_19__* mask; TYPE_15__* key; } ;
struct flow_match_control {int dummy; } ;
struct flow_match_basic {TYPE_24__* mask; TYPE_21__* key; } ;
struct flow_dissector {int used_keys; } ;
struct TYPE_48__ {int /*<<< orphan*/  prio; int /*<<< orphan*/  protocol; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; TYPE_25__ common; } ;
struct TYPE_61__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_59__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_57__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_50__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_47__ {int /*<<< orphan*/  ip_proto; } ;
struct TYPE_44__ {int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_41__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_37__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_35__ {int /*<<< orphan*/  vlan_priority; int /*<<< orphan*/  vlan_id; } ;
struct TYPE_32__ {int /*<<< orphan*/  vlan_priority; int /*<<< orphan*/  vlan_id; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 scalar_t__ ETH_P_ARP ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_CONTROL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ETH_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_PORTS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_VLAN ; 
 int /*<<< orphan*/  OCELOT_ACE_TYPE_ANY ; 
 int /*<<< orphan*/  OCELOT_ACE_TYPE_ETYPE ; 
 int /*<<< orphan*/  OCELOT_ACE_TYPE_IPV4 ; 
 int /*<<< orphan*/  OCELOT_ACE_TYPE_IPV6 ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_basic (struct flow_rule*,struct flow_match_basic*) ; 
 int /*<<< orphan*/  flow_rule_match_control (struct flow_rule*,struct flow_match_control*) ; 
 int /*<<< orphan*/  flow_rule_match_eth_addrs (struct flow_rule*,struct flow_match_eth_addrs*) ; 
 int /*<<< orphan*/  flow_rule_match_ipv4_addrs (struct flow_rule*,struct flow_match_ipv4_addrs*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_rule_match_ports (struct flow_rule*,struct flow_match_ports*) ; 
 int /*<<< orphan*/  flow_rule_match_vlan (struct flow_rule*,struct flow_match_vlan*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int ocelot_flower_parse_action (struct flow_cls_offload*,struct ocelot_ace_rule*) ; 

__attribute__((used)) static int ocelot_flower_parse(struct flow_cls_offload *f,
			       struct ocelot_ace_rule *ocelot_rule)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(f);
	struct flow_dissector *dissector = rule->match.dissector;

	if (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS))) {
		return -EOPNOTSUPP;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) {
		struct flow_match_control match;

		flow_rule_match_control(rule, &match);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		struct flow_match_eth_addrs match;
		u16 proto = ntohs(f->common.protocol);

		/* The hw support mac matches only for MAC_ETYPE key,
		 * therefore if other matches(port, tcp flags, etc) are added
		 * then just bail out
		 */
		if ((dissector->used_keys &
		    (BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
		     BIT(FLOW_DISSECTOR_KEY_BASIC) |
		     BIT(FLOW_DISSECTOR_KEY_CONTROL))) !=
		    (BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
		     BIT(FLOW_DISSECTOR_KEY_BASIC) |
		     BIT(FLOW_DISSECTOR_KEY_CONTROL)))
			return -EOPNOTSUPP;

		if (proto == ETH_P_IP ||
		    proto == ETH_P_IPV6 ||
		    proto == ETH_P_ARP)
			return -EOPNOTSUPP;

		flow_rule_match_eth_addrs(rule, &match);
		ocelot_rule->type = OCELOT_ACE_TYPE_ETYPE;
		ether_addr_copy(ocelot_rule->frame.etype.dmac.value,
				match.key->dst);
		ether_addr_copy(ocelot_rule->frame.etype.smac.value,
				match.key->src);
		ether_addr_copy(ocelot_rule->frame.etype.dmac.mask,
				match.mask->dst);
		ether_addr_copy(ocelot_rule->frame.etype.smac.mask,
				match.mask->src);
		goto finished_key_parsing;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		if (ntohs(match.key->n_proto) == ETH_P_IP) {
			ocelot_rule->type = OCELOT_ACE_TYPE_IPV4;
			ocelot_rule->frame.ipv4.proto.value[0] =
				match.key->ip_proto;
			ocelot_rule->frame.ipv4.proto.mask[0] =
				match.mask->ip_proto;
		}
		if (ntohs(match.key->n_proto) == ETH_P_IPV6) {
			ocelot_rule->type = OCELOT_ACE_TYPE_IPV6;
			ocelot_rule->frame.ipv6.proto.value[0] =
				match.key->ip_proto;
			ocelot_rule->frame.ipv6.proto.mask[0] =
				match.mask->ip_proto;
		}
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS) &&
	    ntohs(f->common.protocol) == ETH_P_IP) {
		struct flow_match_ipv4_addrs match;
		u8 *tmp;

		flow_rule_match_ipv4_addrs(rule, &match);
		tmp = &ocelot_rule->frame.ipv4.sip.value.addr[0];
		memcpy(tmp, &match.key->src, 4);

		tmp = &ocelot_rule->frame.ipv4.sip.mask.addr[0];
		memcpy(tmp, &match.mask->src, 4);

		tmp = &ocelot_rule->frame.ipv4.dip.value.addr[0];
		memcpy(tmp, &match.key->dst, 4);

		tmp = &ocelot_rule->frame.ipv4.dip.mask.addr[0];
		memcpy(tmp, &match.mask->dst, 4);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS) &&
	    ntohs(f->common.protocol) == ETH_P_IPV6) {
		return -EOPNOTSUPP;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		ocelot_rule->frame.ipv4.sport.value = ntohs(match.key->src);
		ocelot_rule->frame.ipv4.sport.mask = ntohs(match.mask->src);
		ocelot_rule->frame.ipv4.dport.value = ntohs(match.key->dst);
		ocelot_rule->frame.ipv4.dport.mask = ntohs(match.mask->dst);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		ocelot_rule->type = OCELOT_ACE_TYPE_ANY;
		ocelot_rule->vlan.vid.value = match.key->vlan_id;
		ocelot_rule->vlan.vid.mask = match.mask->vlan_id;
		ocelot_rule->vlan.pcp.value[0] = match.key->vlan_priority;
		ocelot_rule->vlan.pcp.mask[0] = match.mask->vlan_priority;
	}

finished_key_parsing:
	ocelot_rule->prio = f->common.prio;
	ocelot_rule->id = f->cookie;
	return ocelot_flower_parse_action(f, ocelot_rule);
}