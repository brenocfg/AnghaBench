#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;
struct f71805f_sio_data {size_t kind; int fnsel1; } ;
struct f71805f_data {char* name; int has_in; int* fan_ctrl; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ ADDR_REG_OFFSET ; 
 int /*<<< orphan*/  DRVNAME ; 
 int EBUSY ; 
 int ENOMEM ; 
 int FAN_CTRL_DC_MODE ; 
 int FAN_CTRL_MODE_MANUAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int,...) ; 
 struct f71805f_sio_data* dev_get_platdata (TYPE_1__*) ; 
 struct f71805f_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (TYPE_1__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
#define  f71805f 129 
 int /*<<< orphan*/ * f71805f_attr_pwm ; 
 int /*<<< orphan*/ * f71805f_attributes_pwm_freq ; 
 int /*<<< orphan*/  f71805f_group ; 
 int /*<<< orphan*/ * f71805f_group_optin ; 
 int /*<<< orphan*/  f71805f_group_pwm_freq ; 
 int /*<<< orphan*/  f71805f_init_device (struct f71805f_data*) ; 
#define  f71872f 128 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct f71805f_data*) ; 
 int sysfs_chmod_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int f71805f_probe(struct platform_device *pdev)
{
	struct f71805f_sio_data *sio_data = dev_get_platdata(&pdev->dev);
	struct f71805f_data *data;
	struct resource *res;
	int i, err;

	static const char * const names[] = {
		"f71805f",
		"f71872f",
	};

	data = devm_kzalloc(&pdev->dev, sizeof(struct f71805f_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!devm_request_region(&pdev->dev, res->start + ADDR_REG_OFFSET, 2,
				 DRVNAME)) {
		dev_err(&pdev->dev, "Failed to request region 0x%lx-0x%lx\n",
			(unsigned long)(res->start + ADDR_REG_OFFSET),
			(unsigned long)(res->start + ADDR_REG_OFFSET + 1));
		return -EBUSY;
	}
	data->addr = res->start;
	data->name = names[sio_data->kind];
	mutex_init(&data->update_lock);

	platform_set_drvdata(pdev, data);

	/* Some voltage inputs depend on chip model and configuration */
	switch (sio_data->kind) {
	case f71805f:
		data->has_in = 0x1ff;
		break;
	case f71872f:
		data->has_in = 0x6ef;
		if (sio_data->fnsel1 & 0x01)
			data->has_in |= (1 << 4); /* in4 */
		if (sio_data->fnsel1 & 0x02)
			data->has_in |= (1 << 8); /* in8 */
		break;
	}

	/* Initialize the F71805F chip */
	f71805f_init_device(data);

	/* Register sysfs interface files */
	err = sysfs_create_group(&pdev->dev.kobj, &f71805f_group);
	if (err)
		return err;
	if (data->has_in & (1 << 4)) { /* in4 */
		err = sysfs_create_group(&pdev->dev.kobj,
					 &f71805f_group_optin[0]);
		if (err)
			goto exit_remove_files;
	}
	if (data->has_in & (1 << 8)) { /* in8 */
		err = sysfs_create_group(&pdev->dev.kobj,
					 &f71805f_group_optin[1]);
		if (err)
			goto exit_remove_files;
	}
	if (data->has_in & (1 << 9)) { /* in9 (F71872F/FG only) */
		err = sysfs_create_group(&pdev->dev.kobj,
					 &f71805f_group_optin[2]);
		if (err)
			goto exit_remove_files;
	}
	if (data->has_in & (1 << 10)) { /* in9 (F71872F/FG only) */
		err = sysfs_create_group(&pdev->dev.kobj,
					 &f71805f_group_optin[3]);
		if (err)
			goto exit_remove_files;
	}
	for (i = 0; i < 3; i++) {
		/* If control mode is PWM, create pwm_freq file */
		if (!(data->fan_ctrl[i] & FAN_CTRL_DC_MODE)) {
			err = sysfs_create_file(&pdev->dev.kobj,
						f71805f_attributes_pwm_freq[i]);
			if (err)
				goto exit_remove_files;
		}
		/* If PWM is in manual mode, add write permission */
		if (data->fan_ctrl[i] & FAN_CTRL_MODE_MANUAL) {
			err = sysfs_chmod_file(&pdev->dev.kobj,
					       f71805f_attr_pwm[i],
					       S_IRUGO | S_IWUSR);
			if (err) {
				dev_err(&pdev->dev, "chmod +w pwm%d failed\n",
					i + 1);
				goto exit_remove_files;
			}
		}
	}

	data->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		dev_err(&pdev->dev, "Class registration failed (%d)\n", err);
		goto exit_remove_files;
	}

	return 0;

exit_remove_files:
	sysfs_remove_group(&pdev->dev.kobj, &f71805f_group);
	for (i = 0; i < 4; i++)
		sysfs_remove_group(&pdev->dev.kobj, &f71805f_group_optin[i]);
	sysfs_remove_group(&pdev->dev.kobj, &f71805f_group_pwm_freq);
	return err;
}