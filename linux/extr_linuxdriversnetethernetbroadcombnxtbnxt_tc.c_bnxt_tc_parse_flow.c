#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_48__   TYPE_9__ ;
typedef  struct TYPE_47__   TYPE_8__ ;
typedef  struct TYPE_46__   TYPE_7__ ;
typedef  struct TYPE_45__   TYPE_6__ ;
typedef  struct TYPE_44__   TYPE_5__ ;
typedef  struct TYPE_43__   TYPE_4__ ;
typedef  struct TYPE_42__   TYPE_3__ ;
typedef  struct TYPE_41__   TYPE_2__ ;
typedef  struct TYPE_40__   TYPE_24__ ;
typedef  struct TYPE_39__   TYPE_23__ ;
typedef  struct TYPE_38__   TYPE_22__ ;
typedef  struct TYPE_37__   TYPE_21__ ;
typedef  struct TYPE_36__   TYPE_20__ ;
typedef  struct TYPE_35__   TYPE_1__ ;
typedef  struct TYPE_34__   TYPE_19__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_17__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_15__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct tc_cls_flower_offload {int /*<<< orphan*/  exts; struct flow_dissector* dissector; } ;
struct flow_dissector_key_vlan {int /*<<< orphan*/  vlan_priority; int /*<<< orphan*/  vlan_id; } ;
struct flow_dissector_key_ports {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_keyid {int /*<<< orphan*/  keyid; } ;
struct flow_dissector_key_ipv6_addrs {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_ipv4_addrs {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_icmp {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct flow_dissector_key_eth_addrs {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_control {int /*<<< orphan*/  addr_type; } ;
struct flow_dissector_key_basic {scalar_t__ n_proto; int /*<<< orphan*/  ip_proto; } ;
struct flow_dissector {int used_keys; } ;
struct TYPE_32__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_33__ {TYPE_17__ ipv4; } ;
struct TYPE_36__ {int /*<<< orphan*/  tp_src; int /*<<< orphan*/  tp_dst; void* tun_id; TYPE_18__ u; } ;
struct TYPE_30__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_31__ {TYPE_15__ ipv4; } ;
struct TYPE_34__ {int /*<<< orphan*/  tp_src; int /*<<< orphan*/  tp_dst; void* tun_id; TYPE_16__ u; } ;
struct TYPE_29__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct TYPE_27__ {int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; } ;
struct TYPE_38__ {TYPE_14__ icmp; TYPE_12__ ports; int /*<<< orphan*/  ip_proto; } ;
struct TYPE_28__ {int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct TYPE_26__ {int /*<<< orphan*/  sport; int /*<<< orphan*/  dport; } ;
struct TYPE_37__ {TYPE_13__ icmp; TYPE_11__ ports; int /*<<< orphan*/  ip_proto; } ;
struct TYPE_48__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_44__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_41__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_45__ {TYPE_5__ saddr; TYPE_2__ daddr; } ;
struct TYPE_25__ {TYPE_9__ ipv6; TYPE_6__ ipv4; } ;
struct TYPE_46__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_42__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_35__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_43__ {TYPE_3__ saddr; TYPE_1__ daddr; } ;
struct TYPE_47__ {TYPE_7__ ipv6; TYPE_4__ ipv4; } ;
struct TYPE_40__ {scalar_t__ ether_type; int num_vlans; scalar_t__ inner_vlan_tpid; void* inner_vlan_tci; int /*<<< orphan*/  smac; int /*<<< orphan*/  dmac; } ;
struct TYPE_39__ {scalar_t__ ether_type; scalar_t__ inner_vlan_tpid; void* inner_vlan_tci; int /*<<< orphan*/  smac; int /*<<< orphan*/  dmac; } ;
struct bnxt_tc_flow {int /*<<< orphan*/  actions; TYPE_20__ tun_mask; TYPE_19__ tun_key; int /*<<< orphan*/  flags; TYPE_22__ l4_mask; TYPE_21__ l4_key; TYPE_10__ l3_mask; TYPE_8__ l3_key; TYPE_24__ l2_key; TYPE_23__ l2_mask; } ;
struct bnxt {int /*<<< orphan*/  dev; } ;

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
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_CONTROL ; 
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
 void* GET_KEY (struct tc_cls_flower_offload*,int /*<<< orphan*/ ) ; 
 void* GET_MASK (struct tc_cls_flower_offload*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLAN_TCI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnxt_tc_parse_actions (struct bnxt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ dissector_uses_key (struct flow_dissector*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int) ; 
 void* key32_to_tunnel_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int bnxt_tc_parse_flow(struct bnxt *bp,
			      struct tc_cls_flower_offload *tc_flow_cmd,
			      struct bnxt_tc_flow *flow)
{
	struct flow_dissector *dissector = tc_flow_cmd->dissector;
	u16 addr_type = 0;

	/* KEY_CONTROL and KEY_BASIC are needed for forming a meaningful key */
	if ((dissector->used_keys & BIT(FLOW_DISSECTOR_KEY_CONTROL)) == 0 ||
	    (dissector->used_keys & BIT(FLOW_DISSECTOR_KEY_BASIC)) == 0) {
		netdev_info(bp->dev, "cannot form TC key: used_keys = 0x%x",
			    dissector->used_keys);
		return -EOPNOTSUPP;
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_CONTROL)) {
		struct flow_dissector_key_control *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_CONTROL);

		addr_type = key->addr_type;
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_dissector_key_basic *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_BASIC);
		struct flow_dissector_key_basic *mask =
			GET_MASK(tc_flow_cmd, FLOW_DISSECTOR_KEY_BASIC);

		flow->l2_key.ether_type = key->n_proto;
		flow->l2_mask.ether_type = mask->n_proto;

		if (key->n_proto == htons(ETH_P_IP) ||
		    key->n_proto == htons(ETH_P_IPV6)) {
			flow->l4_key.ip_proto = key->ip_proto;
			flow->l4_mask.ip_proto = mask->ip_proto;
		}
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		struct flow_dissector_key_eth_addrs *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_ETH_ADDRS);
		struct flow_dissector_key_eth_addrs *mask =
			GET_MASK(tc_flow_cmd, FLOW_DISSECTOR_KEY_ETH_ADDRS);

