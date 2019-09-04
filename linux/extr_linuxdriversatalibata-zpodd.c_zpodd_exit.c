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
struct ata_device {int /*<<< orphan*/ * zpodd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_acpi_remove_pm_notifier (struct ata_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void zpodd_exit(struct ata_device *dev)
{
	ata_acpi_remove_pm_notifier(dev);
	kfree(dev->zpodd);
	dev->zpodd = NULL;
}