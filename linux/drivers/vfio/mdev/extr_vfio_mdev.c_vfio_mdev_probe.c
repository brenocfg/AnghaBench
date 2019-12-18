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
struct mdev_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct mdev_device* to_mdev_device (struct device*) ; 
 int vfio_add_group_dev (struct device*,int /*<<< orphan*/ *,struct mdev_device*) ; 
 int /*<<< orphan*/  vfio_mdev_dev_ops ; 

__attribute__((used)) static int vfio_mdev_probe(struct device *dev)
{
	struct mdev_device *mdev = to_mdev_device(dev);

	return vfio_add_group_dev(dev, &vfio_mdev_dev_ops, mdev);
}