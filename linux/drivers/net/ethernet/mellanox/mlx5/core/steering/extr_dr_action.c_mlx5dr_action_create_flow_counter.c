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
struct TYPE_2__ {int /*<<< orphan*/  ctr_id; } ;
struct mlx5dr_action {TYPE_1__ ctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_ACTION_TYP_CTR ; 
 struct mlx5dr_action* dr_action_create_generic (int /*<<< orphan*/ ) ; 

struct mlx5dr_action *
mlx5dr_action_create_flow_counter(u32 counter_id)
{
	struct mlx5dr_action *action;

	action = dr_action_create_generic(DR_ACTION_TYP_CTR);
	if (!action)
		return NULL;

	action->ctr.ctr_id = counter_id;

	return action;
}