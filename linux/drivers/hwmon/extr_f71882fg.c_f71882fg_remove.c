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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct f71882fg_data {size_t type; int temp_config; scalar_t__ hwmon_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int F71882FG_MAX_INS ; 
 int /*<<< orphan*/  F71882FG_REG_START ; 
 int /*<<< orphan*/  dev_attr_name ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  f71808a 134 
 int /*<<< orphan*/ * f71808a_fan3_attr ; 
#define  f71808e 133 
#define  f71858fg 132 
 int /*<<< orphan*/ * f71858fg_temp_attr ; 
#define  f71862fg 131 
 int /*<<< orphan*/ ** f71862fg_auto_pwm_attr ; 
#define  f71869 130 
 int /*<<< orphan*/ ** f71869_auto_pwm_attr ; 
 scalar_t__* f71882fg_fan_has_beep ; 
 scalar_t__** f71882fg_has_in ; 
 scalar_t__* f71882fg_has_in1_alarm ; 
 int* f71882fg_nr_fans ; 
 int* f71882fg_nr_temps ; 
 int f71882fg_read8 (struct f71882fg_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f71882fg_remove_sysfs_files (struct platform_device*,int /*<<< orphan*/ *,int) ; 
 scalar_t__* f71882fg_temp_has_beep ; 
#define  f8000 129 
 int /*<<< orphan*/ ** f8000_auto_pwm_attr ; 
 int /*<<< orphan*/ * f8000_fan_attr ; 
 int /*<<< orphan*/ * f8000_temp_attr ; 
 int /*<<< orphan*/ ** f81866_temp_beep_attr ; 
#define  f81866a 128 
 int /*<<< orphan*/ ** fxxxx_auto_pwm_attr ; 
 int /*<<< orphan*/ ** fxxxx_fan_attr ; 
 int /*<<< orphan*/ * fxxxx_fan_beep_attr ; 
 int /*<<< orphan*/ * fxxxx_in1_alarm_attr ; 
 TYPE_1__* fxxxx_in_attr ; 
 int /*<<< orphan*/ ** fxxxx_temp_attr ; 
 int /*<<< orphan*/ ** fxxxx_temp_beep_attr ; 
 int /*<<< orphan*/  hwmon_device_unregister (scalar_t__) ; 
 struct f71882fg_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int f71882fg_remove(struct platform_device *pdev)
{
	struct f71882fg_data *data = platform_get_drvdata(pdev);
	int nr_fans = f71882fg_nr_fans[data->type];
	int nr_temps = f71882fg_nr_temps[data->type];
	int i;
	u8 start_reg = f71882fg_read8(data, F71882FG_REG_START);

	if (data->hwmon_dev)
		hwmon_device_unregister(data->hwmon_dev);

	device_remove_file(&pdev->dev, &dev_attr_name);

	if (start_reg & 0x01) {
		switch (data->type) {
		case f71858fg:
			if (data->temp_config & 0x10)
				f71882fg_remove_sysfs_files(pdev,
					f8000_temp_attr,
					ARRAY_SIZE(f8000_temp_attr));
			else
				f71882fg_remove_sysfs_files(pdev,
					f71858fg_temp_attr,
					ARRAY_SIZE(f71858fg_temp_attr));
			break;
		case f8000:
			f71882fg_remove_sysfs_files(pdev,
					f8000_temp_attr,
					ARRAY_SIZE(f8000_temp_attr));
			break;
		case f81866a:
			f71882fg_remove_sysfs_files(pdev,
					f71858fg_temp_attr,
					ARRAY_SIZE(f71858fg_temp_attr));
			break;
		default:
			f71882fg_remove_sysfs_files(pdev,
				&fxxxx_temp_attr[0][0],
				ARRAY_SIZE(fxxxx_temp_attr[0]) * nr_temps);
		}
		if (f71882fg_temp_has_beep[data->type]) {
			if (data->type == f81866a)
				f71882fg_remove_sysfs_files(pdev,
					&f81866_temp_beep_attr[0][0],
					ARRAY_SIZE(f81866_temp_beep_attr[0])
						* nr_temps);
			else
				f71882fg_remove_sysfs_files(pdev,
					&fxxxx_temp_beep_attr[0][0],
					ARRAY_SIZE(fxxxx_temp_beep_attr[0])
						* nr_temps);
		}

		for (i = 0; i < F71882FG_MAX_INS; i++) {
			if (f71882fg_has_in[data->type][i]) {
				device_remove_file(&pdev->dev,
						&fxxxx_in_attr[i].dev_attr);
			}
		}
		if (f71882fg_has_in1_alarm[data->type]) {
			f71882fg_remove_sysfs_files(pdev,
					fxxxx_in1_alarm_attr,
					ARRAY_SIZE(fxxxx_in1_alarm_attr));
		}
	}

	if (start_reg & 0x02) {
		f71882fg_remove_sysfs_files(pdev, &fxxxx_fan_attr[0][0],
				ARRAY_SIZE(fxxxx_fan_attr[0]) * nr_fans);

		if (f71882fg_fan_has_beep[data->type]) {
			f71882fg_remove_sysfs_files(pdev,
					fxxxx_fan_beep_attr, nr_fans);
		}

		switch (data->type) {
		case f71808a:
			f71882fg_remove_sysfs_files(pdev,
				&fxxxx_auto_pwm_attr[0][0],
				ARRAY_SIZE(fxxxx_auto_pwm_attr[0]) * nr_fans);
			f71882fg_remove_sysfs_files(pdev,
					f71808a_fan3_attr,
					ARRAY_SIZE(f71808a_fan3_attr));
			break;
		case f71862fg:
			f71882fg_remove_sysfs_files(pdev,
				&f71862fg_auto_pwm_attr[0][0],
				ARRAY_SIZE(f71862fg_auto_pwm_attr[0]) *
					nr_fans);
			break;
		case f71808e:
		case f71869:
			f71882fg_remove_sysfs_files(pdev,
				&f71869_auto_pwm_attr[0][0],
				ARRAY_SIZE(f71869_auto_pwm_attr[0]) * nr_fans);
			break;
		case f8000:
			f71882fg_remove_sysfs_files(pdev,
					f8000_fan_attr,
					ARRAY_SIZE(f8000_fan_attr));
			f71882fg_remove_sysfs_files(pdev,
				&f8000_auto_pwm_attr[0][0],
				ARRAY_SIZE(f8000_auto_pwm_attr[0]) * nr_fans);
			break;
		default:
			f71882fg_remove_sysfs_files(pdev,
				&fxxxx_auto_pwm_attr[0][0],
				ARRAY_SIZE(fxxxx_auto_pwm_attr[0]) * nr_fans);
		}
	}
	return 0;
}