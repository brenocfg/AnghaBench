#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_18__ ;
typedef  struct TYPE_26__   TYPE_17__ ;
typedef  struct TYPE_25__   TYPE_16__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct i40e_vsi {struct i40e_pf* back; } ;
struct i40e_pf {TYPE_15__* pdev; } ;
struct i40e_cloud_filter {int ip_proto; int flags; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; int /*<<< orphan*/  src_ipv4; int /*<<< orphan*/  dst_ipv4; scalar_t__ vlan_id; int /*<<< orphan*/  src_mac; int /*<<< orphan*/  dst_mac; scalar_t__ n_proto; int /*<<< orphan*/  tenant_id; } ;
struct TYPE_35__ {struct flow_dissector* dissector; } ;
struct flow_rule {TYPE_8__ match; } ;
struct flow_match_vlan {TYPE_17__* key; TYPE_16__* mask; } ;
struct flow_match_ports {TYPE_7__* key; TYPE_6__* mask; } ;
struct flow_match_ipv6_addrs {TYPE_5__* key; TYPE_4__* mask; } ;
struct flow_match_ipv4_addrs {TYPE_3__* key; TYPE_2__* mask; } ;
struct flow_match_eth_addrs {TYPE_14__* key; TYPE_13__* mask; } ;
struct flow_match_enc_keyid {TYPE_10__* key; TYPE_9__* mask; } ;
struct flow_match_control {TYPE_1__* key; } ;
struct flow_match_basic {TYPE_12__* key; TYPE_11__* mask; } ;
struct flow_dissector {int used_keys; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_36__ {scalar_t__ keyid; } ;
struct TYPE_34__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_33__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_27__ {int /*<<< orphan*/  s6_addr32; } ;
struct TYPE_32__ {TYPE_18__ dst; TYPE_18__ src; } ;
struct TYPE_31__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_30__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_29__ {scalar_t__ dst; scalar_t__ src; } ;
struct TYPE_28__ {scalar_t__ addr_type; } ;
struct TYPE_26__ {int vlan_id; } ;
struct TYPE_25__ {int vlan_id; } ;
struct TYPE_24__ {int /*<<< orphan*/  dev; } ;
struct TYPE_23__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_22__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct TYPE_21__ {int ip_proto; int /*<<< orphan*/  n_proto; } ;
struct TYPE_20__ {int /*<<< orphan*/  n_proto; } ;
struct TYPE_19__ {int /*<<< orphan*/  keyid; } ;

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
 int VLAN_VID_MASK ; 
 int /*<<< orphan*/  be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be16 (int) ; 
 scalar_t__ cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
 int /*<<< orphan*/  ipv6_addr_any (int /*<<< orphan*/ *) ; 
 scalar_t__ ipv6_addr_loopback (TYPE_18__*) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_parse_cls_flower(struct i40e_vsi *vsi,
				 struct flow_cls_offload *f,
				 struct i40e_cloud_filter *filter)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(f);
	struct flow_dissector *dissector = rule->match.dissector;
	u16 n_proto_mask = 0, n_proto_key = 0, addr_type = 0;
	struct i40e_pf *pf = vsi->back;
	u8 field_flags = 0;

