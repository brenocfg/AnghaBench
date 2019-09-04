#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; TYPE_2__* dissector; int /*<<< orphan*/  key; } ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {TYPE_1__* pdev; } ;
struct i40e_cloud_filter {int ip_proto; scalar_t__ dst_ipv4; scalar_t__ src_ipv4; scalar_t__ dst_port; scalar_t__ src_port; int flags; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; scalar_t__ vlan_id; int /*<<< orphan*/  src_mac; int /*<<< orphan*/  dst_mac; scalar_t__ n_proto; int /*<<< orphan*/  tenant_id; } ;
struct flow_dissector_key_vlan {scalar_t__ vlan_id; } ;
struct flow_dissector_key_ports {scalar_t__ src; scalar_t__ dst; } ;
struct flow_dissector_key_keyid {scalar_t__ keyid; } ;
struct TYPE_8__ {int /*<<< orphan*/  s6_addr32; } ;
struct flow_dissector_key_ipv6_addrs {TYPE_3__ dst; TYPE_3__ src; } ;
struct flow_dissector_key_ipv4_addrs {scalar_t__ dst; scalar_t__ src; } ;
struct flow_dissector_key_eth_addrs {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct flow_dissector_key_control {scalar_t__ addr_type; } ;
struct flow_dissector_key_basic {int ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_7__ {int used_keys; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ ETH_P_ALL ; 
 scalar_t__ FLOW_DISSECTOR_KEY_BASIC ; 
 scalar_t__ FLOW_DISSECTOR_KEY_CONTROL ; 
 scalar_t__ FLOW_DISSECTOR_KEY_ENC_KEYID ; 
 scalar_t__ FLOW_DISSECTOR_KEY_ETH_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_PORTS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_VLAN ; 
 int I40E_CLOUD_FIELD_IIP ; 
 int I40E_CLOUD_FIELD_IMAC ; 
 int I40E_CLOUD_FIELD_IVLAN ; 
 int I40E_CLOUD_FIELD_OMAC ; 
 int I40E_CLOUD_FIELD_TEN_ID ; 
 int I40E_ERR_CONFIG ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 scalar_t__ VLAN_VID_MASK ; 
 int /*<<< orphan*/  be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  be32_to_cpu (scalar_t__) ; 
 scalar_t__ cpu_to_be16 (int) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ dissector_uses_key (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_addr_any (TYPE_3__*) ; 
 scalar_t__ ipv6_addr_loopback (TYPE_3__*) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 void* skb_flow_dissector_target (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_parse_cls_flower(struct i40e_vsi *vsi,
				 struct tc_cls_flower_offload *f,
				 struct i40e_cloud_filter *filter)
{
	u16 n_proto_mask = 0, n_proto_key = 0, addr_type = 0;
	struct i40e_pf *pf = vsi->back;
	u8 field_flags = 0;

	if (f->dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_KEYID))) {
		dev_err(&pf->pdev->dev, "Unsupported key used: 0x%x\n",
			f->dissector->used_keys);
		return -EOPNOTSUPP;
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		struct flow_dissector_key_keyid *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_KEYID,
						  f->key);

		struct flow_dissector_key_keyid *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_KEYID,
						  f->mask);

		if (mask->keyid != 0)
			field_flags |= I40E_CLOUD_FIELD_TEN_ID;

		filter->tenant_id = be32_to_cpu(key->keyid);
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_dissector_key_basic *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_BASIC,
						  f->key);

		struct flow_dissector_key_basic *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_BASIC,
						  f->mask);

		n_proto_key = ntohs(key->n_proto);
		n_proto_mask = ntohs(mask->n_proto);

