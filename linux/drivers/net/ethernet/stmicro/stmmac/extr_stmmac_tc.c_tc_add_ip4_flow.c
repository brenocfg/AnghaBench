#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stmmac_priv {int /*<<< orphan*/  hw; } ;
struct stmmac_flow_entry {int action; int /*<<< orphan*/  idx; } ;
struct TYPE_4__ {struct flow_dissector* dissector; } ;
struct flow_rule {TYPE_1__ match; } ;
struct flow_match_ipv4_addrs {TYPE_3__* mask; TYPE_2__* key; } ;
struct flow_dissector {int dummy; } ;
struct flow_cls_offload {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_5__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_IPV4_ADDRS ; 
 int STMMAC_FLOW_ACTION_DROP ; 
 int /*<<< orphan*/  dissector_uses_key (struct flow_dissector*,int /*<<< orphan*/ ) ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int /*<<< orphan*/  flow_rule_match_ipv4_addrs (struct flow_rule*,struct flow_match_ipv4_addrs*) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int stmmac_config_l3_filter (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static int tc_add_ip4_flow(struct stmmac_priv *priv,
			   struct flow_cls_offload *cls,
			   struct stmmac_flow_entry *entry)
{
	struct flow_rule *rule = flow_cls_offload_flow_rule(cls);
	struct flow_dissector *dissector = rule->match.dissector;
	bool inv = entry->action & STMMAC_FLOW_ACTION_DROP;
	struct flow_match_ipv4_addrs match;
	u32 hw_match;
	int ret;

	/* Nothing to do here */
	if (!dissector_uses_key(dissector, FLOW_DISSECTOR_KEY_IPV4_ADDRS))
		return -EINVAL;

	flow_rule_match_ipv4_addrs(rule, &match);
	hw_match = ntohl(match.key->src) & ntohl(match.mask->src);
	if (hw_match) {
		ret = stmmac_config_l3_filter(priv, priv->hw, entry->idx, true,
					      false, true, inv, hw_match);
		if (ret)
			return ret;
	}

	hw_match = ntohl(match.key->dst) & ntohl(match.mask->dst);
	if (hw_match) {
		ret = stmmac_config_l3_filter(priv, priv->hw, entry->idx, true,
					      false, false, inv, hw_match);
		if (ret)
			return ret;
	}

	return 0;
}