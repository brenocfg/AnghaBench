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
struct flow_cls_offload {int /*<<< orphan*/  stats; int /*<<< orphan*/  cookie; } ;
struct bnxt_tc_info {int /*<<< orphan*/  flow_ht_params; int /*<<< orphan*/  flow_table; } ;
struct bnxt_tc_flow_stats {scalar_t__ packets; scalar_t__ bytes; } ;
struct bnxt_tc_flow {unsigned long lastused; int /*<<< orphan*/  stats_lock; struct bnxt_tc_flow_stats prev_stats; struct bnxt_tc_flow_stats stats; } ;
struct bnxt_tc_flow_node {struct bnxt_tc_flow flow; } ;
struct bnxt {struct bnxt_tc_info* tc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_stats_update (int /*<<< orphan*/ *,scalar_t__,scalar_t__,unsigned long) ; 
 struct bnxt_tc_flow_node* rhashtable_lookup_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnxt_tc_get_flow_stats(struct bnxt *bp,
				  struct flow_cls_offload *tc_flow_cmd)
{
	struct bnxt_tc_flow_stats stats, *curr_stats, *prev_stats;
	struct bnxt_tc_info *tc_info = bp->tc_info;
	struct bnxt_tc_flow_node *flow_node;
	struct bnxt_tc_flow *flow;
	unsigned long lastused;

	flow_node = rhashtable_lookup_fast(&tc_info->flow_table,
					   &tc_flow_cmd->cookie,
					   tc_info->flow_ht_params);
	if (!flow_node)
		return -1;

	flow = &flow_node->flow;
	curr_stats = &flow->stats;
	prev_stats = &flow->prev_stats;

	spin_lock(&flow->stats_lock);
	stats.packets = curr_stats->packets - prev_stats->packets;
	stats.bytes = curr_stats->bytes - prev_stats->bytes;
	*prev_stats = *curr_stats;
	lastused = flow->lastused;
	spin_unlock(&flow->stats_lock);

	flow_stats_update(&tc_flow_cmd->stats, stats.bytes, stats.packets,
			  lastused);
	return 0;
}