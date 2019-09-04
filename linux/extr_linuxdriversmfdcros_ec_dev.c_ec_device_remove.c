#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cros_ec_dev {int /*<<< orphan*/  class_dev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cros_ec_debugfs_remove (struct cros_ec_dev*) ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lb_manual_suspend_ctrl (struct cros_ec_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ec_device_remove(struct platform_device *pdev)
{
	struct cros_ec_dev *ec = dev_get_drvdata(&pdev->dev);

	/* Let the EC take over the lightbar again. */
	lb_manual_suspend_ctrl(ec, 0);

	cros_ec_debugfs_remove(ec);

	mfd_remove_devices(ec->dev);
	cdev_del(&ec->cdev);
	device_unregister(&ec->class_dev);
	return 0;
}