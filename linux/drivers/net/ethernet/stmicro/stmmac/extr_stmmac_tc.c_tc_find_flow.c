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
struct stmmac_priv {int flow_entries_max; struct stmmac_flow_entry* flow_entries; } ;
struct stmmac_flow_entry {scalar_t__ cookie; int in_use; } ;
struct flow_cls_offload {scalar_t__ cookie; } ;

/* Variables and functions */

__attribute__((used)) static struct stmmac_flow_entry *tc_find_flow(struct stmmac_priv *priv,
					      struct flow_cls_offload *cls,
					      bool get_free)
{
	int i;

	for (i = 0; i < priv->flow_entries_max; i++) {
		struct stmmac_flow_entry *entry = &priv->flow_entries[i];

		if (entry->cookie == cls->cookie)
			return entry;
		if (get_free && (entry->in_use == false))
			return entry;
	}

	return NULL;
}