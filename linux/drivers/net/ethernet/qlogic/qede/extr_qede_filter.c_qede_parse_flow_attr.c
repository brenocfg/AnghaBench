#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {int dummy; } ;
struct TYPE_3__ {struct flow_dissector* dissector; } ;
struct flow_rule {TYPE_1__ match; } ;
struct flow_match_basic {TYPE_2__* key; } ;
struct flow_dissector {int used_keys; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {scalar_t__ ip_proto; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*,...) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_CONTROL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_PORTS ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  flow_rule_match_basic (struct flow_rule*,struct flow_match_basic*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qede_arfs_tuple*,int /*<<< orphan*/ ,int) ; 
 int qede_flow_parse_tcp_v4 (struct qede_dev*,struct flow_rule*,struct qede_arfs_tuple*) ; 
 int qede_flow_parse_tcp_v6 (struct qede_dev*,struct flow_rule*,struct qede_arfs_tuple*) ; 
 int qede_flow_parse_udp_v4 (struct qede_dev*,struct flow_rule*,struct qede_arfs_tuple*) ; 
 int qede_flow_parse_udp_v6 (struct qede_dev*,struct flow_rule*,struct qede_arfs_tuple*) ; 

__attribute__((used)) static int
qede_parse_flow_attr(struct qede_dev *edev, __be16 proto,
		     struct flow_rule *rule, struct qede_arfs_tuple *tuple)
{
	struct flow_dissector *dissector = rule->match.dissector;
	int rc = -EINVAL;
	u8 ip_proto = 0;

	memset(tuple, 0, sizeof(*tuple));

	if (dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS))) {
		DP_NOTICE(edev, "Unsupported key set:0x%x\n",
			  dissector->used_keys);
		return -EOPNOTSUPP;
	}

	if (proto != htons(ETH_P_IP) &&
	    proto != htons(ETH_P_IPV6)) {
		DP_NOTICE(edev, "Unsupported proto=0x%x\n", proto);
		return -EPROTONOSUPPORT;
	}

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_match_basic match;

		flow_rule_match_basic(rule, &match);
		ip_proto = match.key->ip_proto;
	}

	if (ip_proto == IPPROTO_TCP && proto == htons(ETH_P_IP))
		rc = qede_flow_parse_tcp_v4(edev, rule, tuple);
	else if (ip_proto == IPPROTO_TCP && proto == htons(ETH_P_IPV6))
		rc = qede_flow_parse_tcp_v6(edev, rule, tuple);
	else if (ip_proto == IPPROTO_UDP && proto == htons(ETH_P_IP))
		rc = qede_flow_parse_udp_v4(edev, rule, tuple);
	else if (ip_proto == IPPROTO_UDP && proto == htons(ETH_P_IPV6))
		rc = qede_flow_parse_udp_v6(edev, rule, tuple);
	else
		DP_NOTICE(edev, "Invalid protocol request\n");

	return rc;
}