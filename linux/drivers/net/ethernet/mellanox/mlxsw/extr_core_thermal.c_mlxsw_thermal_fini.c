#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_thermal {TYPE_1__* bus_info; int /*<<< orphan*/ ** cdevs; int /*<<< orphan*/ * tzdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MLXSW_MFCR_PWMS_MAX ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct mlxsw_thermal*) ; 
 int /*<<< orphan*/  mlxsw_thermal_gearboxes_fini (struct mlxsw_thermal*) ; 
 int /*<<< orphan*/  mlxsw_thermal_modules_fini (struct mlxsw_thermal*) ; 
 int /*<<< orphan*/  thermal_cooling_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_device_unregister (int /*<<< orphan*/ *) ; 

void mlxsw_thermal_fini(struct mlxsw_thermal *thermal)
{
	int i;

	mlxsw_thermal_gearboxes_fini(thermal);
	mlxsw_thermal_modules_fini(thermal);
	if (thermal->tzdev) {
		thermal_zone_device_unregister(thermal->tzdev);
		thermal->tzdev = NULL;
	}

	for (i = 0; i < MLXSW_MFCR_PWMS_MAX; i++) {
		if (thermal->cdevs[i]) {
			thermal_cooling_device_unregister(thermal->cdevs[i]);
			thermal->cdevs[i] = NULL;
		}
	}

	devm_kfree(thermal->bus_info->dev, thermal);
}