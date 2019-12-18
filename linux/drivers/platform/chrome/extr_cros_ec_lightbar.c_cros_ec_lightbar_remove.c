#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct cros_ec_dev {TYPE_2__ class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cros_ec_lightbar_attr_group ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lb_manual_suspend_ctrl (struct cros_ec_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_lightbar_remove(struct platform_device *pd)
{
	struct cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);

	sysfs_remove_group(&ec_dev->class_dev.kobj,
			   &cros_ec_lightbar_attr_group);

	/* Let the EC take over the lightbar again. */
	lb_manual_suspend_ctrl(ec_dev, 0);

	return 0;
}