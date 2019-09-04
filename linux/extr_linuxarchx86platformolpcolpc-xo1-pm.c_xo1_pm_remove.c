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
struct platform_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ acpi_base ; 
 int /*<<< orphan*/  mfd_cell_disable (struct platform_device*) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 scalar_t__ pms_base ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int xo1_pm_remove(struct platform_device *pdev)
{
	mfd_cell_disable(pdev);

	if (strcmp(pdev->name, "cs5535-pms") == 0)
		pms_base = 0;
	else if (strcmp(pdev->name, "olpc-xo1-pm-acpi") == 0)
		acpi_base = 0;

	pm_power_off = NULL;
	return 0;
}