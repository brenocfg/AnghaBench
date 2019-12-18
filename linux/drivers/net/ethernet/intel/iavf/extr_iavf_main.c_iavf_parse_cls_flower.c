#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_21__ ;
typedef  struct TYPE_33__   TYPE_20__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_19__ ;
typedef  struct TYPE_30__   TYPE_18__ ;
typedef  struct TYPE_29__   TYPE_17__ ;
typedef  struct TYPE_28__   TYPE_16__ ;
typedef  struct TYPE_27__   TYPE_15__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_29__ {int vlan_id; scalar_t__ src_port; scalar_t__ dst_port; scalar_t__* src_ip; scalar_t__* dst_ip; int /*<<< orphan*/  src_mac; int /*<<< orphan*/  dst_mac; } ;
struct TYPE_30__ {TYPE_17__ tcp_spec; } ;
struct TYPE_27__ {int* dst_mac; int* src_mac; int vlan_id; int dst_port; int src_port; scalar_t__* src_ip; scalar_t__* dst_ip; } ;
struct TYPE_28__ {TYPE_15__ tcp_spec; } ;
struct virtchnl_filter {int field_flags; TYPE_18__ data; TYPE_16__ mask; int /*<<< orphan*/  flow_type; } ;
struct iavf_cloud_filter {struct virtchnl_filter f; } ;
struct iavf_adapter {TYPE_13__* pdev; } ;
struct TYPE_33__ {struct flow_dissector* dissector; } ;
struct flow_rule {TYPE_20__ match; } ;
struct flow_match_vlan {TYPE_7__* key; TYPE_6__* mask; } ;
struct flow_match_ports {TYPE_19__* key; TYPE_14__* mask; } ;
struct flow_match_ipv6_addrs {TYPE_12__* key; TYPE_11__* mask; } ;
struct flow_match_ipv4_addrs {TYPE_10__* key; TYPE_9__* mask; } ;
struct flow_match_eth_addrs {TYPE_5__* key; TYPE_4__* mask; } ;
struct flow_match_enc_keyid {TYPE_1__* mask; } ;
struct flow_match_control {TYPE_8__* key; } ;
struct flow_match_basic {TYPE_3__* key; TYPE_2__* mask; } ;
struct flow_dissector {int used_keys; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_42__ {scalar_t__ dst; scalar_t__ src; } ;
struct TYPE_41__ {scalar_t__ addr_type; } ;
struct TYPE_40__ {int vlan_id; } ;
struct TYPE_39__ {int vlan_id; } ;
struct TYPE_38__ {int dst; int src; } ;
struct TYPE_37__ {int dst; int src; } ;
struct TYPE_36__ {scalar_t__ ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_35__ {int /*<<< orphan*/  n_proto; } ;
struct TYPE_34__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_32__ {scalar_t__ keyid; } ;
struct TYPE_31__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_26__ {int src; int dst; } ;
struct TYPE_25__ {int /*<<< orphan*/  dev; } ;
struct TYPE_24__ {TYPE_21__ src; TYPE_21__ dst; } ;
struct TYPE_23__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_22__ {scalar_t__ src; scalar_t__ dst; } ;

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
 int IAVF_CLOUD_FIELD_IIP ; 
 int IAVF_CLOUD_FIELD_IMAC ; 
 int IAVF_CLOUD_FIELD_IVLAN ; 
 int IAVF_CLOUD_FIELD_OMAC ; 
 int IAVF_CLOUD_FIELD_TEN_ID ; 
 int IAVF_ERR_CONFIG ; 
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
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_basic (struct flow_rule*,struct flow_match_basic*) ; 
 int /*<<< orphan*/  flow_rule_match_control (struct flow_rule*,struct flow_match_control*) ; 
 int /*<<< orphan*/  flow_rule_match_enc_keyid (struct flow_rule*,struct flow_match_enc_keyid*) ; 
 int /*<<< orphan*/  flow_rule_match_eth_addrs (struct flow_rule*,struct flow_match_eth_addrs*) ; 
 int /*<<< orphan*/  flow_rule_match_ipv4_addrs (struct flow_rule*,struct flow_match_ipv4_addrs*) ; 
 int /*<<< orphan*/  flow_rule_match_ipv6_addrs (struct flow_rule*,struct flow_match_ipv6_addrs*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,scalar_t__) ; 
 int /*<<< orphan*/  flow_rule_match_ports (struct flow_rule*,struct flow_match_ports*) ; 
 int /*<<< orphan*/  flow_rule_match_vlan (struct flow_rule*,struct flow_match_vlan*) ; 
 scalar_t__ ipv6_addr_any (int /*<<< orphan*/ *) ; 
 scalar_t__ ipv6_addr_loopback (TYPE_21__*) ; 
 scalar_t__ is_broadcast_ether_addr (int) ; 
 scalar_t__ is_multicast_ether_addr (int) ; 
 scalar_t__ is_valid_ether_addr (int) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__**,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iavf_parse_cls_flower(struct iavf_adapter *adapter,
				 struct flow_cls_offload *f,
				 struct iavf_cloud_filter *filter)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(f);
	struct flow_dissector *dissector = rule->match.dissector;
	u16 n_proto_mask = 0;
	u16 n_proto_key = 0;
	u8 field_flags = 0;
	u16 addr_type = 0;
	u16 n_proto = 0;
	int i = 0;
	struct virtchnl_filter *vf = &filter->f;

