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
struct rpmsg_ctrldev {int /*<<< orphan*/  cdev; } ;
struct device {int /*<<< orphan*/  devt; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 struct rpmsg_ctrldev* dev_to_ctrldev (struct device*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rpmsg_ctrldev*) ; 
 int /*<<< orphan*/  rpmsg_ctrl_ida ; 
 int /*<<< orphan*/  rpmsg_minor_ida ; 

__attribute__((used)) static void rpmsg_ctrldev_release_device(struct device *dev)
{
	struct rpmsg_ctrldev *ctrldev = dev_to_ctrldev(dev);

	ida_simple_remove(&rpmsg_ctrl_ida, dev->id);
	ida_simple_remove(&rpmsg_minor_ida, MINOR(dev->devt));
	cdev_del(&ctrldev->cdev);
	kfree(ctrldev);
}