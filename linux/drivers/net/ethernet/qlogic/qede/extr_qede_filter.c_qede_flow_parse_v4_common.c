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
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {scalar_t__ dst_ipv4; scalar_t__ src_ipv4; } ;
struct flow_rule {int dummy; } ;
struct flow_match_ipv4_addrs {TYPE_2__* key; TYPE_1__* mask; } ;
struct TYPE_4__ {scalar_t__ dst; scalar_t__ src; } ;
struct TYPE_3__ {scalar_t__ src; scalar_t__ dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 scalar_t__ U32_MAX ; 
 int /*<<< orphan*/  flow_rule_match_ipv4_addrs (struct flow_rule*,struct flow_match_ipv4_addrs*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 scalar_t__ qede_flow_parse_ports (struct qede_dev*,struct flow_rule*,struct qede_arfs_tuple*) ; 
 int qede_set_v4_tuple_to_profile (struct qede_dev*,struct qede_arfs_tuple*) ; 

__attribute__((used)) static int
qede_flow_parse_v4_common(struct qede_dev *edev, struct flow_rule *rule,
			struct qede_arfs_tuple *t)
{
	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) {
		struct flow_match_ipv4_addrs match;

		flow_rule_match_ipv4_addrs(rule, &match);
		if ((match.key->src && match.mask->src != U32_MAX) ||
		    (match.key->dst && match.mask->dst != U32_MAX)) {
			DP_NOTICE(edev, "Do not support ipv4 prefix/masks\n");
			return -EINVAL;
		}

		t->src_ipv4 = match.key->src;
		t->dst_ipv4 = match.key->dst;
	}

	if (qede_flow_parse_ports(edev, rule, t))
		return -EINVAL;

	return qede_set_v4_tuple_to_profile(edev, t);
}