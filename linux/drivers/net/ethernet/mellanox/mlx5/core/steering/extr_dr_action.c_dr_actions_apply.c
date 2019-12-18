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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mlx5dr_domain {int dummy; } ;
struct dr_action_apply_attr {int /*<<< orphan*/  final_icm_addr; int /*<<< orphan*/  hit_gvmi; } ;
typedef  enum mlx5dr_ste_entry_type { ____Placeholder_mlx5dr_ste_entry_type } mlx5dr_ste_entry_type ;

/* Variables and functions */
 int DR_STE_SIZE ; 
 int MLX5DR_STE_TYPE_RX ; 
 int /*<<< orphan*/  dr_actions_apply_rx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dr_action_apply_attr*,int*) ; 
 int /*<<< orphan*/  dr_actions_apply_tx (struct mlx5dr_domain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dr_action_apply_attr*,int*) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_hit_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_hit_gvmi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dr_actions_apply(struct mlx5dr_domain *dmn,
			     enum mlx5dr_ste_entry_type ste_type,
			     u8 *action_type_set,
			     u8 *last_ste,
			     struct dr_action_apply_attr *attr,
			     u32 *new_num_stes)
{
	u32 added_stes = 0;

	if (ste_type == MLX5DR_STE_TYPE_RX)
		dr_actions_apply_rx(action_type_set, last_ste, attr, &added_stes);
	else
		dr_actions_apply_tx(dmn, action_type_set, last_ste, attr, &added_stes);

	last_ste += added_stes * DR_STE_SIZE;
	*new_num_stes += added_stes;

	mlx5dr_ste_set_hit_gvmi(last_ste, attr->hit_gvmi);
	mlx5dr_ste_set_hit_addr(last_ste, attr->final_icm_addr, 1);
}