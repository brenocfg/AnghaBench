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
struct mlxsw_thermal_module {int /*<<< orphan*/  parent; } ;
struct mlxsw_thermal {struct mlxsw_thermal_module* tz_module_arr; } ;
struct mlxsw_core {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlxsw_thermal_module* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_thermal_module*) ; 
 unsigned int mlxsw_core_max_ports (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_core_res_query_enabled (struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_thermal_module_fini (struct mlxsw_thermal_module*) ; 
 int mlxsw_thermal_module_init (struct device*,struct mlxsw_core*,struct mlxsw_thermal*,int) ; 
 int mlxsw_thermal_module_tz_init (struct mlxsw_thermal_module*) ; 

__attribute__((used)) static int
mlxsw_thermal_modules_init(struct device *dev, struct mlxsw_core *core,
			   struct mlxsw_thermal *thermal)
{
	unsigned int module_count = mlxsw_core_max_ports(core);
	struct mlxsw_thermal_module *module_tz;
	int i, err;

	if (!mlxsw_core_res_query_enabled(core))
		return 0;

	thermal->tz_module_arr = kcalloc(module_count,
					 sizeof(*thermal->tz_module_arr),
					 GFP_KERNEL);
	if (!thermal->tz_module_arr)
		return -ENOMEM;

	for (i = 1; i < module_count; i++) {
		err = mlxsw_thermal_module_init(dev, core, thermal, i);
		if (err)
			goto err_unreg_tz_module_arr;
	}

	for (i = 0; i < module_count - 1; i++) {
		module_tz = &thermal->tz_module_arr[i];
		if (!module_tz->parent)
			continue;
		err = mlxsw_thermal_module_tz_init(module_tz);
		if (err)
			goto err_unreg_tz_module_arr;
	}

	return 0;

err_unreg_tz_module_arr:
	for (i = module_count - 1; i >= 0; i--)
		mlxsw_thermal_module_fini(&thermal->tz_module_arr[i]);
	kfree(thermal->tz_module_arr);
	return err;
}