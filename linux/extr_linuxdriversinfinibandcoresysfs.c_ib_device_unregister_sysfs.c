#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct ib_device {TYPE_1__ dev; int /*<<< orphan*/  hw_stats_ag; scalar_t__ hw_stats; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  free_hsag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_port_list_attributes (struct ib_device*) ; 
 int /*<<< orphan*/ * ib_class_attributes ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  kobject_get (int /*<<< orphan*/ *) ; 

void ib_device_unregister_sysfs(struct ib_device *device)
{
	int i;

	/* Hold kobject until ib_dealloc_device() */
	kobject_get(&device->dev.kobj);

	free_port_list_attributes(device);

	if (device->hw_stats) {
		kfree(device->hw_stats);
		free_hsag(&device->dev.kobj, device->hw_stats_ag);
	}

	for (i = 0; i < ARRAY_SIZE(ib_class_attributes); ++i)
		device_remove_file(&device->dev, ib_class_attributes[i]);

	device_unregister(&device->dev);
}