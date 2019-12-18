#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5dr_domain {int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {struct mlx5dr_domain* dmn; } ;
struct mlx5dr_action {TYPE_1__ rewrite; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  DR_ACTION_TYP_MODIFY_HDR ; 
 size_t DR_MODIFY_ACTION_SIZE ; 
 struct mlx5dr_action* dr_action_create_generic (int /*<<< orphan*/ ) ; 
 int dr_action_create_modify_action (struct mlx5dr_domain*,size_t,int /*<<< orphan*/ *,struct mlx5dr_action*) ; 
 int /*<<< orphan*/  kfree (struct mlx5dr_action*) ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*,...) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

struct mlx5dr_action *
mlx5dr_action_create_modify_header(struct mlx5dr_domain *dmn,
				   u32 flags,
				   size_t actions_sz,
				   __be64 actions[])
{
	struct mlx5dr_action *action;
	int ret = 0;

	refcount_inc(&dmn->refcount);

	if (actions_sz % DR_MODIFY_ACTION_SIZE) {
		mlx5dr_dbg(dmn, "Invalid modify actions size provided\n");
		goto dec_ref;
	}

	action = dr_action_create_generic(DR_ACTION_TYP_MODIFY_HDR);
	if (!action)
		goto dec_ref;

	action->rewrite.dmn = dmn;

	ret = dr_action_create_modify_action(dmn,
					     actions_sz,
					     actions,
					     action);
	if (ret) {
		mlx5dr_dbg(dmn, "Failed creating modify header action %d\n", ret);
		goto free_action;
	}

	return action;

free_action:
	kfree(action);
dec_ref:
	refcount_dec(&dmn->refcount);
	return NULL;
}