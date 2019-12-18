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
struct mlxsw_thermal {int /*<<< orphan*/ * tz_module_arr; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 unsigned int mlxsw_core_max_ports (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_res_query_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_thermal_module_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_thermal_modules_fini(struct mlxsw_thermal *thermal)
{
	unsigned int module_count = mlxsw_core_max_ports(thermal->core);
	int i;

	if (!mlxsw_core_res_query_enabled(thermal->core))
		return;

	for (i = module_count - 1; i >= 0; i--)
		mlxsw_thermal_module_fini(&thermal->tz_module_arr[i]);
	kfree(thermal->tz_module_arr);
}