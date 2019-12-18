#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct via686a_data {char* name; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; scalar_t__ addr; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_9__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_1__ driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIA686A_EXTENT ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,unsigned long,unsigned long) ; 
 struct via686a_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct via686a_data*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ via686a_driver ; 
 int /*<<< orphan*/  via686a_group ; 
 int /*<<< orphan*/  via686a_init_device (struct via686a_data*) ; 

__attribute__((used)) static int via686a_probe(struct platform_device *pdev)
{
	struct via686a_data *data;
	struct resource *res;
	int err;

	/* Reserve the ISA region */
	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!devm_request_region(&pdev->dev, res->start, VIA686A_EXTENT,
				 via686a_driver.driver.name)) {
		dev_err(&pdev->dev, "Region 0x%lx-0x%lx already in use!\n",
			(unsigned long)res->start, (unsigned long)res->end);
		return -ENODEV;
	}

	data = devm_kzalloc(&pdev->dev, sizeof(struct via686a_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	platform_set_drvdata(pdev, data);
	data->addr = res->start;
	data->name = "via686a";
	mutex_init(&data->update_lock);

	/* Initialize the VIA686A chip */
	via686a_init_device(data);

	/* Register sysfs hooks */
	err = sysfs_create_group(&pdev->dev.kobj, &via686a_group);
	if (err)
		return err;

	data->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}

	return 0;

exit_remove_files:
	sysfs_remove_group(&pdev->dev.kobj, &via686a_group);
	return err;
}