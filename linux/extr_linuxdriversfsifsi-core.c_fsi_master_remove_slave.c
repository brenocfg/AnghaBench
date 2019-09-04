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
struct fsi_slave {int /*<<< orphan*/  dev; int /*<<< orphan*/  cdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_for_each_child (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_slave_remove_device ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct fsi_slave* to_fsi_slave (struct device*) ; 

__attribute__((used)) static int fsi_master_remove_slave(struct device *dev, void *arg)
{
	struct fsi_slave *slave = to_fsi_slave(dev);

	device_for_each_child(dev, NULL, fsi_slave_remove_device);
	cdev_device_del(&slave->cdev, &slave->dev);
	put_device(dev);
	return 0;
}