#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {scalar_t__ irq_handler; int /*<<< orphan*/  show_label; int /*<<< orphan*/  show_name; int /*<<< orphan*/  read_sensor; } ;
struct abx500_temp {int /*<<< orphan*/  hwmon_dev; TYPE_1__ ops; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; struct platform_device* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DEFERRABLE_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int abx500_hwmon_init (struct abx500_temp*) ; 
 int /*<<< orphan*/  abx500_temp_group ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct abx500_temp* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpadc_monitor ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct abx500_temp*) ; 
 int setup_irqs (struct platform_device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int abx500_temp_probe(struct platform_device *pdev)
{
	struct abx500_temp *data;
	int err;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->pdev = pdev;
	mutex_init(&data->lock);

	/* Chip specific initialization */
	err = abx500_hwmon_init(data);
	if (err	< 0 || !data->ops.read_sensor || !data->ops.show_name ||
			!data->ops.show_label)
		return err;

	INIT_DEFERRABLE_WORK(&data->work, gpadc_monitor);

	platform_set_drvdata(pdev, data);

	err = sysfs_create_group(&pdev->dev.kobj, &abx500_temp_group);
	if (err < 0) {
		dev_err(&pdev->dev, "Create sysfs group failed (%d)\n", err);
		return err;
	}

	data->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		dev_err(&pdev->dev, "Class registration failed (%d)\n", err);
		goto exit_sysfs_group;
	}

	if (data->ops.irq_handler) {
		err = setup_irqs(pdev);
		if (err < 0)
			goto exit_hwmon_reg;
	}
	return 0;

exit_hwmon_reg:
	hwmon_device_unregister(data->hwmon_dev);
exit_sysfs_group:
	sysfs_remove_group(&pdev->dev.kobj, &abx500_temp_group);
	return err;
}