	if (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_KEYID))) {
		dev_err(&adapter->pdev->dev, "Unsupported key used: 0x%x\n",
			dissector->used_keys);
		return -EOPNOTSUPP;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		struct flow_match_enc_keyid match;

		flow_rule_match_enc_keyid(rule, &match);
		if (match.mask->keyid != 0)
			field_flags |= IAVF_CLOUD_FIELD_TEN_ID;
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
		n_proto = n_proto_key & n_proto_mask;
		if (n_proto != ETH_P_IP && n_proto != ETH_P_IPV6)
			return -EINVAL;
		if (n_proto == ETH_P_IPV6) {
			/* specify flow type as TCP IPv6 */
			vf->flow_type = VIRTCHNL_TCP_V6_FLOW;
		}

		if (match.key->ip_proto != IPPROTO_TCP) {
			dev_info(&adapter->pdev->dev, "Only TCP transport is supported\n");
			return -EINVAL;
		}
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		struct flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);

		/* use is_broadcast and is_zero to check for all 0xf or 0 */
		if (!is_zero_ether_addr(match.mask->dst)) {
			if (is_broadcast_ether_addr(match.mask->dst)) {
				field_flags |= IAVF_CLOUD_FIELD_OMAC;
			} else {
				dev_err(&adapter->pdev->dev, "Bad ether dest mask %pM\n",
					match.mask->dst);
				return IAVF_ERR_CONFIG;
			}
		}

		if (!is_zero_ether_addr(match.mask->src)) {
			if (is_broadcast_ether_addr(match.mask->src)) {
				field_flags |= IAVF_CLOUD_FIELD_IMAC;
			} else {
				dev_err(&adapter->pdev->dev, "Bad ether src mask %pM\n",
					match.mask->src);
				return IAVF_ERR_CONFIG;
			}
		}

		if (!is_zero_ether_addr(match.key->dst))
			if (is_valid_ether_addr(match.key->dst) ||
			    is_multicast_ether_addr(match.key->dst)) {
				/* set the mask if a valid dst_mac address */
				for (i = 0; i < ETH_ALEN; i++)
					vf->mask.tcp_spec.dst_mac[i] |= 0xff;
				ether_addr_copy(vf->data.tcp_spec.dst_mac,
						match.key->dst);
			}

		if (!is_zero_ether_addr(match.key->src))
			if (is_valid_ether_addr(match.key->src) ||
			    is_multicast_ether_addr(match.key->src)) {
				/* set the mask if a valid dst_mac address */
				for (i = 0; i < ETH_ALEN; i++)
					vf->mask.tcp_spec.src_mac[i] |= 0xff;
				ether_addr_copy(vf->data.tcp_spec.src_mac,
						match.key->src);
		}
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		if (match.mask->vlan_id) {
			if (match.mask->vlan_id == VLAN_VID_MASK) {
				field_flags |= IAVF_CLOUD_FIELD_IVLAN;
			} else {
				dev_err(&adapter->pdev->dev, "Bad vlan mask %u\n",
					match.mask->vlan_id);
				return IAVF_ERR_CONFIG;
			}
		}
		vf->mask.tcp_spec.vlan_id |= cpu_to_be16(0xffff);
		vf->data.tcp_spec.vlan_id = cpu_to_be16(match.key->vlan_id);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_CONTROL)) {
		struct flow_match_control match;

		flow_rule_match_control(rule, &match);
		addr_type = match.key->addr_type;
	}

	if (addr_type == FLOW_DISSECTOR_KEY_IPV4_ADDRS) {
		struct flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		if (match.mask->dst) {
			if (match.mask->dst == cpu_to_be32(0xffffffff)) {
				field_flags |= IAVF_CLOUD_FIELD_IIP;
			} else {
				dev_err(&adapter->pdev->dev, "Bad ip dst mask 0x%08x\n",
					be32_to_cpu(match.mask->dst));
				return IAVF_ERR_CONFIG;
			}
		}

		if (match.mask->src) {
			if (match.mask->src == cpu_to_be32(0xffffffff)) {
				field_flags |= IAVF_CLOUD_FIELD_IIP;
			} else {
				dev_err(&adapter->pdev->dev, "Bad ip src mask 0x%08x\n",
					be32_to_cpu(match.mask->dst));
				return IAVF_ERR_CONFIG;
			}
		}

		if (field_flags & IAVF_CLOUD_FIELD_TEN_ID) {
			dev_info(&adapter->pdev->dev, "Tenant id not allowed for ip filter\n");
			return IAVF_ERR_CONFIG;
		}
		if (match.key->dst) {
			vf->mask.tcp_spec.dst_ip[0] |= cpu_to_be32(0xffffffff);
			vf->data.tcp_spec.dst_ip[0] = match.key->dst;
		}
		if (match.key->src) {
			vf->mask.tcp_spec.src_ip[0] |= cpu_to_be32(0xffffffff);
			vf->data.tcp_spec.src_ip[0] = match.key->src;
		}
	}

	if (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) {
		struct flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);

		/* validate mask, make sure it is not IPV6_ADDR_ANY */
		if (ipv6_addr_any(&match.mask->dst)) {
			dev_err(&adapter->pdev->dev, "Bad ipv6 dst mask 0x%02x\n",
				IPV6_ADDR_ANY);
			return IAVF_ERR_CONFIG;
		}

		/* src and dest IPv6 address should not be LOOPBACK
		 * (0:0:0:0:0:0:0:1) which can be represented as ::1
		 */
		if (ipv6_addr_loopback(&match.key->dst) ||
		    ipv6_addr_loopback(&match.key->src)) {
			dev_err(&adapter->pdev->dev,
				"ipv6 addr should not be loopback\n");
			return IAVF_ERR_CONFIG;
		}
		if (!ipv6_addr_any(&match.mask->dst) ||
		    !ipv6_addr_any(&match.mask->src))
			field_flags |= IAVF_CLOUD_FIELD_IIP;

		for (i = 0; i < 4; i++)
			vf->mask.tcp_spec.dst_ip[i] |= cpu_to_be32(0xffffffff);
		memcpy(&vf->data.tcp_spec.dst_ip, &match.key->dst.s6_addr32,
		       sizeof(vf->data.tcp_spec.dst_ip));
		for (i = 0; i < 4; i++)
			vf->mask.tcp_spec.src_ip[i] |= cpu_to_be32(0xffffffff);
		memcpy(&vf->data.tcp_spec.src_ip, &match.key->src.s6_addr32,
		       sizeof(vf->data.tcp_spec.src_ip));
	}
	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		if (match.mask->src) {
			if (match.mask->src == cpu_to_be16(0xffff)) {
				field_flags |= IAVF_CLOUD_FIELD_IIP;
			} else {
				dev_err(&adapter->pdev->dev, "Bad src port mask %u\n",
					be16_to_cpu(match.mask->src));
				return IAVF_ERR_CONFIG;
			}
		}

		if (match.mask->dst) {
			if (match.mask->dst == cpu_to_be16(0xffff)) {
				field_flags |= IAVF_CLOUD_FIELD_IIP;
			} else {
				dev_err(&adapter->pdev->dev, "Bad dst port mask %u\n",
					be16_to_cpu(match.mask->dst));
				return IAVF_ERR_CONFIG;
			}
		}
		if (match.key->dst) {
			vf->mask.tcp_spec.dst_port |= cpu_to_be16(0xffff);
			vf->data.tcp_spec.dst_port = match.key->dst;
		}

		if (match.key->src) {
			vf->mask.tcp_spec.src_port |= cpu_to_be16(0xffff);
			vf->data.tcp_spec.src_port = match.key->src;
		}
	}
	vf->field_flags = field_flags;

	return 0;
}