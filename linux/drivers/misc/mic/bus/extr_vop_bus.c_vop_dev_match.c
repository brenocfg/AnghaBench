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
struct vop_device_id {scalar_t__ device; } ;
struct vop_device {int dummy; } ;
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct vop_device_id* id_table; } ;

/* Variables and functions */
 struct vop_device* dev_to_vop (struct device*) ; 
 TYPE_1__* drv_to_vop (struct device_driver*) ; 
 scalar_t__ vop_id_match (struct vop_device*,struct vop_device_id const*) ; 

__attribute__((used)) static int vop_dev_match(struct device *dv, struct device_driver *dr)
{
	unsigned int i;
	struct vop_device *dev = dev_to_vop(dv);
	const struct vop_device_id *ids;

	ids = drv_to_vop(dr)->id_table;
	for (i = 0; ids[i].device; i++)
		if (vop_id_match(dev, &ids[i]))
			return 1;
	return 0;
}