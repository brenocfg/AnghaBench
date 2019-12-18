#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct cros_ec_platform {int /*<<< orphan*/  ec_name; } ;
struct cros_ec_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  name; int /*<<< orphan*/ * fops; int /*<<< orphan*/  minor; } ;
struct chardev_data {TYPE_1__ misc; struct cros_ec_dev* ec_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MISC_DYNAMIC_MINOR ; 
 int /*<<< orphan*/  chardev_fops ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_platform* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_2__*,struct chardev_data*) ; 
 struct chardev_data* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int misc_register (TYPE_1__*) ; 

__attribute__((used)) static int cros_ec_chardev_probe(struct platform_device *pdev)
{
	struct cros_ec_dev *ec_dev = dev_get_drvdata(pdev->dev.parent);
	struct cros_ec_platform *ec_platform = dev_get_platdata(ec_dev->dev);
	struct chardev_data *data;

	/* Create a char device: we want to create it anew */
	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->ec_dev = ec_dev;
	data->misc.minor = MISC_DYNAMIC_MINOR;
	data->misc.fops = &chardev_fops;
	data->misc.name = ec_platform->ec_name;
	data->misc.parent = pdev->dev.parent;

	dev_set_drvdata(&pdev->dev, data);

	return misc_register(&data->misc);
}