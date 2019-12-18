#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {struct device* parent; } ;
struct TYPE_3__ {TYPE_2__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  matrix_bus ; 
 TYPE_1__* matrix_dev ; 
 int /*<<< orphan*/  matrix_driver ; 
 int /*<<< orphan*/  root_device_unregister (struct device*) ; 

__attribute__((used)) static void vfio_ap_matrix_dev_destroy(void)
{
	struct device *root_device = matrix_dev->device.parent;

	driver_unregister(&matrix_driver);
	device_unregister(&matrix_dev->device);
	bus_unregister(&matrix_bus);
	root_device_unregister(root_device);
}