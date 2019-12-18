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
struct mlxsw_thermal {int tz_gearbox_num; int /*<<< orphan*/ * tz_gearbox_arr; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_core_res_query_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_thermal_gearbox_tz_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_thermal_gearboxes_fini(struct mlxsw_thermal *thermal)
{
	int i;

	if (!mlxsw_core_res_query_enabled(thermal->core))
		return;

	for (i = thermal->tz_gearbox_num - 1; i >= 0; i--)
		mlxsw_thermal_gearbox_tz_fini(&thermal->tz_gearbox_arr[i]);
	kfree(thermal->tz_gearbox_arr);
}