		flow->flags |= BNXT_TC_FLOW_FLAGS_ETH_ADDRS;
		ether_addr_copy(flow->l2_key.dmac, key->dst);
		ether_addr_copy(flow->l2_mask.dmac, mask->dst);
		ether_addr_copy(flow->l2_key.smac, key->src);
		ether_addr_copy(flow->l2_mask.smac, mask->src);
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_dissector_key_vlan *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_VLAN);
		struct flow_dissector_key_vlan *mask =
			GET_MASK(tc_flow_cmd, FLOW_DISSECTOR_KEY_VLAN);

		flow->l2_key.inner_vlan_tci =
		   cpu_to_be16(VLAN_TCI(key->vlan_id, key->vlan_priority));
		flow->l2_mask.inner_vlan_tci =
		   cpu_to_be16((VLAN_TCI(mask->vlan_id, mask->vlan_priority)));
		flow->l2_key.inner_vlan_tpid = htons(ETH_P_8021Q);
		flow->l2_mask.inner_vlan_tpid = htons(0xffff);
		flow->l2_key.num_vlans = 1;
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) {
		struct flow_dissector_key_ipv4_addrs *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_IPV4_ADDRS);
		struct flow_dissector_key_ipv4_addrs *mask =
			GET_MASK(tc_flow_cmd, FLOW_DISSECTOR_KEY_IPV4_ADDRS);

