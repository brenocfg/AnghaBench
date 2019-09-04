#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sis5595_data {char* name; scalar_t__ revision; int maxins; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/ * fan_min; int /*<<< orphan*/  addr; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  lock; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_10__ {scalar_t__ revision; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ REV2MIN ; 
 int /*<<< orphan*/  SIS5595_EXTENT ; 
 int /*<<< orphan*/  SIS5595_PIN_REG ; 
 int /*<<< orphan*/  SIS5595_REG_FAN_MIN (int) ; 
 struct sis5595_data* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sis5595_data*) ; 
 TYPE_3__* s_bridge ; 
 TYPE_2__ sis5595_driver ; 
 int /*<<< orphan*/  sis5595_group ; 
 int /*<<< orphan*/  sis5595_group_in4 ; 
 int /*<<< orphan*/  sis5595_group_temp1 ; 
 int /*<<< orphan*/  sis5595_init_device (struct sis5595_data*) ; 
 int /*<<< orphan*/  sis5595_read_value (struct sis5595_data*,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sis5595_probe(struct platform_device *pdev)
{
	int err = 0;
	int i;
	struct sis5595_data *data;
	struct resource *res;
	char val;

	/* Reserve the ISA region */
	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!devm_request_region(&pdev->dev, res->start, SIS5595_EXTENT,
				 sis5595_driver.driver.name))
		return -EBUSY;

	data = devm_kzalloc(&pdev->dev, sizeof(struct sis5595_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	mutex_init(&data->lock);
	mutex_init(&data->update_lock);
	data->addr = res->start;
	data->name = "sis5595";
	platform_set_drvdata(pdev, data);

	/*
	 * Check revision and pin registers to determine whether 4 or 5 voltages
	 */
	data->revision = s_bridge->revision;
	/* 4 voltages, 1 temp */
	data->maxins = 3;
	if (data->revision >= REV2MIN) {
		pci_read_config_byte(s_bridge, SIS5595_PIN_REG, &val);
		if (!(val & 0x80))
			/* 5 voltages, no temps */
			data->maxins = 4;
	}

	/* Initialize the SIS5595 chip */
	sis5595_init_device(data);

	/* A few vars need to be filled upon startup */
	for (i = 0; i < 2; i++) {
		data->fan_min[i] = sis5595_read_value(data,
					SIS5595_REG_FAN_MIN(i));
	}

	/* Register sysfs hooks */
	err = sysfs_create_group(&pdev->dev.kobj, &sis5595_group);
	if (err)
		return err;
	if (data->maxins == 4) {
		err = sysfs_create_group(&pdev->dev.kobj, &sis5595_group_in4);
		if (err)
			goto exit_remove_files;
	} else {
		err = sysfs_create_group(&pdev->dev.kobj, &sis5595_group_temp1);
		if (err)
			goto exit_remove_files;
	}

	data->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}

	return 0;

exit_remove_files:
	sysfs_remove_group(&pdev->dev.kobj, &sis5595_group);
	sysfs_remove_group(&pdev->dev.kobj, &sis5595_group_in4);
	sysfs_remove_group(&pdev->dev.kobj, &sis5595_group_temp1);
	return err;
}