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
typedef  int u8 ;
struct mlxsw_hwmon {int module_sensor_count; TYPE_1__* bus_info; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_HWMON_ATTR_TYPE_TEMP ; 
 int /*<<< orphan*/  MLXSW_HWMON_ATTR_TYPE_TEMP_GBOX_LABEL ; 
 int /*<<< orphan*/  MLXSW_HWMON_ATTR_TYPE_TEMP_MAX ; 
 int /*<<< orphan*/  MLXSW_HWMON_ATTR_TYPE_TEMP_RST ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MGPIR_LEN ; 
 int MLXSW_REG_MTMP_GBOX_INDEX_MIN ; 
 int MLXSW_REG_MTMP_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mgpir ; 
 int /*<<< orphan*/  mlxsw_hwmon_attr_add (struct mlxsw_hwmon*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_mgpir_pack (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mgpir_unpack (char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_reg_mtmp_pack (char*,int,int,int) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtmp ; 

__attribute__((used)) static int mlxsw_hwmon_gearbox_init(struct mlxsw_hwmon *mlxsw_hwmon)
{
	int index, max_index, sensor_index;
	char mgpir_pl[MLXSW_REG_MGPIR_LEN];
	char mtmp_pl[MLXSW_REG_MTMP_LEN];
	u8 gbox_num;
	int err;

	mlxsw_reg_mgpir_pack(mgpir_pl);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mgpir), mgpir_pl);
	if (err)
		return err;

	mlxsw_reg_mgpir_unpack(mgpir_pl, &gbox_num, NULL, NULL);
	if (!gbox_num)
		return 0;

	index = mlxsw_hwmon->module_sensor_count;
	max_index = mlxsw_hwmon->module_sensor_count + gbox_num;
	while (index < max_index) {
		sensor_index = index % mlxsw_hwmon->module_sensor_count +
			       MLXSW_REG_MTMP_GBOX_INDEX_MIN;
		mlxsw_reg_mtmp_pack(mtmp_pl, sensor_index, true, true);
		err = mlxsw_reg_write(mlxsw_hwmon->core,
				      MLXSW_REG(mtmp), mtmp_pl);
		if (err) {
			dev_err(mlxsw_hwmon->bus_info->dev, "Failed to setup temp sensor number %d\n",
				sensor_index);
			return err;
		}
		mlxsw_hwmon_attr_add(mlxsw_hwmon, MLXSW_HWMON_ATTR_TYPE_TEMP,
				     index, index);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_MAX, index,
				     index);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_RST, index,
				     index);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_GBOX_LABEL,
				     index, index);
		index++;
	}

	return 0;
}