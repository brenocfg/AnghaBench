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
struct rbtn_data {scalar_t__ type; } ;
struct device {int dummy; } ;
struct acpi_device {struct rbtn_data* driver_data; } ;

/* Variables and functions */
 scalar_t__ RBTN_SLIDER ; 
 int /*<<< orphan*/  rbtn_rfkill_exit (struct acpi_device*) ; 
 int /*<<< orphan*/  rbtn_rfkill_init (struct acpi_device*) ; 
 struct acpi_device* to_acpi_device (struct device*) ; 

__attribute__((used)) static int rbtn_switch_dev(struct device *dev, void *data)
{
	struct acpi_device *device = to_acpi_device(dev);
	struct rbtn_data *rbtn_data = device->driver_data;
	bool enable = data;

	if (rbtn_data->type != RBTN_SLIDER)
		return 0;

	if (enable)
		rbtn_rfkill_init(device);
	else
		rbtn_rfkill_exit(device);

	return 0;
}