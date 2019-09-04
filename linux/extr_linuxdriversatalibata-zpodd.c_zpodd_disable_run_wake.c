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
struct zpodd {scalar_t__ powered_off; } ;
struct ata_device {int /*<<< orphan*/  tdev; struct zpodd* zpodd; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_pm_set_device_wakeup (int /*<<< orphan*/ *,int) ; 

void zpodd_disable_run_wake(struct ata_device *dev)
{
	struct zpodd *zpodd = dev->zpodd;

	if (zpodd->powered_off)
		acpi_pm_set_device_wakeup(&dev->tdev, false);
}