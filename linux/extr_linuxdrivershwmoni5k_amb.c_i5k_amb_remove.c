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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_attr; } ;
struct i5k_amb_data {int num_attrs; int /*<<< orphan*/  amb_len; int /*<<< orphan*/  amb_base; int /*<<< orphan*/  amb_mmio; struct i5k_amb_data* attrs; TYPE_1__ s_attr; int /*<<< orphan*/  hwmon_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_name ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i5k_amb_data*) ; 
 struct i5k_amb_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i5k_amb_remove(struct platform_device *pdev)
{
	int i;
	struct i5k_amb_data *data = platform_get_drvdata(pdev);

	hwmon_device_unregister(data->hwmon_dev);
	device_remove_file(&pdev->dev, &dev_attr_name);
	for (i = 0; i < data->num_attrs; i++)
		device_remove_file(&pdev->dev, &data->attrs[i].s_attr.dev_attr);
	kfree(data->attrs);
	iounmap(data->amb_mmio);
	release_mem_region(data->amb_base, data->amb_len);
	kfree(data);
	return 0;
}