#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_13__ {int vlan_id; int dst_port; int src_port; scalar_t__* src_ip; scalar_t__* dst_ip; int /*<<< orphan*/  src_mac; int /*<<< orphan*/  dst_mac; } ;
struct TYPE_14__ {TYPE_4__ tcp_spec; } ;
struct TYPE_11__ {int* dst_mac; int* src_mac; int vlan_id; int dst_port; int src_port; scalar_t__* src_ip; scalar_t__* dst_ip; } ;
struct TYPE_12__ {TYPE_2__ tcp_spec; } ;
struct virtchnl_filter {int field_flags; TYPE_5__ data; TYPE_3__ mask; int /*<<< orphan*/  flow_type; } ;
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; TYPE_6__* dissector; int /*<<< orphan*/  key; } ;
struct i40evf_cloud_filter {struct virtchnl_filter f; } ;
struct i40evf_adapter {TYPE_1__* pdev; } ;
struct flow_dissector_key_vlan {int vlan_id; } ;
struct flow_dissector_key_ports {int src; int dst; } ;
struct flow_dissector_key_keyid {scalar_t__ keyid; } ;
struct TYPE_16__ {int /*<<< orphan*/  s6_addr32; } ;
struct flow_dissector_key_ipv6_addrs {TYPE_7__ src; TYPE_7__ dst; } ;
struct flow_dissector_key_ipv4_addrs {scalar_t__ src; scalar_t__ dst; } ;
struct flow_dissector_key_eth_addrs {int dst; int src; } ;
struct flow_dissector_key_control {scalar_t__ addr_type; } ;
struct flow_dissector_key_basic {scalar_t__ ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_15__ {int used_keys; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ETH_ALEN ; 
 scalar_t__ ETH_P_ALL ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 scalar_t__ FLOW_DISSECTOR_KEY_BASIC ; 
 scalar_t__ FLOW_DISSECTOR_KEY_CONTROL ; 
 scalar_t__ FLOW_DISSECTOR_KEY_ENC_KEYID ; 
 scalar_t__ FLOW_DISSECTOR_KEY_ETH_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_PORTS ; 
 scalar_t__ FLOW_DISSECTOR_KEY_VLAN ; 
 int I40EVF_CLOUD_FIELD_IIP ; 
 int I40EVF_CLOUD_FIELD_IMAC ; 
 int I40EVF_CLOUD_FIELD_IVLAN ; 
 int I40EVF_CLOUD_FIELD_OMAC ; 
 int I40EVF_CLOUD_FIELD_TEN_ID ; 
 int I40E_ERR_CONFIG ; 
 scalar_t__ IPPROTO_TCP ; 
 int IPV6_ADDR_ANY ; 
 int /*<<< orphan*/  VIRTCHNL_TCP_V6_FLOW ; 
 int VLAN_VID_MASK ; 
 int be16_to_cpu (int) ; 
 int be32_to_cpu (scalar_t__) ; 
 int cpu_to_be16 (int) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dissector_uses_key (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ipv6_addr_any (TYPE_7__*) ; 
 scalar_t__ ipv6_addr_loopback (TYPE_7__*) ; 
 scalar_t__ is_broadcast_ether_addr (int) ; 
 scalar_t__ is_multicast_ether_addr (int) ; 
 scalar_t__ is_valid_ether_addr (int) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__**,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 void* skb_flow_dissector_target (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40evf_parse_cls_flower(struct i40evf_adapter *adapter,
				   struct tc_cls_flower_offload *f,
				   struct i40evf_cloud_filter *filter)
{
	u16 n_proto_mask = 0;
	u16 n_proto_key = 0;
	u8 field_flags = 0;
	u16 addr_type = 0;
	u16 n_proto = 0;
	int i = 0;
	struct virtchnl_filter *vf = &filter->f;

	if (f->dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_KEYID))) {
		dev_err(&adapter->pdev->dev, "Unsupported key used: 0x%x\n",
			f->dissector->used_keys);
		return -EOPNOTSUPP;
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		struct flow_dissector_key_keyid *mask =
			skb_flow_dissector_target(f->dissector,
						  FLOW_DISSECTOR_KEY_ENC_KEYID,
						  f->mask);

		if (mask->keyid != 0)
			field_flags |= I40EVF_CLOUD_FIELD_TEN_ID;
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
		n_proto = n_proto_key & n_proto_mask;
		if (n_proto != ETH_P_IP && n_proto != ETH_P_IPV6)
			return -EINVAL;
		if (n_proto == ETH_P_IPV6) {
			/* specify flow type as TCP IPv6 */
			vf->flow_type = VIRTCHNL_TCP_V6_FLOW;
		}

		if (key->ip_proto != IPPROTO_TCP) {
			dev_info(&adapter->pdev->dev, "Only TCP transport is supported\n");
			return -EINVAL;
		}
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
				field_flags |= I40EVF_CLOUD_FIELD_OMAC;
			} else {
				dev_err(&adapter->pdev->dev, "Bad ether dest mask %pM\n",
					mask->dst);
				return I40E_ERR_CONFIG;
			}
		}

		if (!is_zero_ether_addr(mask->src)) {
			if (is_broadcast_ether_addr(mask->src)) {
				field_flags |= I40EVF_CLOUD_FIELD_IMAC;
			} else {
				dev_err(&adapter->pdev->dev, "Bad ether src mask %pM\n",
					mask->src);
				return I40E_ERR_CONFIG;
			}
		}

