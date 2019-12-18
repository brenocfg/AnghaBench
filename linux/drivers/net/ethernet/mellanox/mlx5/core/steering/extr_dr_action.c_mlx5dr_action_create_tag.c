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
typedef  int u32 ;
struct mlx5dr_action {int flow_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_ACTION_TYP_TAG ; 
 struct mlx5dr_action* dr_action_create_generic (int /*<<< orphan*/ ) ; 

struct mlx5dr_action *mlx5dr_action_create_tag(u32 tag_value)
{
	struct mlx5dr_action *action;

	action = dr_action_create_generic(DR_ACTION_TYP_TAG);
	if (!action)
		return NULL;

	action->flow_tag = tag_value & 0xffffff;

	return action;
}