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
struct TYPE_2__ {int /*<<< orphan*/  devt; } ;
struct event_device_data {TYPE_1__ dev; int /*<<< orphan*/  cdev; } ;
struct acpi_device {struct event_device_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  event_ida ; 
 int /*<<< orphan*/  hangup_device (struct event_device_data*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int event_device_remove(struct acpi_device *adev)
{
	struct event_device_data *dev_data = adev->driver_data;

	cdev_device_del(&dev_data->cdev, &dev_data->dev);
	ida_simple_remove(&event_ida, MINOR(dev_data->dev.devt));
	hangup_device(dev_data);

	return 0;
}