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
struct vme_driver {int (* probe ) (struct vme_dev*) ;} ;
struct vme_dev {int dummy; } ;
struct device {struct vme_driver* platform_data; } ;

/* Variables and functions */
 int ENODEV ; 
 struct vme_dev* dev_to_vme_dev (struct device*) ; 
 int stub1 (struct vme_dev*) ; 

__attribute__((used)) static int vme_bus_probe(struct device *dev)
{
	struct vme_driver *driver;
	struct vme_dev *vdev = dev_to_vme_dev(dev);

	driver = dev->platform_data;
	if (driver->probe)
		return driver->probe(vdev);

	return -ENODEV;
}