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
struct qede_arfs_tuple {int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; } ;
struct in6_addr {int dummy; } ;
struct flow_rule {int dummy; } ;
struct flow_match_ipv6_addrs {TYPE_2__* key; TYPE_1__* mask; } ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_4__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 int /*<<< orphan*/  flow_rule_match_ipv6_addrs (struct flow_rule*,struct flow_match_ipv6_addrs*) ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct in6_addr*,int,int) ; 
 scalar_t__ qede_flow_parse_ports (struct qede_dev*,struct flow_rule*,struct qede_arfs_tuple*) ; 
 int qede_set_v6_tuple_to_profile (struct qede_dev*,struct qede_arfs_tuple*,struct in6_addr*) ; 

__attribute__((used)) static int
qede_flow_parse_v6_common(struct qede_dev *edev, struct flow_rule *rule,
			  struct qede_arfs_tuple *t)
{
	struct in6_addr zero_addr, addr;

	memset(&zero_addr, 0, sizeof(addr));
	memset(&addr, 0xff, sizeof(addr));

	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_IPV6_ADDRS)) {
		struct flow_match_ipv6_addrs match;

		flow_rule_match_ipv6_addrs(rule, &match);
		if ((memcmp(&match.key->src, &zero_addr, sizeof(addr)) &&
		     memcmp(&match.mask->src, &addr, sizeof(addr))) ||
		    (memcmp(&match.key->dst, &zero_addr, sizeof(addr)) &&
		     memcmp(&match.mask->dst, &addr, sizeof(addr)))) {
			DP_NOTICE(edev,
				  "Do not support IPv6 address prefix/mask\n");
			return -EINVAL;
		}

		memcpy(&t->src_ipv6, &match.key->src, sizeof(addr));
		memcpy(&t->dst_ipv6, &match.key->dst, sizeof(addr));
	}

	if (qede_flow_parse_ports(edev, rule, t))
		return -EINVAL;

	return qede_set_v6_tuple_to_profile(edev, t, &zero_addr);
}