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
struct flow_cls_offload {TYPE_2__* rule; } ;
struct flow_action_entry {scalar_t__ id; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int num_entries; struct flow_action_entry* entries; } ;
struct TYPE_4__ {TYPE_1__ action; } ;

/* Variables and functions */
 scalar_t__ FLOW_ACTION_MIRRED ; 
 scalar_t__ FLOW_ACTION_REDIRECT ; 
 int netif_is_gretap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nfp_flower_tun_is_gre(struct flow_cls_offload *flow, int start_idx)
{
	struct flow_action_entry *act = flow->rule->action.entries;
	int num_act = flow->rule->action.num_entries;
	int act_idx;

	/* Preparse action list for next mirred or redirect action */
	for (act_idx = start_idx + 1; act_idx < num_act; act_idx++)
		if (act[act_idx].id == FLOW_ACTION_REDIRECT ||
		    act[act_idx].id == FLOW_ACTION_MIRRED)
			return netif_is_gretap(act[act_idx].dev);

	return false;
}