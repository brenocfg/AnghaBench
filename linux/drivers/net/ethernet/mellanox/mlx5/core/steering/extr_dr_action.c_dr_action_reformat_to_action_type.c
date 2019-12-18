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
typedef  enum mlx5dr_action_type { ____Placeholder_mlx5dr_action_type } mlx5dr_action_type ;
typedef  enum mlx5dr_action_reformat_type { ____Placeholder_mlx5dr_action_reformat_type } mlx5dr_action_reformat_type ;

/* Variables and functions */
#define  DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L2 131 
#define  DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L3 130 
#define  DR_ACTION_REFORMAT_TYP_TNL_L2_TO_L2 129 
#define  DR_ACTION_REFORMAT_TYP_TNL_L3_TO_L2 128 
 int DR_ACTION_TYP_L2_TO_TNL_L2 ; 
 int DR_ACTION_TYP_L2_TO_TNL_L3 ; 
 int DR_ACTION_TYP_TNL_L2_TO_L2 ; 
 int DR_ACTION_TYP_TNL_L3_TO_L2 ; 
 int EINVAL ; 

__attribute__((used)) static int
dr_action_reformat_to_action_type(enum mlx5dr_action_reformat_type reformat_type,
				  enum mlx5dr_action_type *action_type)
{
	switch (reformat_type) {
	case DR_ACTION_REFORMAT_TYP_TNL_L2_TO_L2:
		*action_type = DR_ACTION_TYP_TNL_L2_TO_L2;
		break;
	case DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L2:
		*action_type = DR_ACTION_TYP_L2_TO_TNL_L2;
		break;
	case DR_ACTION_REFORMAT_TYP_TNL_L3_TO_L2:
		*action_type = DR_ACTION_TYP_TNL_L3_TO_L2;
		break;
	case DR_ACTION_REFORMAT_TYP_L2_TO_TNL_L3:
		*action_type = DR_ACTION_TYP_L2_TO_TNL_L3;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}