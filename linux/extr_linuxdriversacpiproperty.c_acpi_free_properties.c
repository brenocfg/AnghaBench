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
struct TYPE_2__ {int /*<<< orphan*/ * properties; int /*<<< orphan*/ * pointer; int /*<<< orphan*/ * of_compatible; int /*<<< orphan*/  subnodes; } ;
struct acpi_device {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (void*) ; 
 int /*<<< orphan*/  acpi_destroy_nondev_subnodes (int /*<<< orphan*/ *) ; 

void acpi_free_properties(struct acpi_device *adev)
{
	acpi_destroy_nondev_subnodes(&adev->data.subnodes);
	ACPI_FREE((void *)adev->data.pointer);
	adev->data.of_compatible = NULL;
	adev->data.pointer = NULL;
	adev->data.properties = NULL;
}