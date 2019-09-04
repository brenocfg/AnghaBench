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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  acpi_dev_remove_driver_gpios (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devm_acpi_dev_release_driver_gpios(struct device *dev, void *res)
{
	acpi_dev_remove_driver_gpios(ACPI_COMPANION(dev));
}