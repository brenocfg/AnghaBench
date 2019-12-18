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
struct cros_ec_device {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALL_NOTIFY ; 
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cros_ec_lpc_acpi_notify ; 
 int cros_ec_unregister (struct cros_ec_device*) ; 
 struct cros_ec_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cros_ec_lpc_remove(struct platform_device *pdev)
{
	struct cros_ec_device *ec_dev = platform_get_drvdata(pdev);
	struct acpi_device *adev;

	adev = ACPI_COMPANION(&pdev->dev);
	if (adev)
		acpi_remove_notify_handler(adev->handle, ACPI_ALL_NOTIFY,
					   cros_ec_lpc_acpi_notify);

	return cros_ec_unregister(ec_dev);
}