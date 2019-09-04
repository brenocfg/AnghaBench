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
typedef  int /*<<< orphan*/  u64 ;
struct mlxsw_driver {int (* kvd_sizes_get ) (struct mlxsw_core*,struct mlxsw_config_profile const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct mlxsw_core {struct mlxsw_driver* driver; } ;
struct mlxsw_config_profile {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct mlxsw_core*,struct mlxsw_config_profile const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlxsw_core_kvd_sizes_get(struct mlxsw_core *mlxsw_core,
			     const struct mlxsw_config_profile *profile,
			     u64 *p_single_size, u64 *p_double_size,
			     u64 *p_linear_size)
{
	struct mlxsw_driver *driver = mlxsw_core->driver;

	if (!driver->kvd_sizes_get)
		return -EINVAL;

	return driver->kvd_sizes_get(mlxsw_core, profile,
				     p_single_size, p_double_size,
				     p_linear_size);
}