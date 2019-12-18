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
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_params_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_devlink_params ; 
 int /*<<< orphan*/  priv_to_devlink (struct mlxsw_core*) ; 

__attribute__((used)) static void mlxsw_sp_params_unregister(struct mlxsw_core *mlxsw_core)
{
	devlink_params_unregister(priv_to_devlink(mlxsw_core),
				  mlxsw_sp_devlink_params,
				  ARRAY_SIZE(mlxsw_sp_devlink_params));
}