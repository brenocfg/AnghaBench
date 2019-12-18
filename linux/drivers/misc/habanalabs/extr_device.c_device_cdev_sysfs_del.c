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
struct hl_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  dev_ctrl; int /*<<< orphan*/  cdev_ctrl; int /*<<< orphan*/  cdev_sysfs_created; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_sysfs_fini (struct hl_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_cdev_sysfs_del(struct hl_device *hdev)
{
	/* device_release() won't be called so must free devices explicitly */
	if (!hdev->cdev_sysfs_created) {
		kfree(hdev->dev_ctrl);
		kfree(hdev->dev);
		return;
	}

	hl_sysfs_fini(hdev);
	cdev_device_del(&hdev->cdev_ctrl, hdev->dev_ctrl);
	cdev_device_del(&hdev->cdev, hdev->dev);
}