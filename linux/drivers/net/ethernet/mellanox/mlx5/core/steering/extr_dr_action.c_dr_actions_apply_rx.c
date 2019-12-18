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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int count; } ;
struct dr_action_apply_attr {int /*<<< orphan*/  flow_tag; int /*<<< orphan*/  gvmi; int /*<<< orphan*/  modify_index; int /*<<< orphan*/  modify_actions; TYPE_1__ vlans; int /*<<< orphan*/  decap_index; int /*<<< orphan*/  decap_actions; int /*<<< orphan*/  decap_with_vlan; int /*<<< orphan*/  ctr_id; } ;

/* Variables and functions */
 size_t DR_ACTION_TYP_CTR ; 
 size_t DR_ACTION_TYP_MODIFY_HDR ; 
 size_t DR_ACTION_TYP_POP_VLAN ; 
 size_t DR_ACTION_TYP_TAG ; 
 size_t DR_ACTION_TYP_TNL_L2_TO_L2 ; 
 size_t DR_ACTION_TYP_TNL_L3_TO_L2 ; 
 scalar_t__ MLX5DR_STE_TYPE_MODIFY_PKT ; 
 scalar_t__ MLX5DR_STE_TYPE_RX ; 
 int /*<<< orphan*/  dr_actions_init_next_ste (scalar_t__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx5dr_ste_get_entry_type (scalar_t__*) ; 
 int /*<<< orphan*/  mlx5dr_ste_rx_set_flow_tag (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_counter_id (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_entry_type (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_rewrite_actions (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_rx_decap (scalar_t__*) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_rx_decap_l3 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_rx_pop_vlan (scalar_t__*) ; 

__attribute__((used)) static void dr_actions_apply_rx(u8 *action_type_set,
				u8 *last_ste,
				struct dr_action_apply_attr *attr,
				u32 *added_stes)
{
	if (action_type_set[DR_ACTION_TYP_CTR])
		mlx5dr_ste_set_counter_id(last_ste, attr->ctr_id);

	if (action_type_set[DR_ACTION_TYP_TNL_L3_TO_L2]) {
		mlx5dr_ste_set_entry_type(last_ste, MLX5DR_STE_TYPE_MODIFY_PKT);
		mlx5dr_ste_set_rx_decap_l3(last_ste, attr->decap_with_vlan);
		mlx5dr_ste_set_rewrite_actions(last_ste,
					       attr->decap_actions,
					       attr->decap_index);
	}

	if (action_type_set[DR_ACTION_TYP_TNL_L2_TO_L2])
		mlx5dr_ste_set_rx_decap(last_ste);

	if (action_type_set[DR_ACTION_TYP_POP_VLAN]) {
		int i;

		for (i = 0; i < attr->vlans.count; i++) {
			if (i ||
			    action_type_set[DR_ACTION_TYP_TNL_L2_TO_L2] ||
			    action_type_set[DR_ACTION_TYP_TNL_L3_TO_L2])
				dr_actions_init_next_ste(&last_ste,
							 added_stes,
							 MLX5DR_STE_TYPE_RX,
							 attr->gvmi);

			mlx5dr_ste_set_rx_pop_vlan(last_ste);
		}
	}

	if (action_type_set[DR_ACTION_TYP_MODIFY_HDR]) {
		if (mlx5dr_ste_get_entry_type(last_ste) == MLX5DR_STE_TYPE_MODIFY_PKT)
			dr_actions_init_next_ste(&last_ste,
						 added_stes,
						 MLX5DR_STE_TYPE_MODIFY_PKT,
						 attr->gvmi);
		else
			mlx5dr_ste_set_entry_type(last_ste, MLX5DR_STE_TYPE_MODIFY_PKT);

		mlx5dr_ste_set_rewrite_actions(last_ste,
					       attr->modify_actions,
					       attr->modify_index);
	}

	if (action_type_set[DR_ACTION_TYP_TAG]) {
		if (mlx5dr_ste_get_entry_type(last_ste) == MLX5DR_STE_TYPE_MODIFY_PKT)
			dr_actions_init_next_ste(&last_ste,
						 added_stes,
						 MLX5DR_STE_TYPE_RX,
						 attr->gvmi);

		mlx5dr_ste_rx_set_flow_tag(last_ste, attr->flow_tag);
	}
}