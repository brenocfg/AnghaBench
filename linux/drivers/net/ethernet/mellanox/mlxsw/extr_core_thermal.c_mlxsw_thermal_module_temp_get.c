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
struct thermal_zone_device {struct mlxsw_thermal_module* devdata; } ;
struct mlxsw_thermal_module {int /*<<< orphan*/  trips; scalar_t__ module; struct mlxsw_thermal* parent; } ;
struct mlxsw_thermal {int /*<<< orphan*/  core; TYPE_1__* bus_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MTMP_LEN ; 
 scalar_t__ MLXSW_REG_MTMP_MODULE_INDEX_MIN ; 
 int /*<<< orphan*/  mlxsw_reg_mtmp_pack (char*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtmp_unpack (char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_thermal_module_trips_update (struct device*,int /*<<< orphan*/ ,struct mlxsw_thermal_module*) ; 
 int /*<<< orphan*/  mlxsw_thermal_tz_score_update (struct mlxsw_thermal*,struct thermal_zone_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtmp ; 

__attribute__((used)) static int mlxsw_thermal_module_temp_get(struct thermal_zone_device *tzdev,
					 int *p_temp)
{
	struct mlxsw_thermal_module *tz = tzdev->devdata;
	struct mlxsw_thermal *thermal = tz->parent;
	struct device *dev = thermal->bus_info->dev;
	char mtmp_pl[MLXSW_REG_MTMP_LEN];
	int temp;
	int err;

	/* Read module temperature. */
	mlxsw_reg_mtmp_pack(mtmp_pl, MLXSW_REG_MTMP_MODULE_INDEX_MIN +
			    tz->module, false, false);
	err = mlxsw_reg_query(thermal->core, MLXSW_REG(mtmp), mtmp_pl);
	if (err) {
		/* Do not return error - in case of broken module's sensor
		 * it will cause error message flooding.
		 */
		temp = 0;
		*p_temp = (int) temp;
		return 0;
	}
	mlxsw_reg_mtmp_unpack(mtmp_pl, &temp, NULL, NULL);
	*p_temp = temp;

	if (!temp)
		return 0;

	/* Update trip points. */
	err = mlxsw_thermal_module_trips_update(dev, thermal->core, tz);
	if (!err && temp > 0)
		mlxsw_thermal_tz_score_update(thermal, tzdev, tz->trips, temp);

	return 0;
}