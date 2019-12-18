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
struct mlx5dr_domain {scalar_t__ type; } ;
typedef  enum mlx5dr_action_type { ____Placeholder_mlx5dr_action_type } mlx5dr_action_type ;

/* Variables and functions */
 int DR_ACTION_TYP_L2_TO_TNL_L2 ; 
 int DR_ACTION_TYP_L2_TO_TNL_L3 ; 
 int DR_ACTION_TYP_TNL_L2_TO_L2 ; 
 int DR_ACTION_TYP_TNL_L3_TO_L2 ; 
 int EINVAL ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_FDB ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_NIC_RX ; 
 scalar_t__ MLX5DR_DOMAIN_TYPE_NIC_TX ; 
 int /*<<< orphan*/  mlx5dr_dbg (struct mlx5dr_domain*,char*) ; 

__attribute__((used)) static int
dr_action_verify_reformat_params(enum mlx5dr_action_type reformat_type,
				 struct mlx5dr_domain *dmn,
				 size_t data_sz,
				 void *data)
{
	if ((!data && data_sz) || (data && !data_sz) || reformat_type >
		DR_ACTION_TYP_L2_TO_TNL_L3) {
		mlx5dr_dbg(dmn, "Invalid reformat parameter!\n");
		goto out_err;
	}

	if (dmn->type == MLX5DR_DOMAIN_TYPE_FDB)
		return 0;

	if (dmn->type == MLX5DR_DOMAIN_TYPE_NIC_RX) {
		if (reformat_type != DR_ACTION_TYP_TNL_L2_TO_L2 &&
		    reformat_type != DR_ACTION_TYP_TNL_L3_TO_L2) {
			mlx5dr_dbg(dmn, "Action reformat type not support on RX domain\n");
			goto out_err;
		}
	} else if (dmn->type == MLX5DR_DOMAIN_TYPE_NIC_TX) {
		if (reformat_type != DR_ACTION_TYP_L2_TO_TNL_L2 &&
		    reformat_type != DR_ACTION_TYP_L2_TO_TNL_L3) {
			mlx5dr_dbg(dmn, "Action reformat type not support on TX domain\n");
			goto out_err;
		}
	}

	return 0;

out_err:
	return -EINVAL;
}