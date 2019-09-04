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
struct TYPE_2__ {int dev; } ;
struct mei_device {TYPE_1__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mei_class ; 
 int /*<<< orphan*/  mei_dbgfs_deregister (struct mei_device*) ; 
 int /*<<< orphan*/  mei_minor_free (struct mei_device*) ; 

void mei_deregister(struct mei_device *dev)
{
	int devno;

	devno = dev->cdev.dev;
	cdev_del(&dev->cdev);

	mei_dbgfs_deregister(dev);

	device_destroy(mei_class, devno);

	mei_minor_free(dev);
}