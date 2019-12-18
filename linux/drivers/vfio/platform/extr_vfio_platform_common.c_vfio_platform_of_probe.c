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
struct vfio_platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  compat; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_property_read_string (struct device*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vfio_platform_of_probe(struct vfio_platform_device *vdev,
			   struct device *dev)
{
	int ret;

	ret = device_property_read_string(dev, "compatible",
					  &vdev->compat);
	if (ret)
		dev_err(dev, "Cannot retrieve compat for %s\n", vdev->name);

	return ret;
}