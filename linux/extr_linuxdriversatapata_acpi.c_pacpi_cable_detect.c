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
struct pata_acpi {int* mask; } ;
struct ata_port {struct pata_acpi* private_data; } ;

/* Variables and functions */
 int ATA_CBL_PATA40 ; 
 int ATA_CBL_PATA80 ; 
 int ATA_SHIFT_UDMA ; 

__attribute__((used)) static int pacpi_cable_detect(struct ata_port *ap)
{
	struct pata_acpi *acpi = ap->private_data;

	if ((acpi->mask[0] | acpi->mask[1]) & (0xF8 << ATA_SHIFT_UDMA))
		return ATA_CBL_PATA80;
	else
		return ATA_CBL_PATA40;
}