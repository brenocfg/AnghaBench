#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tc_cls_flower_offload {int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; int /*<<< orphan*/  key; } ;
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; } ;
struct in6_addr {int dummy; } ;
struct flow_dissector_key_ipv6_addrs {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV6_ADDRS ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct in6_addr*,int,int) ; 
 int qede_set_v6_tuple_to_profile (struct qede_dev*,struct qede_arfs_tuple*,struct in6_addr*) ; 
 scalar_t__ qede_tc_parse_ports (struct qede_dev*,struct tc_cls_flower_offload*,struct qede_arfs_tuple*) ; 
 struct flow_dissector_key_ipv6_addrs* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qede_tc_parse_v6_common(struct qede_dev *edev,
			struct tc_cls_flower_offload *f,
			struct qede_arfs_tuple *t)
{
	struct in6_addr zero_addr, addr;

	memset(&zero_addr, 0, sizeof(addr));
	memset(&addr, 0xff, sizeof(addr));

	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_IPV6_ADDRS)) {
		struct flow_dissector_key_ipv6_addrs *key, *mask;

		key = skb_flow_dissector_target(f->dissector,
						FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						f->key);
		mask = skb_flow_dissector_target(f->dissector,
						 FLOW_DISSECTOR_KEY_IPV6_ADDRS,
						 f->mask);

		if ((memcmp(&key->src, &zero_addr, sizeof(addr)) &&
		     memcmp(&mask->src, &addr, sizeof(addr))) ||
		    (memcmp(&key->dst, &zero_addr, sizeof(addr)) &&
		     memcmp(&mask->dst, &addr, sizeof(addr)))) {
			DP_NOTICE(edev,
				  "Do not support IPv6 address prefix/mask\n");
			return -EINVAL;
		}

		memcpy(&t->src_ipv6, &key->src, sizeof(addr));
		memcpy(&t->dst_ipv6, &key->dst, sizeof(addr));
	}

	if (qede_tc_parse_ports(edev, f, t))
		return -EINVAL;

	return qede_set_v6_tuple_to_profile(edev, t, &zero_addr);
}