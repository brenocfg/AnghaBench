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
struct stmmac_priv {int /*<<< orphan*/  hw; } ;
struct stmmac_flow_entry {int in_use; int is_l4; scalar_t__ cookie; int /*<<< orphan*/  idx; } ;
struct flow_cls_offload {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int stmmac_config_l3_filter (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 int stmmac_config_l4_filter (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 
 struct stmmac_flow_entry* tc_find_flow (struct stmmac_priv*,struct flow_cls_offload*,int) ; 

__attribute__((used)) static int tc_del_flow(struct stmmac_priv *priv,
		       struct flow_cls_offload *cls)
{
	struct stmmac_flow_entry *entry = tc_find_flow(priv, cls, false);
	int ret;

	if (!entry || !entry->in_use)
		return -ENOENT;

	if (entry->is_l4) {
		ret = stmmac_config_l4_filter(priv, priv->hw, entry->idx, false,
					      false, false, false, 0);
	} else {
		ret = stmmac_config_l3_filter(priv, priv->hw, entry->idx, false,
					      false, false, false, 0);
	}

	entry->in_use = false;
	entry->cookie = 0;
	entry->is_l4 = false;
	return ret;
}