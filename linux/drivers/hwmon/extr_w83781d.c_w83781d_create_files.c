#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
struct TYPE_8__ {TYPE_1__ dev_attr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
 int as99127f ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 TYPE_5__ sensor_dev_attr_temp1_type ; 
 TYPE_4__ sensor_dev_attr_temp2_type ; 
 TYPE_3__ sensor_dev_attr_temp3_alarm ; 
 TYPE_2__ sensor_dev_attr_temp3_type ; 
 int sysfs_chmod_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int w83781d ; 
 int /*<<< orphan*/  w83781d_group ; 
 int /*<<< orphan*/  w83781d_group_in1 ; 
 int /*<<< orphan*/  w83781d_group_in78 ; 
 int /*<<< orphan*/  w83781d_group_pwm12 ; 
 int /*<<< orphan*/  w83781d_group_pwm34 ; 
 int /*<<< orphan*/  w83781d_group_temp3 ; 
 int w83782d ; 
 int w83783s ; 

__attribute__((used)) static int
w83781d_create_files(struct device *dev, int kind, int is_isa)
{
	int err;

	err = sysfs_create_group(&dev->kobj, &w83781d_group);
	if (err)
		return err;

	if (kind != w83783s) {
		err = sysfs_create_group(&dev->kobj, &w83781d_group_in1);
		if (err)
			return err;
	}
	if (kind != as99127f && kind != w83781d && kind != w83783s) {
		err = sysfs_create_group(&dev->kobj, &w83781d_group_in78);
		if (err)
			return err;
	}
	if (kind != w83783s) {
		err = sysfs_create_group(&dev->kobj, &w83781d_group_temp3);
		if (err)
			return err;

		if (kind != w83781d) {
			err = sysfs_chmod_file(&dev->kobj,
				&sensor_dev_attr_temp3_alarm.dev_attr.attr,
				S_IRUGO | S_IWUSR);
			if (err)
				return err;
		}
	}

	if (kind != w83781d && kind != as99127f) {
		err = sysfs_create_group(&dev->kobj, &w83781d_group_pwm12);
		if (err)
			return err;
	}
	if (kind == w83782d && !is_isa) {
		err = sysfs_create_group(&dev->kobj, &w83781d_group_pwm34);
		if (err)
			return err;
	}

	if (kind != as99127f && kind != w83781d) {
		err = device_create_file(dev,
					 &sensor_dev_attr_temp1_type.dev_attr);
		if (err)
			return err;
		err = device_create_file(dev,
					 &sensor_dev_attr_temp2_type.dev_attr);
		if (err)
			return err;
		if (kind != w83783s) {
			err = device_create_file(dev,
					&sensor_dev_attr_temp3_type.dev_attr);
			if (err)
				return err;
		}
	}

	return 0;
}