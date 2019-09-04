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
struct ata_acpi_gtm {int dummy; } ;
struct pata_acpi {struct ata_acpi_gtm gtm; } ;
struct ata_port {int /*<<< orphan*/  cbl; struct pata_acpi* private_data; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_CBL_PATA80 ; 
 int ATA_SHIFT_UDMA ; 
 int /*<<< orphan*/  ata_acpi_gtm (struct ata_port*,struct ata_acpi_gtm*) ; 
 unsigned int ata_acpi_gtm_xfermask (struct ata_device*,struct ata_acpi_gtm*) ; 

__attribute__((used)) static unsigned long pacpi_discover_modes(struct ata_port *ap, struct ata_device *adev)
{
	struct pata_acpi *acpi = ap->private_data;
	struct ata_acpi_gtm probe;
	unsigned int xfer_mask;

	probe = acpi->gtm;

	ata_acpi_gtm(ap, &probe);

	xfer_mask = ata_acpi_gtm_xfermask(adev, &probe);

	if (xfer_mask & (0xF8 << ATA_SHIFT_UDMA))
		ap->cbl = ATA_CBL_PATA80;

	return xfer_mask;
}