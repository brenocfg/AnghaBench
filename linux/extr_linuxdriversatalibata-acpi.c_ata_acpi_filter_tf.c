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
struct ata_taskfile {scalar_t__ command; scalar_t__ feature; scalar_t__ nsect; } ;
struct ata_device {int gtf_filter; } ;

/* Variables and functions */
 int ATA_ACPI_FILTER_DIPM ; 
 int ATA_ACPI_FILTER_FPDMA_AA ; 
 int ATA_ACPI_FILTER_FPDMA_OFFSET ; 
 int ATA_ACPI_FILTER_LOCK ; 
 int ATA_ACPI_FILTER_SETXFER ; 
 scalar_t__ ATA_CMD_CONF_OVERLAY ; 
 scalar_t__ ATA_CMD_READ_NATIVE_MAX ; 
 scalar_t__ ATA_CMD_SEC_FREEZE_LOCK ; 
 scalar_t__ ATA_CMD_SET_FEATURES ; 
 scalar_t__ ATA_CMD_SET_MAX ; 
 scalar_t__ ATA_DCO_FREEZE_LOCK ; 
 scalar_t__ ATA_SET_MAX_FREEZE_LOCK ; 
 scalar_t__ ATA_SET_MAX_LOCK ; 
 scalar_t__ SATA_DIPM ; 
 scalar_t__ SATA_FPDMA_AA ; 
 scalar_t__ SATA_FPDMA_IN_ORDER ; 
 scalar_t__ SATA_FPDMA_OFFSET ; 
 scalar_t__ SETFEATURES_SATA_ENABLE ; 
 scalar_t__ SETFEATURES_XFER ; 

__attribute__((used)) static int ata_acpi_filter_tf(struct ata_device *dev,
			      const struct ata_taskfile *tf,
			      const struct ata_taskfile *ptf)
{
	if (dev->gtf_filter & ATA_ACPI_FILTER_SETXFER) {
		/* libata doesn't use ACPI to configure transfer mode.
		 * It will only confuse device configuration.  Skip.
		 */
		if (tf->command == ATA_CMD_SET_FEATURES &&
		    tf->feature == SETFEATURES_XFER)
			return 1;
	}

	if (dev->gtf_filter & ATA_ACPI_FILTER_LOCK) {
		/* BIOS writers, sorry but we don't wanna lock
		 * features unless the user explicitly said so.
		 */

		/* DEVICE CONFIGURATION FREEZE LOCK */
		if (tf->command == ATA_CMD_CONF_OVERLAY &&
		    tf->feature == ATA_DCO_FREEZE_LOCK)
			return 1;

		/* SECURITY FREEZE LOCK */
		if (tf->command == ATA_CMD_SEC_FREEZE_LOCK)
			return 1;

		/* SET MAX LOCK and SET MAX FREEZE LOCK */
		if ((!ptf || ptf->command != ATA_CMD_READ_NATIVE_MAX) &&
		    tf->command == ATA_CMD_SET_MAX &&
		    (tf->feature == ATA_SET_MAX_LOCK ||
		     tf->feature == ATA_SET_MAX_FREEZE_LOCK))
			return 1;
	}

	if (tf->command == ATA_CMD_SET_FEATURES &&
	    tf->feature == SETFEATURES_SATA_ENABLE) {
		/* inhibit enabling DIPM */
		if (dev->gtf_filter & ATA_ACPI_FILTER_DIPM &&
		    tf->nsect == SATA_DIPM)
			return 1;

		/* inhibit FPDMA non-zero offset */
		if (dev->gtf_filter & ATA_ACPI_FILTER_FPDMA_OFFSET &&
		    (tf->nsect == SATA_FPDMA_OFFSET ||
		     tf->nsect == SATA_FPDMA_IN_ORDER))
			return 1;

		/* inhibit FPDMA auto activation */
		if (dev->gtf_filter & ATA_ACPI_FILTER_FPDMA_AA &&
		    tf->nsect == SATA_FPDMA_AA)
			return 1;
	}

	return 0;
}