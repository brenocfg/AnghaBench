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
struct thermal_cooling_device {struct acpi_device* devdata; } ;
struct acpi_processor {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct acpi_processor* acpi_driver_data (struct acpi_device*) ; 
 unsigned long acpi_processor_max_state (struct acpi_processor*) ; 

__attribute__((used)) static int
processor_get_max_state(struct thermal_cooling_device *cdev,
			unsigned long *state)
{
	struct acpi_device *device = cdev->devdata;
	struct acpi_processor *pr;

	if (!device)
		return -EINVAL;

	pr = acpi_driver_data(device);
	if (!pr)
		return -EINVAL;

	*state = acpi_processor_max_state(pr);
	return 0;
}