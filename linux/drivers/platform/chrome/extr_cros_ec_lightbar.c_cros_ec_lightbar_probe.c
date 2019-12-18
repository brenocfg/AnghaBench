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
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct cros_ec_platform {int /*<<< orphan*/  ec_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct cros_ec_dev {TYPE_1__ class_dev; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CROS_EC_DEV_NAME ; 
 int ENODEV ; 
 TYPE_2__ cros_ec_lightbar_attr_group ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct cros_ec_platform* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_lightbar_version (struct cros_ec_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lb_manual_suspend_ctrl (struct cros_ec_dev*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int cros_ec_lightbar_probe(struct platform_device *pd)
{
	struct cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);
	struct cros_ec_platform *pdata = dev_get_platdata(ec_dev->dev);
	struct device *dev = &pd->dev;
	int ret;

	/*
	 * Only instantiate the lightbar if the EC name is 'cros_ec'. Other EC
	 * devices like 'cros_pd' doesn't have a lightbar.
	 */
	if (strcmp(pdata->ec_name, CROS_EC_DEV_NAME) != 0)
		return -ENODEV;

	/*
	 * Ask then for the lightbar version, if it's 0 then the 'cros_ec'
	 * doesn't have a lightbar.
	 */
	if (!get_lightbar_version(ec_dev, NULL, NULL))
		return -ENODEV;

	/* Take control of the lightbar from the EC. */
	lb_manual_suspend_ctrl(ec_dev, 1);

	ret = sysfs_create_group(&ec_dev->class_dev.kobj,
				 &cros_ec_lightbar_attr_group);
	if (ret < 0)
		dev_err(dev, "failed to create %s attributes. err=%d\n",
			cros_ec_lightbar_attr_group.name, ret);

	return ret;
}