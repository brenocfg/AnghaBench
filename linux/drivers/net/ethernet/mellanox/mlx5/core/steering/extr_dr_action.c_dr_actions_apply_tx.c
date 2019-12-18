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
struct mlx5dr_domain {int /*<<< orphan*/  mdev; } ;
struct TYPE_2__ {int count; int /*<<< orphan*/ * headers; } ;
struct dr_action_apply_attr {int /*<<< orphan*/  ctr_id; int /*<<< orphan*/  reformat_size; int /*<<< orphan*/  reformat_id; int /*<<< orphan*/  gvmi; TYPE_1__ vlans; int /*<<< orphan*/  modify_index; int /*<<< orphan*/  modify_actions; } ;

/* Variables and functions */
 size_t DR_ACTION_TYP_CTR ; 
 size_t DR_ACTION_TYP_L2_TO_TNL_L2 ; 
 size_t DR_ACTION_TYP_L2_TO_TNL_L3 ; 
 size_t DR_ACTION_TYP_MODIFY_HDR ; 
 size_t DR_ACTION_TYP_PUSH_VLAN ; 
 int /*<<< orphan*/  MLX5DR_STE_TYPE_MODIFY_PKT ; 
 int /*<<< orphan*/  MLX5DR_STE_TYPE_TX ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_actions_init_next_ste (scalar_t__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_counter_id (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_entry_type (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_go_back_bit (scalar_t__*) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_rewrite_actions (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_tx_encap (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mlx5dr_ste_set_tx_push_vlan (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prio_tag_required ; 

__attribute__((used)) static void dr_actions_apply_tx(struct mlx5dr_domain *dmn,
				u8 *action_type_set,
				u8 *last_ste,
				struct dr_action_apply_attr *attr,
				u32 *added_stes)
{
	bool encap = action_type_set[DR_ACTION_TYP_L2_TO_TNL_L2] ||
		action_type_set[DR_ACTION_TYP_L2_TO_TNL_L3];

	/* We want to make sure the modify header comes before L2
	 * encapsulation. The reason for that is that we support
	 * modify headers for outer headers only
	 */
	if (action_type_set[DR_ACTION_TYP_MODIFY_HDR]) {
		mlx5dr_ste_set_entry_type(last_ste, MLX5DR_STE_TYPE_MODIFY_PKT);
		mlx5dr_ste_set_rewrite_actions(last_ste,
					       attr->modify_actions,
					       attr->modify_index);
	}

	if (action_type_set[DR_ACTION_TYP_PUSH_VLAN]) {
		int i;

		for (i = 0; i < attr->vlans.count; i++) {
			if (i || action_type_set[DR_ACTION_TYP_MODIFY_HDR])
				dr_actions_init_next_ste(&last_ste,
							 added_stes,
							 MLX5DR_STE_TYPE_TX,
							 attr->gvmi);

			mlx5dr_ste_set_tx_push_vlan(last_ste,
						    attr->vlans.headers[i],
						    encap);
		}
	}

	if (encap) {
		/* Modify header and encapsulation require a different STEs.
		 * Since modify header STE format doesn't support encapsulation
		 * tunneling_action.
		 */
		if (action_type_set[DR_ACTION_TYP_MODIFY_HDR] ||
		    action_type_set[DR_ACTION_TYP_PUSH_VLAN])
			dr_actions_init_next_ste(&last_ste,
						 added_stes,
						 MLX5DR_STE_TYPE_TX,
						 attr->gvmi);

		mlx5dr_ste_set_tx_encap(last_ste,
					attr->reformat_id,
					attr->reformat_size,
					action_type_set[DR_ACTION_TYP_L2_TO_TNL_L3]);
		/* Whenever prio_tag_required enabled, we can be sure that the
		 * previous table (ACL) already push vlan to our packet,
		 * And due to HW limitation we need to set this bit, otherwise
		 * push vlan + reformat will not work.
		 */
		if (MLX5_CAP_GEN(dmn->mdev, prio_tag_required))
			mlx5dr_ste_set_go_back_bit(last_ste);
	}

	if (action_type_set[DR_ACTION_TYP_CTR])
		mlx5dr_ste_set_counter_id(last_ste, attr->ctr_id);
}