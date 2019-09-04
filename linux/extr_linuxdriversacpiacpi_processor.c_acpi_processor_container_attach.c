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
struct acpi_device_id {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int acpi_processor_container_attach(struct acpi_device *dev,
					   const struct acpi_device_id *id)
{
	return 1;
}