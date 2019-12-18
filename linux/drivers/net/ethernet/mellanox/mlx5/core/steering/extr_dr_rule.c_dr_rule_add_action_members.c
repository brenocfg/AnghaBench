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
struct mlx5dr_rule_action_member {struct mlx5dr_action* action; int /*<<< orphan*/  list; } ;
struct mlx5dr_rule {int /*<<< orphan*/  rule_actions_list; } ;
struct mlx5dr_action {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dr_rule_remove_action_members (struct mlx5dr_rule*) ; 
 struct mlx5dr_rule_action_member* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dr_rule_add_action_members(struct mlx5dr_rule *rule,
				      size_t num_actions,
				      struct mlx5dr_action *actions[])
{
	struct mlx5dr_rule_action_member *action_mem;
	int i;

	for (i = 0; i < num_actions; i++) {
		action_mem = kvzalloc(sizeof(*action_mem), GFP_KERNEL);
		if (!action_mem)
			goto free_action_members;

		action_mem->action = actions[i];
		INIT_LIST_HEAD(&action_mem->list);
		list_add_tail(&action_mem->list, &rule->rule_actions_list);
		refcount_inc(&action_mem->action->refcount);
	}

	return 0;

free_action_members:
	dr_rule_remove_action_members(rule);
	return -ENOMEM;
}