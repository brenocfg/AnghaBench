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
struct thermal_zone_device {struct mlxsw_thermal* devdata; } ;
struct mlxsw_thermal {int /*<<< orphan*/  trips; int /*<<< orphan*/  core; TYPE_1__* bus_info; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MTMP_LEN ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mtmp_pack (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mtmp_unpack (char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_thermal_tz_score_update (struct mlxsw_thermal*,struct thermal_zone_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtmp ; 

__attribute__((used)) static int mlxsw_thermal_get_temp(struct thermal_zone_device *tzdev,
				  int *p_temp)
{
	struct mlxsw_thermal *thermal = tzdev->devdata;
	struct device *dev = thermal->bus_info->dev;
	char mtmp_pl[MLXSW_REG_MTMP_LEN];
	int temp;
	int err;

	mlxsw_reg_mtmp_pack(mtmp_pl, 0, false, false);

	err = mlxsw_reg_query(thermal->core, MLXSW_REG(mtmp), mtmp_pl);
	if (err) {
		dev_err(dev, "Failed to query temp sensor\n");
		return err;
	}
	mlxsw_reg_mtmp_unpack(mtmp_pl, &temp, NULL, NULL);
	if (temp > 0)
		mlxsw_thermal_tz_score_update(thermal, tzdev, thermal->trips,
					      temp);

	*p_temp = temp;
	return 0;
}