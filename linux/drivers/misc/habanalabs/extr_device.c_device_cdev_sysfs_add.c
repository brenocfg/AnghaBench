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
struct hl_device {int cdev_sysfs_created; int /*<<< orphan*/  dev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  dev_ctrl; int /*<<< orphan*/  cdev_ctrl; } ;

/* Variables and functions */
 int cdev_device_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hl_sysfs_init (struct hl_device*) ; 

__attribute__((used)) static int device_cdev_sysfs_add(struct hl_device *hdev)
{
	int rc;

	rc = cdev_device_add(&hdev->cdev, hdev->dev);
	if (rc) {
		dev_err(hdev->dev,
			"failed to add a char device to the system\n");
		return rc;
	}

	rc = cdev_device_add(&hdev->cdev_ctrl, hdev->dev_ctrl);
	if (rc) {
		dev_err(hdev->dev,
			"failed to add a control char device to the system\n");
		goto delete_cdev_device;
	}

	/* hl_sysfs_init() must be done after adding the device to the system */
	rc = hl_sysfs_init(hdev);
	if (rc) {
		dev_err(hdev->dev, "failed to initialize sysfs\n");
		goto delete_ctrl_cdev_device;
	}

	hdev->cdev_sysfs_created = true;

	return 0;

delete_ctrl_cdev_device:
	cdev_device_del(&hdev->cdev_ctrl, hdev->dev_ctrl);
delete_cdev_device:
	cdev_device_del(&hdev->cdev, hdev->dev);
	return rc;
}