	if (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_VLAN) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS) |
	      BIT(FLOW_DISSECTOR_KEY_ENC_KEYID))) {
		dev_err(&pf->pdev->dev, "Unsupported key used: 0x%x\n",
			dissector->used_keys);
		return -EOPNOTSUPP;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ENC_KEYID)) {
		struct flow_match_enc_keyid match;

		flow_rule_match_enc_keyid(rule, &match);
		if (match.mask->keyid != 0)
			field_flags |= I40E_CLOUD_FIELD_TEN_ID;

		filter->tenant_id = be32_to_cpu(match.key->keyid);
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
		filter->n_proto = n_proto_key & n_proto_mask;
		filter->ip_proto = match.key->ip_proto;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) {
		struct flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);

		/* use is_broadcast and is_zero to check for all 0xf or 0 */
		if (!is_zero_ether_addr(match.mask->dst)) {
			if (is_broadcast_ether_addr(match.mask->dst)) {
				field_flags |= I40E_CLOUD_FIELD_OMAC;
			} else {
				dev_err(&pf->pdev->dev, "Bad ether dest mask %pM\n",
					match.mask->dst);
				return I40E_ERR_CONFIG;
			}
		}

		if (!is_zero_ether_addr(match.mask->src)) {
			if (is_broadcast_ether_addr(match.mask->src)) {
				field_flags |= I40E_CLOUD_FIELD_IMAC;
			} else {
				dev_err(&pf->pdev->dev, "Bad ether src mask %pM\n",
					match.mask->src);
				return I40E_ERR_CONFIG;
			}
		}
		ether_addr_copy(filter->dst_mac, match.key->dst);
		ether_addr_copy(filter->src_mac, match.key->src);
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) {
		struct flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		if (match.mask->vlan_id) {
			if (match.mask->vlan_id == VLAN_VID_MASK) {
				field_flags |= I40E_CLOUD_FIELD_IVLAN;

			} else {
				dev_err(&pf->pdev->dev, "Bad vlan mask 0x%04x\n",
					match.mask->vlan_id);
				return I40E_ERR_CONFIG;
			}
		}

		filter->vlan_id = cpu_to_be16(match.key->vlan_id);
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
				field_flags |= I40E_CLOUD_FIELD_IIP;
			} else {
				dev_err(&pf->pdev->dev, "Bad ip dst mask %pI4b\n",
					&match.mask->dst);
				return I40E_ERR_CONFIG;
			}
		}

		if (match.mask->src) {
			if (match.mask->src == cpu_to_be32(0xffffffff)) {
				field_flags |= I40E_CLOUD_FIELD_IIP;
			} else {
				dev_err(&pf->pdev->dev, "Bad ip src mask %pI4b\n",
					&match.mask->src);
				return I40E_ERR_CONFIG;
			}
		}

		if (field_flags & I40E_CLOUD_FIELD_TEN_ID) {
			dev_err(&pf->pdev->dev, "Tenant id not allowed for ip filter\n");
			return I40E_ERR_CONFIG;
		}
		filter->dst_ipv4 = match.key->dst;
		filter->src_ipv4 = match.key->src;
	}

	if (addr_type == FLOW_DISSECTOR_KEY_IPV6_ADDRS) {
		struct flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);

		/* src and dest IPV6 address should not be LOOPBACK
		 * (0:0:0:0:0:0:0:1), which can be represented as ::1
		 */
		if (ipv6_addr_loopback(&match.key->dst) ||
		    ipv6_addr_loopback(&match.key->src)) {
			dev_err(&pf->pdev->dev,
				"Bad ipv6, addr is LOOPBACK\n");
			return I40E_ERR_CONFIG;
		}
		if (!ipv6_addr_any(&match.mask->dst) ||
		    !ipv6_addr_any(&match.mask->src))
			field_flags |= I40E_CLOUD_FIELD_IIP;

		memcpy(&filter->src_ipv6, &match.key->src.s6_addr32,
		       sizeof(filter->src_ipv6));
		memcpy(&filter->dst_ipv6, &match.key->dst.s6_addr32,
		       sizeof(filter->dst_ipv6));
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		if (match.mask->src) {
			if (match.mask->src == cpu_to_be16(0xffff)) {
				field_flags |= I40E_CLOUD_FIELD_IIP;
			} else {
				dev_err(&pf->pdev->dev, "Bad src port mask 0x%04x\n",
					be16_to_cpu(match.mask->src));
				return I40E_ERR_CONFIG;
			}
		}

		if (match.mask->dst) {
			if (match.mask->dst == cpu_to_be16(0xffff)) {
				field_flags |= I40E_CLOUD_FIELD_IIP;
			} else {
				dev_err(&pf->pdev->dev, "Bad dst port mask 0x%04x\n",
					be16_to_cpu(match.mask->dst));
				return I40E_ERR_CONFIG;
			}
		}

		filter->dst_port = match.key->dst;
		filter->src_port = match.key->src;

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