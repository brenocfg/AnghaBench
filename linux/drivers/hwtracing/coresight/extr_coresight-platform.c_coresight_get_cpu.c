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
struct device {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int acpi_coresight_get_cpu (struct device*) ; 
 scalar_t__ is_acpi_device_node (int /*<<< orphan*/ ) ; 
 scalar_t__ is_of_node (int /*<<< orphan*/ ) ; 
 int of_coresight_get_cpu (struct device*) ; 

int coresight_get_cpu(struct device *dev)
{
	if (is_of_node(dev->fwnode))
		return of_coresight_get_cpu(dev);
	else if (is_acpi_device_node(dev->fwnode))
		return acpi_coresight_get_cpu(dev);
	return 0;
}