		if (n_proto_key == ETH_P_ALL) {
			n_proto_key = 0;
			n_proto_mask = 0;
		}
		filter->n_proto = n_proto_key & n_proto_mask;
		filter->ip_proto = key->ip_proto;
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		struct flow_dissector_key_eth_addrs *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ETH_ADDRS,
						  f->key);

		struct flow_dissector_key_eth_addrs *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ETH_ADDRS,
						  f->mask);

		/* use is_broadcast and is_zero to check for all 0xf or 0 */
		if (!is_zero_ether_addr(mask->dst)) {
			if (is_broadcast_ether_addr(mask->dst)) {
				field_flags |= I40E_CLOUD_FIELD_OMAC;
			} else {
				dev_err(&pf->pdev->dev, "Bad ether dest mask %pM\n",
					mask->dst);
				return I40E_ERR_CONFIG;
			}
		}

		if (!is_zero_ether_addr(mask->src)) {
			if (is_broadcast_ether_addr(mask->src)) {
				field_flags |= I40E_CLOUD_FIELD_IMAC;
			} else {
				dev_err(&pf->pdev->dev, "Bad ether src mask %pM\n",
					mask->src);
				return I40E_ERR_CONFIG;
			}
		}
		ether_addr_copy(filter->dst_mac, key->dst);
		ether_addr_copy(filter->src_mac, key->src);
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_dissector_key_vlan *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_VLAN,
						  f->key);
		struct flow_dissector_key_vlan *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_VLAN,
						  f->mask);

		if (mask->vlan_id) {
			if (mask->vlan_id == VLAN_VID_MASK) {
				field_flags |= I40E_CLOUD_FIELD_IVLAN;

			} else {
				dev_err(&pf->pdev->dev, "Bad vlan mask 0x%04x\n",
					mask->vlan_id);
				return I40E_ERR_CONFIG;
			}
		}

		filter->vlan_id = cpu_to_be16(key->vlan_id);
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_CONTROL)) {
		struct flow_dissector_key_control *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_CONTROL,
						  f->key);

		addr_type = key->addr_type;
	}

	if (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) {
		struct flow_dissector_key_ipv4_addrs *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_IPV4_ADDRS,
						  f->key);
		struct flow_dissector_key_ipv4_addrs *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_IPV4_ADDRS,
						  f->mask);

		if (mask->dst) {
			if (mask->dst == cpu_to_be32(0xffffffff)) {
				field_flags |= I40E_CLOUD_FIELD_IIP;
			} else {
				dev_err(&pf->pdev->dev, "Bad ip dst mask %pI4b\n",
					&mask->dst);
				return I40E_ERR_CONFIG;
			}
		}

		if (mask->src) {
			if (mask->src == cpu_to_be32(0xffffffff)) {
				field_flags |= I40E_CLOUD_FIELD_IIP;
			} else {
				dev_err(&pf->pdev->dev, "Bad ip src mask %pI4b\n",
					&mask->src);
				return I40E_ERR_CONFIG;
			}
		}

		if (field_flags & I40E_CLOUD_FIELD_TEN_ID) {
			dev_err(&pf->pdev->dev, "Tenant id not allowed for ip filter\n");
			return I40E_ERR_CONFIG;
		}
		filter->dst_ipv4 = key->dst;
		filter->src_ipv4 = key->src;
	}

	if (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) {
		struct flow_dissector_key_ipv6_addrs *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						  f->key);
		struct flow_dissector_key_ipv6_addrs *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						  f->mask);

		/* src and dest IPV6 address should not be LOOPBACK
		 * (0:0:0:0:0:0:0:1), which can be represented as ::1
		 */
		if (ipv6_addr_loopback(&key->dst) ||
		    ipv6_addr_loopback(&key->src)) {
			dev_err(&pf->pdev->dev,
				"Bad ipv6, addr is LOOPBACK\n");
			return I40E_ERR_CONFIG;
		}
		if (!ipv6_addr_any(&mask->dst) || !ipv6_addr_any(&mask->src))
			field_flags |= I40E_CLOUD_FIELD_IIP;

		memcpy(&filter->src_ipv6, &key->src.s6_addr32,
		       sizeof(filter->src_ipv6));
		memcpy(&filter->dst_ipv6, &key->dst.s6_addr32,
		       sizeof(filter->dst_ipv6));
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_dissector_key_ports *key =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_PORTS,
						  f->key);
		struct flow_dissector_key_ports *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_PORTS,
						  f->mask);

		if (mask->src) {
			if (mask->src == cpu_to_be16(0xffff)) {
				field_flags |= I40E_CLOUD_FIELD_IIP;
			} else {
				dev_err(&pf->pdev->dev, "Bad src port mask 0x%04x\n",
					be16_to_cpu(mask->src));
				return I40E_ERR_CONFIG;
			}
		}

		if (mask->dst) {
			if (mask->dst == cpu_to_be16(0xffff)) {
				field_flags |= I40E_CLOUD_FIELD_IIP;
			} else {
				dev_err(&pf->pdev->dev, "Bad dst port mask 0x%04x\n",
					be16_to_cpu(mask->dst));
				return I40E_ERR_CONFIG;
			}
		}

		filter->dst_port = key->dst;
		filter->src_port = key->src;

		switch (filter->ip_proto) {
		case IPPROTO_TCP:
		case IPPROTO_UDP:
			break;
		default:
			dev_err(&pf->pdev->dev,
				"Only UDP and TCP transport are supported\n");
			return -EINVAL;
		}
	}
	filter->flags = field_flags;
	return 0;
}