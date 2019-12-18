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
struct visor_device {scalar_t__ chipset_bus_no; scalar_t__ chipset_dev_no; } ;
struct visor_busdev {scalar_t__ bus_no; scalar_t__ dev_no; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct visor_device* to_visor_device (struct device*) ; 

__attribute__((used)) static int match_visorbus_dev_by_id(struct device *dev, const void *data)
{
	struct visor_device *vdev = to_visor_device(dev);
	const struct visor_busdev *id = data;

	if (vdev->chipset_bus_no == id->bus_no &&
	    vdev->chipset_dev_no == id->dev_no)
		return 1;
	return 0;
}