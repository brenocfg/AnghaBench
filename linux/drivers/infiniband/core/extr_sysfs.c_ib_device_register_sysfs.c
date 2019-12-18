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
struct TYPE_2__ {scalar_t__ alloc_hw_stats; } ;
struct ib_device {TYPE_1__ ops; int /*<<< orphan*/  coredev; } ;

/* Variables and functions */
 int ib_setup_port_attrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_hw_stats (struct ib_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ib_device_register_sysfs(struct ib_device *device)
{
	int ret;

	ret = ib_setup_port_attrs(&device->coredev);
	if (ret)
		return ret;

	if (device->ops.alloc_hw_stats)
		setup_hw_stats(device, NULL, 0);

	return 0;
}