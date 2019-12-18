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
struct thermal_cooling_device {int /*<<< orphan*/  type; } ;
struct mlxsw_thermal {struct thermal_cooling_device** cdevs; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int MLXSW_MFCR_PWMS_MAX ; 
 int /*<<< orphan*/ * mlxsw_thermal_external_allowed_cdev ; 
 scalar_t__ strnstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlxsw_get_cooling_device_idx(struct mlxsw_thermal *thermal,
					struct thermal_cooling_device *cdev)
{
	int i;

	for (i = 0; i < MLXSW_MFCR_PWMS_MAX; i++)
		if (thermal->cdevs[i] == cdev)
			return i;

	/* Allow mlxsw thermal zone binding to an external cooling device */
	for (i = 0; i < ARRAY_SIZE(mlxsw_thermal_external_allowed_cdev); i++) {
		if (strnstr(cdev->type, mlxsw_thermal_external_allowed_cdev[i],
			    sizeof(cdev->type)))
			return 0;
	}

	return -ENODEV;
}