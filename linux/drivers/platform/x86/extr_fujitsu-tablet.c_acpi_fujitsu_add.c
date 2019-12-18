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
struct acpi_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  io_length; int /*<<< orphan*/  io_base; int /*<<< orphan*/  irq; int /*<<< orphan*/  phys; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 char* ACPI_FUJITSU_CLASS ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  MODULENAME ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 char* acpi_device_hid (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ fujitsu ; 
 int /*<<< orphan*/  fujitsu_interrupt ; 
 int /*<<< orphan*/  fujitsu_reset () ; 
 int /*<<< orphan*/  fujitsu_walk_resources ; 
 int /*<<< orphan*/  input_fujitsu_remove () ; 
 int input_fujitsu_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int acpi_fujitsu_add(struct acpi_device *adev)
{
	acpi_status status;
	int error;

	if (!adev)
		return -EINVAL;

	status = acpi_walk_resources(adev->handle, METHOD_NAME__CRS,
			fujitsu_walk_resources, NULL);
	if (ACPI_FAILURE(status) || !fujitsu.irq || !fujitsu.io_base)
		return -ENODEV;

	sprintf(acpi_device_name(adev), "Fujitsu %s", acpi_device_hid(adev));
	sprintf(acpi_device_class(adev), "%s", ACPI_FUJITSU_CLASS);

	snprintf(fujitsu.phys, sizeof(fujitsu.phys),
			"%s/input0", acpi_device_hid(adev));

	error = input_fujitsu_setup(&adev->dev,
		acpi_device_name(adev), fujitsu.phys);
	if (error)
		return error;

	if (!request_region(fujitsu.io_base, fujitsu.io_length, MODULENAME)) {
		input_fujitsu_remove();
		return -EBUSY;
	}

	fujitsu_reset();

	error = request_irq(fujitsu.irq, fujitsu_interrupt,
			IRQF_SHARED, MODULENAME, fujitsu_interrupt);
	if (error) {
		release_region(fujitsu.io_base, fujitsu.io_length);
		input_fujitsu_remove();
		return error;
	}

	return 0;
}