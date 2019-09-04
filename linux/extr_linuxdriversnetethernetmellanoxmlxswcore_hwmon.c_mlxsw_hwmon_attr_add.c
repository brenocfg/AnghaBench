#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {TYPE_2__ attr; int /*<<< orphan*/  store; int /*<<< orphan*/  show; } ;
struct mlxsw_hwmon_attr {unsigned int type_index; TYPE_1__ dev_attr; int /*<<< orphan*/  name; struct mlxsw_hwmon* hwmon; } ;
struct mlxsw_hwmon {unsigned int attrs_count; TYPE_2__** attrs; struct mlxsw_hwmon_attr* hwmon_attrs; } ;
typedef  enum mlxsw_hwmon_attr_type { ____Placeholder_mlxsw_hwmon_attr_type } mlxsw_hwmon_attr_type ;

/* Variables and functions */
#define  MLXSW_HWMON_ATTR_TYPE_FAN_RPM 132 
#define  MLXSW_HWMON_ATTR_TYPE_PWM 131 
#define  MLXSW_HWMON_ATTR_TYPE_TEMP 130 
#define  MLXSW_HWMON_ATTR_TYPE_TEMP_MAX 129 
#define  MLXSW_HWMON_ATTR_TYPE_TEMP_RST 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_hwmon_fan_rpm_show ; 
 int /*<<< orphan*/  mlxsw_hwmon_pwm_show ; 
 int /*<<< orphan*/  mlxsw_hwmon_pwm_store ; 
 int /*<<< orphan*/  mlxsw_hwmon_temp_max_show ; 
 int /*<<< orphan*/  mlxsw_hwmon_temp_rst_store ; 
 int /*<<< orphan*/  mlxsw_hwmon_temp_show ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

__attribute__((used)) static void mlxsw_hwmon_attr_add(struct mlxsw_hwmon *mlxsw_hwmon,
				 enum mlxsw_hwmon_attr_type attr_type,
				 unsigned int type_index, unsigned int num) {
	struct mlxsw_hwmon_attr *mlxsw_hwmon_attr;
	unsigned int attr_index;

	attr_index = mlxsw_hwmon->attrs_count;
	mlxsw_hwmon_attr = &mlxsw_hwmon->hwmon_attrs[attr_index];

	switch (attr_type) {
	case MLXSW_HWMON_ATTR_TYPE_TEMP:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_temp_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snprintf(mlxsw_hwmon_attr->name, sizeof(mlxsw_hwmon_attr->name),
			 "temp%u_input", num + 1);
		break;
	case MLXSW_HWMON_ATTR_TYPE_TEMP_MAX:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_temp_max_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snprintf(mlxsw_hwmon_attr->name, sizeof(mlxsw_hwmon_attr->name),
			 "temp%u_highest", num + 1);
		break;
	case MLXSW_HWMON_ATTR_TYPE_TEMP_RST:
		mlxsw_hwmon_attr->dev_attr.store = mlxsw_hwmon_temp_rst_store;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0200;
		snprintf(mlxsw_hwmon_attr->name, sizeof(mlxsw_hwmon_attr->name),
			 "temp%u_reset_history", num + 1);
		break;
	case MLXSW_HWMON_ATTR_TYPE_FAN_RPM:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_fan_rpm_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snprintf(mlxsw_hwmon_attr->name, sizeof(mlxsw_hwmon_attr->name),
			 "fan%u_input", num + 1);
		break;
	case MLXSW_HWMON_ATTR_TYPE_PWM:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_pwm_show;
		mlxsw_hwmon_attr->dev_attr.store = mlxsw_hwmon_pwm_store;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0644;
		snprintf(mlxsw_hwmon_attr->name, sizeof(mlxsw_hwmon_attr->name),
			 "pwm%u", num + 1);
		break;
	default:
		WARN_ON(1);
	}

	mlxsw_hwmon_attr->type_index = type_index;
	mlxsw_hwmon_attr->hwmon = mlxsw_hwmon;
	mlxsw_hwmon_attr->dev_attr.attr.name = mlxsw_hwmon_attr->name;
	sysfs_attr_init(&mlxsw_hwmon_attr->dev_attr.attr);

	mlxsw_hwmon->attrs[attr_index] = &mlxsw_hwmon_attr->dev_attr.attr;
	mlxsw_hwmon->attrs_count++;
}