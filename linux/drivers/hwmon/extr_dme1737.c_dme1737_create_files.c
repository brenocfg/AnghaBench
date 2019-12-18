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
struct dme1737_data {int has_features; int config; int /*<<< orphan*/ * pwm_config; int /*<<< orphan*/  client; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_2__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int HAS_FAN (int) ; 
 int HAS_IN7 ; 
 int HAS_PWM (int) ; 
 int HAS_PWM_MIN ; 
 int HAS_TEMP_OFFSET ; 
 int HAS_VID ; 
 int HAS_ZONE3 ; 
 int HAS_ZONE_HYST ; 
 int PWM_EN_FROM_REG (int /*<<< orphan*/ ) ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 TYPE_1__ dev_attr_name ; 
 struct dme1737_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/ ** dme1737_auto_pwm_min_attr ; 
 int /*<<< orphan*/  dme1737_chmod_file (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dme1737_chmod_group (struct device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dme1737_fan_group ; 
 int /*<<< orphan*/  dme1737_group ; 
 int /*<<< orphan*/  dme1737_in7_group ; 
 int /*<<< orphan*/ ** dme1737_pwm_chmod_attr ; 
 int /*<<< orphan*/ * dme1737_pwm_chmod_group ; 
 int /*<<< orphan*/ * dme1737_pwm_group ; 
 int /*<<< orphan*/  dme1737_remove_files (struct device*) ; 
 int /*<<< orphan*/  dme1737_temp_offset_group ; 
 int /*<<< orphan*/  dme1737_vid_group ; 
 int /*<<< orphan*/  dme1737_zone3_chmod_group ; 
 int /*<<< orphan*/  dme1737_zone3_group ; 
 int /*<<< orphan*/  dme1737_zone_chmod_group ; 
 int /*<<< orphan*/  dme1737_zone_hyst_group ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dme1737_create_files(struct device *dev)
{
	struct dme1737_data *data = dev_get_drvdata(dev);
	int err, ix;

	/* Create a name attribute for ISA devices */
	if (!data->client) {
		err = sysfs_create_file(&dev->kobj, &dev_attr_name.attr);
		if (err)
			goto exit;
	}

	/* Create standard sysfs attributes */
	err = sysfs_create_group(&dev->kobj, &dme1737_group);
	if (err)
		goto exit_remove;

	/* Create chip-dependent sysfs attributes */
	if (data->has_features & HAS_TEMP_OFFSET) {
		err = sysfs_create_group(&dev->kobj,
					 &dme1737_temp_offset_group);
		if (err)
			goto exit_remove;
	}
	if (data->has_features & HAS_VID) {
		err = sysfs_create_group(&dev->kobj, &dme1737_vid_group);
		if (err)
			goto exit_remove;
	}
	if (data->has_features & HAS_ZONE3) {
		err = sysfs_create_group(&dev->kobj, &dme1737_zone3_group);
		if (err)
			goto exit_remove;
	}
	if (data->has_features & HAS_ZONE_HYST) {
		err = sysfs_create_group(&dev->kobj, &dme1737_zone_hyst_group);
		if (err)
			goto exit_remove;
	}
	if (data->has_features & HAS_IN7) {
		err = sysfs_create_group(&dev->kobj, &dme1737_in7_group);
		if (err)
			goto exit_remove;
	}

	/* Create fan sysfs attributes */
	for (ix = 0; ix < ARRAY_SIZE(dme1737_fan_group); ix++) {
		if (data->has_features & HAS_FAN(ix)) {
			err = sysfs_create_group(&dev->kobj,
						 &dme1737_fan_group[ix]);
			if (err)
				goto exit_remove;
		}
	}

	/* Create PWM sysfs attributes */
	for (ix = 0; ix < ARRAY_SIZE(dme1737_pwm_group); ix++) {
		if (data->has_features & HAS_PWM(ix)) {
			err = sysfs_create_group(&dev->kobj,
						 &dme1737_pwm_group[ix]);
			if (err)
				goto exit_remove;
			if ((data->has_features & HAS_PWM_MIN) && (ix < 3)) {
				err = sysfs_create_file(&dev->kobj,
						dme1737_auto_pwm_min_attr[ix]);
				if (err)
					goto exit_remove;
			}
		}
	}

	/*
	 * Inform if the device is locked. Otherwise change the permissions of
	 * selected attributes from read-only to read-writeable.
	 */
	if (data->config & 0x02) {
		dev_info(dev,
			 "Device is locked. Some attributes will be read-only.\n");
	} else {
		/* Change permissions of zone sysfs attributes */
		dme1737_chmod_group(dev, &dme1737_zone_chmod_group,
				    S_IRUGO | S_IWUSR);

		/* Change permissions of chip-dependent sysfs attributes */
		if (data->has_features & HAS_TEMP_OFFSET) {
			dme1737_chmod_group(dev, &dme1737_temp_offset_group,
					    S_IRUGO | S_IWUSR);
		}
		if (data->has_features & HAS_ZONE3) {
			dme1737_chmod_group(dev, &dme1737_zone3_chmod_group,
					    S_IRUGO | S_IWUSR);
		}
		if (data->has_features & HAS_ZONE_HYST) {
			dme1737_chmod_group(dev, &dme1737_zone_hyst_group,
					    S_IRUGO | S_IWUSR);
		}

		/* Change permissions of PWM sysfs attributes */
		for (ix = 0; ix < ARRAY_SIZE(dme1737_pwm_chmod_group); ix++) {
			if (data->has_features & HAS_PWM(ix)) {
				dme1737_chmod_group(dev,
						&dme1737_pwm_chmod_group[ix],
						S_IRUGO | S_IWUSR);
				if ((data->has_features & HAS_PWM_MIN) &&
				    ix < 3) {
					dme1737_chmod_file(dev,
						dme1737_auto_pwm_min_attr[ix],
						S_IRUGO | S_IWUSR);
				}
			}
		}

		/* Change permissions of pwm[1-3] if in manual mode */
		for (ix = 0; ix < 3; ix++) {
			if ((data->has_features & HAS_PWM(ix)) &&
			    (PWM_EN_FROM_REG(data->pwm_config[ix]) == 1)) {
				dme1737_chmod_file(dev,
						dme1737_pwm_chmod_attr[ix],
						S_IRUGO | S_IWUSR);
			}
		}
	}

	return 0;

exit_remove:
	dme1737_remove_files(dev);
exit:
	return err;
}