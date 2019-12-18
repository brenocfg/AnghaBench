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
struct stmmac_priv {int dummy; } ;
struct stmmac_flow_entry {int in_use; int /*<<< orphan*/  cookie; } ;
struct flow_rule {int /*<<< orphan*/  action; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; } ;
struct TYPE_3__ {int (* fn ) (struct stmmac_priv*,struct flow_cls_offload*,struct stmmac_flow_entry*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENOENT ; 
 struct flow_rule* flow_cls_offload_flow_rule (struct flow_cls_offload*) ; 
 int stub1 (struct stmmac_priv*,struct flow_cls_offload*,struct stmmac_flow_entry*) ; 
 struct stmmac_flow_entry* tc_find_flow (struct stmmac_priv*,struct flow_cls_offload*,int) ; 
 TYPE_1__* tc_flow_parsers ; 
 int tc_parse_flow_actions (struct stmmac_priv*,int /*<<< orphan*/ *,struct stmmac_flow_entry*) ; 

__attribute__((used)) static int tc_add_flow(struct stmmac_priv *priv,
		       struct flow_cls_offload *cls)
{
	struct stmmac_flow_entry *entry = tc_find_flow(priv, cls, false);
	struct flow_rule *rule = flow_cls_offload_flow_rule(cls);
	int i, ret;

	if (!entry) {
		entry = tc_find_flow(priv, cls, true);
		if (!entry)
			return -ENOENT;
	}

	ret = tc_parse_flow_actions(priv, &rule->action, entry);
	if (ret)
		return ret;

	for (i = 0; i < ARRAY_SIZE(tc_flow_parsers); i++) {
		ret = tc_flow_parsers[i].fn(priv, cls, entry);
		if (!ret) {
			entry->in_use = true;
			continue;
		}
	}

	if (!entry->in_use)
		return -EINVAL;

	entry->cookie = cls->cookie;
	return 0;
}