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
struct ata_device {int flags; int /*<<< orphan*/  tdev; } ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 int ATA_DFLAG_ACPI_DISABLED ; 

acpi_handle ata_dev_acpi_handle(struct ata_device *dev)
{
	return dev->flags & ATA_DFLAG_ACPI_DISABLED ?
			NULL : ACPI_HANDLE(&dev->tdev);
}