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
struct qede_arfs_tuple {scalar_t__ dst_port; scalar_t__ src_port; } ;
struct flow_rule {int dummy; } ;
struct flow_match_ports {TYPE_1__* key; TYPE_2__* mask; } ;
struct TYPE_4__ {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_3__ {scalar_t__ dst; scalar_t__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qede_dev*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_PORTS ; 
 scalar_t__ U16_MAX ; 
 scalar_t__ flow_rule_match_key (struct flow_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flow_rule_match_ports (struct flow_rule*,struct flow_match_ports*) ; 

__attribute__((used)) static int
qede_flow_parse_ports(struct qede_dev *edev, struct flow_rule *rule,
		      struct qede_arfs_tuple *t)
{
	if (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_PORTS)) {
		struct flow_match_ports match;

		flow_rule_match_ports(rule, &match);
		if ((match.key->src && match.mask->src != U16_MAX) ||
		    (match.key->dst && match.mask->dst != U16_MAX)) {
			DP_NOTICE(edev, "Do not support ports masks\n");
			return -EINVAL;
		}

		t->src_port = match.key->src;
		t->dst_port = match.key->dst;
	}

	return 0;
}