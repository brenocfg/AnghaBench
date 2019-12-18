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
struct platform_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  METHOD_NAME__CRS ; 
 int /*<<< orphan*/  acpi_has_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_walk_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  count_registers_cb ; 

__attribute__((used)) static int count_registers(struct platform_device *pdev)
{
	acpi_handle ahandle = ACPI_HANDLE(&pdev->dev);
	acpi_status status;
	int count = 0;

	if (!acpi_has_method(ahandle, METHOD_NAME__CRS))
		return -EINVAL;

	status = acpi_walk_resources(ahandle, METHOD_NAME__CRS,
				     count_registers_cb, &count);
	if (ACPI_FAILURE(status))
		return -EINVAL;
	return count;
}