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
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 scalar_t__ AE_NOT_FOUND ; 
 int ENXIO ; 
 scalar_t__ acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int sony_pic_disable(struct acpi_device *device)
{
	acpi_status ret = acpi_evaluate_object(device->handle, "_DIS", NULL,
					       NULL);

	if (ACPI_FAILURE(ret) && ret != AE_NOT_FOUND)
		return -ENXIO;

	dprintk("Device disabled\n");
	return 0;
}