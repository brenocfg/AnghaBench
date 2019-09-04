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
struct qede_arfs_tuple {scalar_t__ src_ipv4; scalar_t__ dst_ipv4; } ;
struct flow_dissector_key_ipv4_addrs {scalar_t__ src; scalar_t__ dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 scalar_t__ U32_MAX ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qede_set_v4_tuple_to_profile (struct qede_dev*,struct qede_arfs_tuple*) ; 
 scalar_t__ qede_tc_parse_ports (struct qede_dev*,struct tc_cls_flower_offload*,struct qede_arfs_tuple*) ; 
 struct flow_dissector_key_ipv4_addrs* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qede_tc_parse_v4_common(struct qede_dev *edev,
			struct tc_cls_flower_offload *f,
			struct qede_arfs_tuple *t)
{
	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_IPV4_ADDRS)) {
		struct flow_dissector_key_ipv4_addrs *key, *mask;

		key = skb_flow_dissector_target(f->dissector,
						FLOW_DISSECTOR_KEY_IPV4_ADDRS,
						f->key);
		mask = skb_flow_dissector_target(f->dissector,
						 FLOW_DISSECTOR_KEY_IPV4_ADDRS,
						 f->mask);

		if ((key->src && mask->src != U32_MAX) ||
		    (key->dst && mask->dst != U32_MAX)) {
			DP_NOTICE(edev, "Do not support ipv4 prefix/masks\n");
			return -EINVAL;
		}

		t->src_ipv4 = key->src;
		t->dst_ipv4 = key->dst;
	}

	if (qede_tc_parse_ports(edev, f, t))
		return -EINVAL;

	return qede_set_v4_tuple_to_profile(edev, t);
}