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
struct acpi_device {scalar_t__ handle; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ hed_handle ; 

__attribute__((used)) static int acpi_hed_add(struct acpi_device *device)
{
	/* Only one hardware error device */
	if (hed_handle)
		return -EINVAL;
	hed_handle = device->handle;
	return 0;
}