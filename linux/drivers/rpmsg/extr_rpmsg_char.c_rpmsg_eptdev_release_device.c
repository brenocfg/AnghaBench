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
struct TYPE_2__ {int /*<<< orphan*/  devt; } ;
struct rpmsg_eptdev {int /*<<< orphan*/  cdev; TYPE_1__ dev; } ;
struct device {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 struct rpmsg_eptdev* dev_to_eptdev (struct device*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rpmsg_eptdev*) ; 
 int /*<<< orphan*/  rpmsg_ept_ida ; 
 int /*<<< orphan*/  rpmsg_minor_ida ; 

__attribute__((used)) static void rpmsg_eptdev_release_device(struct device *dev)
{
	struct rpmsg_eptdev *eptdev = dev_to_eptdev(dev);

	ida_simple_remove(&rpmsg_ept_ida, dev->id);
	ida_simple_remove(&rpmsg_minor_ida, MINOR(eptdev->dev.devt));
	cdev_del(&eptdev->cdev);
	kfree(eptdev);
}