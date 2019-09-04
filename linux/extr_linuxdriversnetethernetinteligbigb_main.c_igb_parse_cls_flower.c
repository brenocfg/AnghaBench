#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct netlink_ext_ack* extack; } ;
struct tc_cls_flower_offload {int /*<<< orphan*/  cookie; int /*<<< orphan*/  mask; TYPE_3__* dissector; int /*<<< orphan*/  key; TYPE_1__ common; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_6__ {scalar_t__ etype; scalar_t__ vlan_tci; int /*<<< orphan*/  match_flags; int /*<<< orphan*/  src_addr; int /*<<< orphan*/  dst_addr; } ;
struct igb_nfc_filter {int action; int /*<<< orphan*/  cookie; TYPE_2__ filter; } ;
struct igb_adapter {int dummy; } ;
struct flow_dissector_key_vlan {scalar_t__ vlan_priority; } ;
struct flow_dissector_key_eth_addrs {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_basic {scalar_t__ n_proto; } ;
struct TYPE_7__ {int used_keys; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ ETHER_TYPE_FULL_MASK ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_CONTROL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ETH_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_VLAN ; 
 int /*<<< orphan*/  IGB_FILTER_FLAG_DST_MAC_ADDR ; 
 int /*<<< orphan*/  IGB_FILTER_FLAG_ETHER_TYPE ; 
 int /*<<< orphan*/  IGB_FILTER_FLAG_SRC_MAC_ADDR ; 
 int /*<<< orphan*/  IGB_FILTER_FLAG_VLAN_TCI ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ VLAN_PRIO_FULL_MASK ; 
 scalar_t__ dissector_uses_key (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 void* skb_flow_dissector_target (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igb_parse_cls_flower(struct igb_adapter *adapter,
				struct tc_cls_flower_offload *f,
				int traffic_class,
				struct igb_nfc_filter *input)
{
	struct netlink_ext_ack *extack = f->common.extack;

	if (f->dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN))) {
		NL_SET_ERR_MSG_MOD(extack,
				   "Unsupported key used, only BASIC, CONTROL, ETH_ADDRS and VLAN are supported");
		return -EOPNOTSUPP;
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		struct flow_dissector_key_eth_addrs *key, *mask;

		key = skb_flow_dissector_target(f->dissector,
						FLOW_DISSECTOR_KEY_ETH_ADDRS,
						f->key);
		mask = skb_flow_dissector_target(f->dissector,
						 FLOW_DISSECTOR_KEY_ETH_ADDRS,
						 f->mask);

		if (!is_zero_ether_addr(mask->dst)) {
			if (!is_broadcast_ether_addr(mask->dst)) {
				NL_SET_ERR_MSG_MOD(extack, "Only full masks are supported for destination MAC address");
				return -EINVAL;
			}

			input->filter.match_flags |=
				IGB_FILTER_FLAG_DST_MAC_ADDR;
			ether_addr_copy(input->filter.dst_addr, key->dst);
		}

		if (!is_zero_ether_addr(mask->src)) {
			if (!is_broadcast_ether_addr(mask->src)) {
				NL_SET_ERR_MSG_MOD(extack, "Only full masks are supported for source MAC address");
				return -EINVAL;
			}

			input->filter.match_flags |=
				IGB_FILTER_FLAG_SRC_MAC_ADDR;
			ether_addr_copy(input->filter.src_addr, key->src);
		}
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_dissector_key_basic *key, *mask;

		key = skb_flow_dissector_target(f->dissector,
						FLOW_DISSECTOR_KEY_BASIC,
						f->key);
		mask = skb_flow_dissector_target(f->dissector,
						 FLOW_DISSECTOR_KEY_BASIC,
						 f->mask);

		if (mask->n_proto) {
			if (mask->n_proto != ETHER_TYPE_FULL_MASK) {
				NL_SET_ERR_MSG_MOD(extack, "Only full mask is supported for EtherType filter");
				return -EINVAL;
			}

			input->filter.match_flags |= IGB_FILTER_FLAG_ETHER_TYPE;
			input->filter.etype = key->n_proto;
		}
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_dissector_key_vlan *key, *mask;

		key = skb_flow_dissector_target(f->dissector,
						FLOW_DISSECTOR_KEY_VLAN,
						f->key);
		mask = skb_flow_dissector_target(f->dissector,
						 FLOW_DISSECTOR_KEY_VLAN,
						 f->mask);

		if (mask->vlan_priority) {
			if (mask->vlan_priority != VLAN_PRIO_FULL_MASK) {
				NL_SET_ERR_MSG_MOD(extack, "Only full mask is supported for VLAN priority");
				return -EINVAL;
			}

			input->filter.match_flags |= IGB_FILTER_FLAG_VLAN_TCI;
			input->filter.vlan_tci = key->vlan_priority;
		}
	}

	input->action = traffic_class;
	input->cookie = f->cookie;

	return 0;
}