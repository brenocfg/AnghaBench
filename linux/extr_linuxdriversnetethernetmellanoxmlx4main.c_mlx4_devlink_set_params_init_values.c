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
union devlink_param_value {int vbool; unsigned long vu32; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PARAM_GENERIC_ID_INT_ERR_RESET ; 
 int /*<<< orphan*/  DEVLINK_PARAM_GENERIC_ID_MAX_MACS ; 
 int /*<<< orphan*/  DEVLINK_PARAM_GENERIC_ID_REGION_SNAPSHOT ; 
 int /*<<< orphan*/  MLX4_DEVLINK_PARAM_ID_ENABLE_4K_UAR ; 
 int /*<<< orphan*/  MLX4_DEVLINK_PARAM_ID_ENABLE_64B_CQE_EQE ; 
 int /*<<< orphan*/  devlink_param_driverinit_value_set (struct devlink*,int /*<<< orphan*/ ,union devlink_param_value) ; 
 int enable_4k_uar ; 
 int enable_64b_cqe_eqe ; 
 unsigned long log_num_mac ; 
 int /*<<< orphan*/  mlx4_internal_err_reset ; 

__attribute__((used)) static void mlx4_devlink_set_params_init_values(struct devlink *devlink)
{
	union devlink_param_value value;

	value.vbool = !!mlx4_internal_err_reset;
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_INT_ERR_RESET,
					   value);

	value.vu32 = 1UL << log_num_mac;
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_MAX_MACS,
					   value);

	value.vbool = enable_64b_cqe_eqe;
	devlink_param_driverinit_value_set(devlink,
					   MLX4_DEVLINK_PARAM_ID_ENABLE_64B_CQE_EQE,
					   value);

	value.vbool = enable_4k_uar;
	devlink_param_driverinit_value_set(devlink,
					   MLX4_DEVLINK_PARAM_ID_ENABLE_4K_UAR,
					   value);

	value.vbool = false;
	devlink_param_driverinit_value_set(devlink,
					   DEVLINK_PARAM_GENERIC_ID_REGION_SNAPSHOT,
					   value);
}