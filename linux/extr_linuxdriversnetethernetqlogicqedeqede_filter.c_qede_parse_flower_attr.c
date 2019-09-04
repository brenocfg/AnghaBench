#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct tc_cls_flower_offload {int /*<<< orphan*/  key; TYPE_1__* dissector; } ;
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {int dummy; } ;
struct flow_dissector_key_basic {scalar_t__ ip_proto; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_3__ {int used_keys; } ;

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
 scalar_t__ dissector_uses_key (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qede_arfs_tuple*,int /*<<< orphan*/ ,int) ; 
 int qede_tc_parse_tcp_v4 (struct qede_dev*,struct tc_cls_flower_offload*,struct qede_arfs_tuple*) ; 
 int qede_tc_parse_tcp_v6 (struct qede_dev*,struct tc_cls_flower_offload*,struct qede_arfs_tuple*) ; 
 int qede_tc_parse_udp_v4 (struct qede_dev*,struct tc_cls_flower_offload*,struct qede_arfs_tuple*) ; 
 int qede_tc_parse_udp_v6 (struct qede_dev*,struct tc_cls_flower_offload*,struct qede_arfs_tuple*) ; 
 struct flow_dissector_key_basic* skb_flow_dissector_target (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qede_parse_flower_attr(struct qede_dev *edev, __be16 proto,
		       struct tc_cls_flower_offload *f,
		       struct qede_arfs_tuple *tuple)
{
	int rc = -EINVAL;
	u8 ip_proto = 0;

	memset(tuple, 0, sizeof(*tuple));

	if (f->dissector->used_keys &
	    ~(BIT(FLOW_DISSECTOR_KEY_CONTROL) |
	      BIT(FLOW_DISSECTOR_KEY_IPV4_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_BASIC) |
	      BIT(FLOW_DISSECTOR_KEY_IPV6_ADDRS) |
	      BIT(FLOW_DISSECTOR_KEY_PORTS))) {
		DP_NOTICE(edev, "Unsupported key set:0x%x\n",
			  f->dissector->used_keys);
		return -EOPNOTSUPP;
	}

	if (proto != htons(ETH_P_IP) &&
	    proto != htons(ETH_P_IPV6)) {
		DP_NOTICE(edev, "Unsupported proto=0x%x\n", proto);
		return -EPROTONOSUPPORT;
	}

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_BASIC)) {
		struct flow_dissector_key_basic *key;

		key = skb_flow_dissector_target(f->dissector,
						FLOW_DISSECTOR_KEY_BASIC,
						f->key);
		ip_proto = key->ip_proto;
	}

	if (ip_proto == IPPROTO_TCP && proto == htons(ETH_P_IP))
		rc = qede_tc_parse_tcp_v4(edev, f, tuple);
	else if (ip_proto == IPPROTO_TCP && proto == htons(ETH_P_IPV6))
		rc = qede_tc_parse_tcp_v6(edev, f, tuple);
	else if (ip_proto == IPPROTO_UDP && proto == htons(ETH_P_IP))
		rc = qede_tc_parse_udp_v4(edev, f, tuple);
	else if (ip_proto == IPPROTO_UDP && proto == htons(ETH_P_IPV6))
		rc = qede_tc_parse_udp_v6(edev, f, tuple);
	else
		DP_NOTICE(edev, "Invalid tc protocol request\n");

	return rc;
}