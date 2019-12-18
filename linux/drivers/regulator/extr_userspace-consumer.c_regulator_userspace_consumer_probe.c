#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct userspace_consumer_data {scalar_t__ enabled; int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; } ;
struct regulator_userspace_consumer_data {scalar_t__ init_on; int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  attr_group ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct regulator_userspace_consumer_data* dev_get_platdata (TYPE_1__*) ; 
 struct userspace_consumer_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct userspace_consumer_data*) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int regulator_userspace_consumer_probe(struct platform_device *pdev)
{
	struct regulator_userspace_consumer_data *pdata;
	struct userspace_consumer_data *drvdata;
	int ret;

	pdata = dev_get_platdata(&pdev->dev);
	if (!pdata)
		return -EINVAL;

	drvdata = devm_kzalloc(&pdev->dev,
			       sizeof(struct userspace_consumer_data),
			       GFP_KERNEL);
	if (drvdata == NULL)
		return -ENOMEM;

	drvdata->name = pdata->name;
	drvdata->num_supplies = pdata->num_supplies;
	drvdata->supplies = pdata->supplies;

	mutex_init(&drvdata->lock);

	ret = devm_regulator_bulk_get(&pdev->dev, drvdata->num_supplies,
				      drvdata->supplies);
	if (ret) {
		dev_err(&pdev->dev, "Failed to get supplies: %d\n", ret);
		return ret;
	}

	ret = sysfs_create_group(&pdev->dev.kobj, &attr_group);
	if (ret != 0)
		return ret;

	if (pdata->init_on) {
		ret = regulator_bulk_enable(drvdata->num_supplies,
					    drvdata->supplies);
		if (ret) {
			dev_err(&pdev->dev,
				"Failed to set initial state: %d\n", ret);
			goto err_enable;
		}
	}

	drvdata->enabled = pdata->init_on;
	platform_set_drvdata(pdev, drvdata);

	return 0;

err_enable:
	sysfs_remove_group(&pdev->dev.kobj, &attr_group);

	return ret;
}