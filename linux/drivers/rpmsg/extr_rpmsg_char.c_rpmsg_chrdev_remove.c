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
struct rpmsg_device {int /*<<< orphan*/  dev; } ;
struct rpmsg_ctrldev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rpmsg_ctrldev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpmsg_eptdev_destroy ; 

__attribute__((used)) static void rpmsg_chrdev_remove(struct rpmsg_device *rpdev)
{
	struct rpmsg_ctrldev *ctrldev = dev_get_drvdata(&rpdev->dev);
	int ret;

	/* Destroy all endpoints */
	ret = device_for_each_child(&ctrldev->dev, NULL, rpmsg_eptdev_destroy);
	if (ret)
		dev_warn(&rpdev->dev, "failed to nuke endpoints: %d\n", ret);

	device_del(&ctrldev->dev);
	put_device(&ctrldev->dev);
}