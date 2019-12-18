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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct ib_device {int /*<<< orphan*/  coredev; int /*<<< orphan*/  hw_stats; scalar_t__ hw_stats_ag; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_hsag (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ib_free_port_attrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void ib_device_unregister_sysfs(struct ib_device *device)
{
	if (device->hw_stats_ag)
		free_hsag(&device->dev.kobj, device->hw_stats_ag);
	kfree(device->hw_stats);

	ib_free_port_attrs(&device->coredev);
}