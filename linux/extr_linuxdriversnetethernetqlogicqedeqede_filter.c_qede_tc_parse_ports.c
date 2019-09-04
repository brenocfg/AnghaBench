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
struct qede_arfs_tuple {scalar_t__ src_port; scalar_t__ dst_port; } ;
struct flow_dissector_key_ports {scalar_t__ src; scalar_t__ dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_PORTS ; 
 scalar_t__ U16_MAX ; 
 scalar_t__ dissector_uses_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct flow_dissector_key_ports* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qede_tc_parse_ports(struct qede_dev *edev,
		    struct tc_cls_flower_offload *f,
		    struct qede_arfs_tuple *t)
{
	if (dissector_uses_key(f->dissector, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_dissector_key_ports *key, *mask;

		key = skb_flow_dissector_target(f->dissector,
						FLOW_DISSECTOR_KEY_PORTS,
						f->key);
		mask = skb_flow_dissector_target(f->dissector,
						 FLOW_DISSECTOR_KEY_PORTS,
						 f->mask);

		if ((key->src && mask->src != U16_MAX) ||
		    (key->dst && mask->dst != U16_MAX)) {
			DP_NOTICE(edev, "Do not support ports masks\n");
			return -EINVAL;
		}

		t->src_port = key->src;
		t->dst_port = key->dst;
	}

	return 0;
}