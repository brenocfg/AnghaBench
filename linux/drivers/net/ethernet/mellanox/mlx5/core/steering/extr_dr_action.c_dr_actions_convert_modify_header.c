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
typedef  scalar_t__ u16 ;
struct mlx5dr_domain {int dummy; } ;
struct dr_action_modify_field_conv {int l3_type; int l4_type; scalar_t__ hw_field; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLX5DR_ACTION_MDFY_HW_FLD_RESERVED ; 
 int MLX5DR_ACTION_MDFY_HW_HDR_L3_NONE ; 
 int MLX5DR_ACTION_MDFY_HW_HDR_L4_NONE ; 
 int dr_action_modify_check_field_limitation (struct mlx5dr_domain*,int /*<<< orphan*/ *) ; 
 int dr_action_modify_check_is_ttl_modify (int /*<<< orphan*/ *) ; 
 int dr_action_modify_sw_to_hw (struct mlx5dr_domain*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct dr_action_modify_field_conv const**) ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*) ; 

__attribute__((used)) static int dr_actions_convert_modify_header(struct mlx5dr_domain *dmn,
					    u32 max_hw_actions,
					    u32 num_sw_actions,
					    __be64 sw_actions[],
					    __be64 hw_actions[],
					    u32 *num_hw_actions,
					    bool *modify_ttl)
{
	const struct dr_action_modify_field_conv *hw_action_info;
	u16 hw_field = MLX5DR_ACTION_MDFY_HW_FLD_RESERVED;
	u32 l3_type = MLX5DR_ACTION_MDFY_HW_HDR_L3_NONE;
	u32 l4_type = MLX5DR_ACTION_MDFY_HW_HDR_L4_NONE;
	int ret, i, hw_idx = 0;
	__be64 *sw_action;
	__be64 hw_action;

	*modify_ttl = false;

	for (i = 0; i < num_sw_actions; i++) {
		sw_action = &sw_actions[i];

		ret = dr_action_modify_check_field_limitation(dmn, sw_action);
		if (ret)
			return ret;

		if (!(*modify_ttl))
			*modify_ttl = dr_action_modify_check_is_ttl_modify(sw_action);

		/* Convert SW action to HW action */
		ret = dr_action_modify_sw_to_hw(dmn,
						sw_action,
						&hw_action,
						&hw_action_info);
		if (ret)
			return ret;

		/* Due to a HW limitation we cannot modify 2 different L3 types */
		if (l3_type && hw_action_info->l3_type &&
		    hw_action_info->l3_type != l3_type) {
			mlx5dr_dbg(dmn, "Action list can't support two different L3 types\n");
			return -EINVAL;
		}
		if (hw_action_info->l3_type)
			l3_type = hw_action_info->l3_type;

		/* Due to a HW limitation we cannot modify two different L4 types */
		if (l4_type && hw_action_info->l4_type &&
		    hw_action_info->l4_type != l4_type) {
			mlx5dr_dbg(dmn, "Action list can't support two different L4 types\n");
			return -EINVAL;
		}
		if (hw_action_info->l4_type)
			l4_type = hw_action_info->l4_type;

		/* HW reads and executes two actions at once this means we
		 * need to create a gap if two actions access the same field
		 */
		if ((hw_idx % 2) && hw_field == hw_action_info->hw_field) {
			/* Check if after gap insertion the total number of HW
			 * modify actions doesn't exceeds the limit
			 */
			hw_idx++;
			if ((num_sw_actions + hw_idx - i) >= max_hw_actions) {
				mlx5dr_dbg(dmn, "Modify header action number exceeds HW limit\n");
				return -EINVAL;
			}
		}
		hw_field = hw_action_info->hw_field;

		hw_actions[hw_idx] = hw_action;
		hw_idx++;
	}

	*num_hw_actions = hw_idx;

	return 0;
}