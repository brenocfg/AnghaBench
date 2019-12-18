#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int vflag; int (* get_vendor ) () ;TYPE_1__* of_dev; int /*<<< orphan*/  of_node; scalar_t__ worker_irqs; int /*<<< orphan*/  orient2; int /*<<< orphan*/  orient1; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ams_freefall_client ; 
 TYPE_3__ ams_info ; 
 int ams_input_init () ; 
 int /*<<< orphan*/  ams_shock_client ; 
 int /*<<< orphan*/  dev_attr_current ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* of_platform_device_create (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int pmf_register_irq_client (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmf_unregister_irq_client (int /*<<< orphan*/ *) ; 
 int stub1 () ; 

int ams_sensor_attach(void)
{
	int result;
	const u32 *prop;

	/* Get orientation */
	prop = of_get_property(ams_info.of_node, "orientation", NULL);
	if (!prop)
		return -ENODEV;
	ams_info.orient1 = *prop;
	ams_info.orient2 = *(prop + 1);

	/* Register freefall interrupt handler */
	result = pmf_register_irq_client(ams_info.of_node,
			"accel-int-1",
			&ams_freefall_client);
	if (result < 0)
		return -ENODEV;

	/* Reset saved irqs */
	ams_info.worker_irqs = 0;

	/* Register shock interrupt handler */
	result = pmf_register_irq_client(ams_info.of_node,
			"accel-int-2",
			&ams_shock_client);
	if (result < 0)
		goto release_freefall;

	/* Create device */
	ams_info.of_dev = of_platform_device_create(ams_info.of_node, "ams", NULL);
	if (!ams_info.of_dev) {
		result = -ENODEV;
		goto release_shock;
	}

	/* Create attributes */
	result = device_create_file(&ams_info.of_dev->dev, &dev_attr_current);
	if (result)
		goto release_of;

	ams_info.vflag = !!(ams_info.get_vendor() & 0x10);

	/* Init input device */
	result = ams_input_init();
	if (result)
		goto release_device_file;

	return result;
release_device_file:
	device_remove_file(&ams_info.of_dev->dev, &dev_attr_current);
release_of:
	of_device_unregister(ams_info.of_dev);
release_shock:
	pmf_unregister_irq_client(&ams_shock_client);
release_freefall:
	pmf_unregister_irq_client(&ams_freefall_client);
	return result;
}