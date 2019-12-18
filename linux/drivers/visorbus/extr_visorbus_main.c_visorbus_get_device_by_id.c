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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct visor_device {struct device device; } ;
struct visor_busdev {int /*<<< orphan*/  dev_no; int /*<<< orphan*/  bus_no; } ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,struct device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_visorbus_dev_by_id ; 
 struct visor_device* to_visor_device (struct device*) ; 
 int /*<<< orphan*/  visorbus_type ; 

struct visor_device *visorbus_get_device_by_id(u32 bus_no, u32 dev_no,
					       struct visor_device *from)
{
	struct device *dev;
	struct device *dev_start = NULL;
	struct visor_busdev id = {
		.bus_no = bus_no,
		.dev_no = dev_no
	};

	if (from)
		dev_start = &from->device;
	dev = bus_find_device(&visorbus_type, dev_start, (void *)&id,
			      match_visorbus_dev_by_id);
	if (!dev)
		return NULL;
	return to_visor_device(dev);
}