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
typedef  scalar_t__ u16 ;
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; int /*<<< orphan*/  key; } ;
struct net_device {int dummy; } ;
struct flow_dissector_key_vlan {scalar_t__ vlan_id; scalar_t__ vlan_priority; } ;
struct flow_dissector_key_ports {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_keyid {int /*<<< orphan*/  keyid; } ;
struct TYPE_7__ {int /*<<< orphan*/ * s6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * s6_addr; } ;
struct flow_dissector_key_ipv6_addrs {TYPE_2__ src; TYPE_1__ dst; } ;
struct flow_dissector_key_ipv4_addrs {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_ip {int /*<<< orphan*/  tos; } ;
struct flow_dissector_key_control {scalar_t__ addr_type; } ;
struct flow_dissector_key_basic {int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_8__ {int encap_vld; int ivlan_vld; int /*<<< orphan*/  iport; scalar_t__ ethtype; scalar_t__ ivlan; void* vni; int /*<<< orphan*/  tos; void* fport; void* lport; int /*<<< orphan*/ * fip; int /*<<< orphan*/ * lip; int /*<<< orphan*/  proto; } ;
struct TYPE_9__ {scalar_t__ ethtype; int encap_vld; int ivlan_vld; int /*<<< orphan*/  iport; scalar_t__ ivlan; void* vni; int /*<<< orphan*/  tos; void* fport; void* lport; int /*<<< orphan*/ * fip; int /*<<< orphan*/ * lip; int /*<<< orphan*/  proto; } ;
struct ch_filter_specification {int type; TYPE_3__ mask; TYPE_4__ val; void* nat_fport; void* nat_lport; int /*<<< orphan*/ * nat_fip; int /*<<< orphan*/ * nat_lip; } ;
struct TYPE_10__ {int /*<<< orphan*/  port_id; } ;

/* Variables and functions */
 scalar_t__ ETH_P_8021Q ; 
 scalar_t__ ETH_P_ALL ; 
 scalar_t__ ETH_P_IPV6 ; 
 scalar_t__ FLOW_DISSECTOR_KEY_BASIC ; 
 scalar_t__ FLOW_DISSECTOR_KEY_CONTROL ; 
 scalar_t__ FLOW_DISSECTOR_KEY_ENC_KEYID ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IP ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_PORTS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_VLAN ; 
 scalar_t__ VLAN_PRIO_SHIFT ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_5__* netdev2pinfo (struct net_device*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 void* skb_flow_dissector_target (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxgb4_process_flow_match(struct net_device *dev,
				     struct tc_cls_flower_offload *cls,
				     struct ch_filter_specification *fs)
{
	u16 addr_type = 0;

	if (dissector_uses_key(cls->dissector, FLOW_DISSECTOR_KEY_CONTROL)) {
		struct flow_dissector_key_control *key =
			skb_flow_dissector_target(cls->dissector,
						  FLOW_DISSECTOR_KEY_CONTROL,
						  cls->key);

		addr_type = key->addr_type;
	}

	if (dissector_uses_key(cls->dissector, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_dissector_key_basic *key =
			skb_flow_dissector_target(cls->dissector,
						  FLOW_DISSECTOR_KEY_BASIC,
						  cls->key);
		struct flow_dissector_key_basic *mask =
			skb_flow_dissector_target(cls->dissector,
						  FLOW_DISSECTOR_KEY_BASIC,
						  cls->mask);
		u16 ethtype_key = ntohs(key->n_proto);
		u16 ethtype_mask = ntohs(mask->n_proto);

		if (ethtype_key == ETH_P_ALL) {
			ethtype_key = 0;
			ethtype_mask = 0;
		}

		if (ethtype_key == ETH_P_IPV6)
			fs->type = 1;

		fs->val.ethtype = ethtype_key;
		fs->mask.ethtype = ethtype_mask;
		fs->val.proto = key->ip_proto;
		fs->mask.proto = mask->ip_proto;
	}

	if (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) {
		struct flow_dissector_key_ipv4_addrs *key =
			skb_flow_dissector_target(cls->dissector,
						  FLOW_DISSECTOR_KEY_IPV4_ADDRS,
						  cls->key);
		struct flow_dissector_key_ipv4_addrs *mask =
			skb_flow_dissector_target(cls->dissector,
						  FLOW_DISSECTOR_KEY_IPV4_ADDRS,
						  cls->mask);
		fs->type = 0;
		memcpy(&fs->val.lip[0], &key->dst, sizeof(key->dst));
		memcpy(&fs->val.fip[0], &key->src, sizeof(key->src));
		memcpy(&fs->mask.lip[0], &mask->dst, sizeof(mask->dst));
		memcpy(&fs->mask.fip[0], &mask->src, sizeof(mask->src));

		/* also initialize nat_lip/fip to same values */
		memcpy(&fs->nat_lip[0], &key->dst, sizeof(key->dst));
		memcpy(&fs->nat_fip[0], &key->src, sizeof(key->src));

	}

	if (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) {
		struct flow_dissector_key_ipv6_addrs *key =
			skb_flow_dissector_target(cls->dissector,
						  FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						  cls->key);
		struct flow_dissector_key_ipv6_addrs *mask =
			skb_flow_dissector_target(cls->dissector,
						  FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						  cls->mask);

		fs->type = 1;
		memcpy(&fs->val.lip[0], key->dst.s6_addr, sizeof(key->dst));
		memcpy(&fs->val.fip[0], key->src.s6_addr, sizeof(key->src));
		memcpy(&fs->mask.lip[0], mask->dst.s6_addr, sizeof(mask->dst));
		memcpy(&fs->mask.fip[0], mask->src.s6_addr, sizeof(mask->src));

		/* also initialize nat_lip/fip to same values */
		memcpy(&fs->nat_lip[0], key->dst.s6_addr, sizeof(key->dst));
		memcpy(&fs->nat_fip[0], key->src.s6_addr, sizeof(key->src));
	}

	if (dissector_uses_key(cls->dissector, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_dissector_key_ports *key, *mask;

		key = skb_flow_dissector_target(cls->dissector,
						FLOW_DISSECTOR_KEY_PORTS,
						cls->key);
		mask = skb_flow_dissector_target(cls->dissector,
						 FLOW_DISSECTOR_KEY_PORTS,
						 cls->mask);
		fs->val.lport = cpu_to_be16(key->dst);
		fs->mask.lport = cpu_to_be16(mask->dst);
		fs->val.fport = cpu_to_be16(key->src);
		fs->mask.fport = cpu_to_be16(mask->src);

		/* also initialize nat_lport/fport to same values */
		fs->nat_lport = cpu_to_be16(key->dst);
		fs->nat_fport = cpu_to_be16(key->src);
	}

	if (dissector_uses_key(cls->dissector, FLOW_DISSECTOR_KEY_IP)) {
		struct flow_dissector_key_ip *key, *mask;

		key = skb_flow_dissector_target(cls->dissector,
						FLOW_DISSECTOR_KEY_IP,
						cls->key);
		mask = skb_flow_dissector_target(cls->dissector,
						 FLOW_DISSECTOR_KEY_IP,
						 cls->mask);
		fs->val.tos = key->tos;
		fs->mask.tos = mask->tos;
	}

	if (dissector_uses_key(cls->dissector, FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		struct flow_dissector_key_keyid *key, *mask;

		key = skb_flow_dissector_target(cls->dissector,
						FLOW_DISSECTOR_KEY_ENC_KEYID,
						cls->key);
		mask = skb_flow_dissector_target(cls->dissector,
						 FLOW_DISSECTOR_KEY_ENC_KEYID,
						 cls->mask);
		fs->val.vni = be32_to_cpu(key->keyid);
		fs->mask.vni = be32_to_cpu(mask->keyid);
		if (fs->mask.vni) {
			fs->val.encap_vld = 1;
			fs->mask.encap_vld = 1;
		}
	}

	if (dissector_uses_key(cls->dissector, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_dissector_key_vlan *key, *mask;
		u16 vlan_tci, vlan_tci_mask;

		key = skb_flow_dissector_target(cls->dissector,
						FLOW_DISSECTOR_KEY_VLAN,
						cls->key);
		mask = skb_flow_dissector_target(cls->dissector,
						 FLOW_DISSECTOR_KEY_VLAN,
						 cls->mask);
		vlan_tci = key->vlan_id | (key->vlan_priority <<
					   VLAN_PRIO_SHIFT);
		vlan_tci_mask = mask->vlan_id | (mask->vlan_priority <<
						 VLAN_PRIO_SHIFT);
		fs->val.ivlan = vlan_tci;
		fs->mask.ivlan = vlan_tci_mask;

		/* Chelsio adapters use ivlan_vld bit to match vlan packets
		 * as 802.1Q. Also, when vlan tag is present in packets,
		 * ethtype match is used then to match on ethtype of inner
		 * header ie. the header following the vlan header.
		 * So, set the ivlan_vld based on ethtype info supplied by
		 * TC for vlan packets if its 802.1Q. And then reset the
		 * ethtype value else, hw will try to match the supplied
		 * ethtype value with ethtype of inner header.
		 */
		if (fs->val.ethtype == ETH_P_8021Q) {
			fs->val.ivlan_vld = 1;
			fs->mask.ivlan_vld = 1;
			fs->val.ethtype = 0;
			fs->mask.ethtype = 0;
		}
	}

	/* Match only packets coming from the ingress port where this
	 * filter will be created.
	 */
	fs->val.iport = netdev2pinfo(dev)->port_id;
	fs->mask.iport = ~0;
}