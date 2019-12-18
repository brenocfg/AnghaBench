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
struct mlxsw_thermal_module {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * tzdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_thermal_module_tz_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_thermal_module_fini(struct mlxsw_thermal_module *module_tz)
{
	if (module_tz && module_tz->tzdev) {
		mlxsw_thermal_module_tz_fini(module_tz->tzdev);
		module_tz->tzdev = NULL;
		module_tz->parent = NULL;
	}
}