		if (!is_zero_ether_addr(key->dst))
			if (is_valid_ether_addr(key->dst) ||
			    is_multicast_ether_addr(key->dst)) {
				/* set the mask if a valid dst_mac address */
				for (i = 0; i < ETH_ALEN; i++)
					vf->mask.tcp_spec.dst_mac[i] |= 0xff;
				ether_addr_copy(vf->data.tcp_spec.dst_mac,
						key->dst);
			}

		if (!is_zero_ether_addr(key->src))
			if (is_valid_ether_addr(key->src) ||
			    is_multicast_ether_addr(key->src)) {
				/* set the mask if a valid dst_mac address */
				for (i = 0; i < ETH_ALEN; i++)
					vf->mask.tcp_spec.src_mac[i] |= 0xff;
				ether_addr_copy(vf->data.tcp_spec.src_mac,
						key->src);
		}
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
				field_flags |= I40EVF_CLOUD_FIELD_IVLAN;
			} else {
				dev_err(&adapter->pdev->dev, "Bad vlan mask %u\n",
					mask->vlan_id);
				return I40E_ERR_CONFIG;
			}
		}
		vf->mask.tcp_spec.vlan_id |= cpu_to_be16(0xffff);
		vf->data.tcp_spec.vlan_id = cpu_to_be16(key->vlan_id);
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
				field_flags |= I40EVF_CLOUD_FIELD_IIP;
			} else {
				dev_err(&adapter->pdev->dev, "Bad ip dst mask 0x%08x\n",
					be32_to_cpu(mask->dst));
				return I40E_ERR_CONFIG;
			}
		}

		if (mask->src) {
			if (mask->src == cpu_to_be32(0xffffffff)) {
				field_flags |= I40EVF_CLOUD_FIELD_IIP;
			} else {
				dev_err(&adapter->pdev->dev, "Bad ip src mask 0x%08x\n",
					be32_to_cpu(mask->dst));
				return I40E_ERR_CONFIG;
			}
		}

		if (field_flags & I40EVF_CLOUD_FIELD_TEN_ID) {
			dev_info(&adapter->pdev->dev, "Tenant id not allowed for ip filter\n");
			return I40E_ERR_CONFIG;
		}
		if (key->dst) {
			vf->mask.tcp_spec.dst_ip[0] |= cpu_to_be32(0xffffffff);
			vf->data.tcp_spec.dst_ip[0] = key->dst;
		}
		if (key->src) {
			vf->mask.tcp_spec.src_ip[0] |= cpu_to_be32(0xffffffff);
			vf->data.tcp_spec.src_ip[0] = key->src;
		}
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

		/* validate mask, make sure it is not IPV6_ADDR_ANY */
		if (ipv6_addr_any(&mask->dst)) {
			dev_err(&adapter->pdev->dev, "Bad ipv6 dst mask 0x%02x\n",
				IPV6_ADDR_ANY);
			return I40E_ERR_CONFIG;
		}

		/* src and dest IPv6 address should not be LOOPBACK
		 * (0:0:0:0:0:0:0:1) which can be represented as ::1
		 */
		if (ipv6_addr_loopback(&key->dst) ||
		    ipv6_addr_loopback(&key->src)) {
			dev_err(&adapter->pdev->dev,
				"ipv6 addr should not be loopback\n");
			return I40E_ERR_CONFIG;
		}
		if (!ipv6_addr_any(&mask->dst) || !ipv6_addr_any(&mask->src))
			field_flags |= I40EVF_CLOUD_FIELD_IIP;

		for (i = 0; i < 4; i++)
			vf->mask.tcp_spec.dst_ip[i] |= cpu_to_be32(0xffffffff);
		memcpy(&vf->data.tcp_spec.dst_ip, &key->dst.s6_addr32,
		       sizeof(vf->data.tcp_spec.dst_ip));
		for (i = 0; i < 4; i++)
			vf->mask.tcp_spec.src_ip[i] |= cpu_to_be32(0xffffffff);
		memcpy(&vf->data.tcp_spec.src_ip, &key->src.s6_addr32,
		       sizeof(vf->data.tcp_spec.src_ip));
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
				field_flags |= I40EVF_CLOUD_FIELD_IIP;
			} else {
				dev_err(&adapter->pdev->dev, "Bad src port mask %u\n",
					be16_to_cpu(mask->src));
				return I40E_ERR_CONFIG;
			}
		}

		if (mask->dst) {
			if (mask->dst == cpu_to_be16(0xffff)) {
				field_flags |= I40EVF_CLOUD_FIELD_IIP;
			} else {
				dev_err(&adapter->pdev->dev, "Bad dst port mask %u\n",
					be16_to_cpu(mask->dst));
				return I40E_ERR_CONFIG;
			}
		}
		if (key->dst) {
			vf->mask.tcp_spec.dst_port |= cpu_to_be16(0xffff);
			vf->data.tcp_spec.dst_port = key->dst;
		}

		if (key->src) {
			vf->mask.tcp_spec.src_port |= cpu_to_be16(0xffff);
			vf->data.tcp_spec.src_port = key->src;
		}
	}
	vf->field_flags = field_flags;

	return 0;
}