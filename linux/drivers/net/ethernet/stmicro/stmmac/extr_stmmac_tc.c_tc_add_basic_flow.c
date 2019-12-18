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
struct stmmac_priv {int dummy; } ;
struct stmmac_flow_entry {int /*<<< orphan*/  ip_proto; } ;
struct TYPE_3__ {struct flow_dissector* dissector; } ;
struct flow_rule {TYPE_1__ match; } ;
struct flow_match_basic {TYPE_2__* key; } ;
struct flow_dissector {int dummy; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip_proto; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_BASIC ; 
 int /*<<< orphan*/  dissector_uses_key (struct flow_dissector*,int /*<<< orphan*/ ) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_basic (struct flow_rule*,struct flow_match_basic*) ; 

__attribute__((used)) static int tc_add_basic_flow(struct stmmac_priv *priv,
			     struct flow_cls_offload *cls,
			     struct stmmac_flow_entry *entry)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(cls);
	struct flow_dissector *dissector = rule->match.dissector;
	struct flow_match_basic match;

	/* Nothing to do here */
	if (!dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_BASIC))
		return -EINVAL;

	flow_rule_match_basic(rule, &match);
	entry->ip_proto = match.key->ip_proto;
	return 0;
}