		flow->flags |= BNXT_TC_FLOW_FLAGS_IPV4_ADDRS;
		flow->l3_key.ipv4.daddr.s_addr = key->dst;
		flow->l3_mask.ipv4.daddr.s_addr = mask->dst;
		flow->l3_key.ipv4.saddr.s_addr = key->src;
		flow->l3_mask.ipv4.saddr.s_addr = mask->src;
	} else if (dissector_uses_key(dissector,
				      FLOW_DISSECTOR_KEY_IPV6_ADDRS)) {
		struct flow_dissector_key_ipv6_addrs *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_IPV6_ADDRS);
		struct flow_dissector_key_ipv6_addrs *mask =
			GET_MASK(tc_flow_cmd, FLOW_DISSECTOR_KEY_IPV6_ADDRS);

		flow->flags |= BNXT_TC_FLOW_FLAGS_IPV6_ADDRS;
		flow->l3_key.ipv6.daddr = key->dst;
		flow->l3_mask.ipv6.daddr = mask->dst;
		flow->l3_key.ipv6.saddr = key->src;
		flow->l3_mask.ipv6.saddr = mask->src;
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_dissector_key_ports *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_PORTS);
		struct flow_dissector_key_ports *mask =
			GET_MASK(tc_flow_cmd, FLOW_DISSECTOR_KEY_PORTS);

		flow->flags |= BNXT_TC_FLOW_FLAGS_PORTS;
		flow->l4_key.ports.dport = key->dst;
		flow->l4_mask.ports.dport = mask->dst;
		flow->l4_key.ports.sport = key->src;
		flow->l4_mask.ports.sport = mask->src;
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_ICMP)) {
		struct flow_dissector_key_icmp *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_ICMP);
		struct flow_dissector_key_icmp *mask =
			GET_MASK(tc_flow_cmd, FLOW_DISSECTOR_KEY_ICMP);

		flow->flags |= BNXT_TC_FLOW_FLAGS_ICMP;
		flow->l4_key.icmp.type = key->type;
		flow->l4_key.icmp.code = key->code;
		flow->l4_mask.icmp.type = mask->type;
		flow->l4_mask.icmp.code = mask->code;
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_ENC_CONTROL)) {
		struct flow_dissector_key_control *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_ENC_CONTROL);

		addr_type = key->addr_type;
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS)) {
		struct flow_dissector_key_ipv4_addrs *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS);
		struct flow_dissector_key_ipv4_addrs *mask =
				GET_MASK(tc_flow_cmd,
					 FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS);

		flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_IPV4_ADDRS;
		flow->tun_key.u.ipv4.dst = key->dst;
		flow->tun_mask.u.ipv4.dst = mask->dst;
		flow->tun_key.u.ipv4.src = key->src;
		flow->tun_mask.u.ipv4.src = mask->src;
	} else if (dissector_uses_key(dissector,
				      FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS)) {
		return -EOPNOTSUPP;
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		struct flow_dissector_key_keyid *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_ENC_KEYID);
		struct flow_dissector_key_keyid *mask =
			GET_MASK(tc_flow_cmd, FLOW_DISSECTOR_KEY_ENC_KEYID);

		flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_ID;
		flow->tun_key.tun_id = key32_to_tunnel_id(key->keyid);
		flow->tun_mask.tun_id = key32_to_tunnel_id(mask->keyid);
	}

	if (dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_ENC_PORTS)) {
		struct flow_dissector_key_ports *key =
			GET_KEY(tc_flow_cmd, FLOW_DISSECTOR_KEY_ENC_PORTS);
		struct flow_dissector_key_ports *mask =
			GET_MASK(tc_flow_cmd, FLOW_DISSECTOR_KEY_ENC_PORTS);

		flow->flags |= BNXT_TC_FLOW_FLAGS_TUNL_PORTS;
		flow->tun_key.tp_dst = key->dst;
		flow->tun_mask.tp_dst = mask->dst;
		flow->tun_key.tp_src = key->src;
		flow->tun_mask.tp_src = mask->src;
	}

	return bnxt_tc_parse_actions(bp, &flow->actions, tc_flow_cmd->exts);
}