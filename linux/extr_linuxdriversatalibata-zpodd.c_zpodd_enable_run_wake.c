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
struct zpodd {int powered_off; } ;
struct ata_device {int /*<<< orphan*/  tdev; int /*<<< orphan*/  sdev; struct zpodd* zpodd; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_pm_set_device_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sdev_disable_disk_events (int /*<<< orphan*/ ) ; 

void zpodd_enable_run_wake(struct ata_device *dev)
{
	struct zpodd *zpodd = dev->zpodd;

	sdev_disable_disk_events(dev->sdev);

	zpodd->powered_off = true;
	acpi_pm_set_device_wakeup(&dev->tdev, true);
}