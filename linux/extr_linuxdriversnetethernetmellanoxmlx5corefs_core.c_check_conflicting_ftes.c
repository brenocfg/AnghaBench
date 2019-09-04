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
struct mlx5_flow_act {scalar_t__ flow_tag; scalar_t__ has_flow_tag; int /*<<< orphan*/  action; } ;
struct TYPE_2__ {scalar_t__ flow_tag; int /*<<< orphan*/  action; } ;
struct fs_fte {TYPE_1__ action; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ check_conflicting_actions (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int check_conflicting_ftes(struct fs_fte *fte, const struct mlx5_flow_act *flow_act)
{
	if (check_conflicting_actions(flow_act->action, fte->action.action)) {
		mlx5_core_warn(get_dev(&fte->node),
			       "Found two FTEs with conflicting actions\n");
		return -EEXIST;
	}

	if (flow_act->has_flow_tag &&
	    fte->action.flow_tag != flow_act->flow_tag) {
		mlx5_core_warn(get_dev(&fte->node),
			       "FTE flow tag %u already exists with different flow tag %u\n",
			       fte->action.flow_tag,
			       flow_act->flow_tag);
		return -EEXIST;
	}

	return 0;
}