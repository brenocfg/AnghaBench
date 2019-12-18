#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int action; } ;
struct TYPE_7__ {scalar_t__ type; TYPE_2__* ft; } ;
struct TYPE_5__ {struct fs_node* parent; } ;
struct mlx5_flow_rule {scalar_t__ sw_action; int modify_mask; scalar_t__ dests_size; TYPE_4__ action; TYPE_3__ dest_attr; int /*<<< orphan*/  next_ft; TYPE_1__ node; } ;
struct fs_node {int dummy; } ;
struct fs_fte {scalar_t__ sw_action; int modify_mask; scalar_t__ dests_size; TYPE_4__ action; TYPE_3__ dest_attr; int /*<<< orphan*/  next_ft; TYPE_1__ node; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int MLX5_FLOW_CONTEXT_ACTION_COUNT ; 
 int MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 scalar_t__ MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO ; 
 scalar_t__ MLX5_FLOW_DESTINATION_TYPE_COUNTER ; 
 int /*<<< orphan*/  MLX5_SET_FTE_MODIFY_ENABLE_MASK_ACTION ; 
 int /*<<< orphan*/  MLX5_SET_FTE_MODIFY_ENABLE_MASK_DESTINATION_LIST ; 
 int /*<<< orphan*/  MLX5_SET_FTE_MODIFY_ENABLE_MASK_FLOW_COUNTERS ; 
 int /*<<< orphan*/  fs_get_obj (struct mlx5_flow_rule*,struct fs_node*) ; 
 int /*<<< orphan*/  kfree (struct mlx5_flow_rule*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mlx5_fs_del_rule (struct mlx5_flow_rule*) ; 

__attribute__((used)) static void del_sw_hw_rule(struct fs_node *node)
{
	struct mlx5_flow_rule *rule;
	struct fs_fte *fte;

	fs_get_obj(rule, node);
	fs_get_obj(fte, rule->node.parent);
	trace_mlx5_fs_del_rule(rule);
	if (rule->sw_action == MLX5_FLOW_CONTEXT_ACTION_FWD_NEXT_PRIO) {
		mutex_lock(&rule->dest_attr.ft->lock);
		list_del(&rule->next_ft);
		mutex_unlock(&rule->dest_attr.ft->lock);
	}

	if (rule->dest_attr.type == MLX5_FLOW_DESTINATION_TYPE_COUNTER  &&
	    --fte->dests_size) {
		fte->modify_mask |=
			BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_ACTION) |
			BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_FLOW_COUNTERS);
		fte->action.action &= ~MLX5_FLOW_CONTEXT_ACTION_COUNT;
		goto out;
	}

	if ((fte->action.action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) &&
	    --fte->dests_size) {
		fte->modify_mask |=
			BIT(MLX5_SET_FTE_MODIFY_ENABLE_MASK_DESTINATION_LIST);
	}
out:
	kfree(rule);
}