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
struct ata_taskfile {int lbam; int lbah; } ;

/* Variables and functions */
 unsigned int ATA_DEV_ATA ; 
 unsigned int ATA_DEV_ATAPI ; 
 unsigned int ATA_DEV_PMP ; 
 unsigned int ATA_DEV_SEMB ; 
 unsigned int ATA_DEV_UNKNOWN ; 
 unsigned int ATA_DEV_ZAC ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 

unsigned int ata_dev_classify(const struct ata_taskfile *tf)
{
	/* Apple's open source Darwin code hints that some devices only
	 * put a proper signature into the LBA mid/high registers,
	 * So, we only check those.  It's sufficient for uniqueness.
	 *
	 * ATA/ATAPI-7 (d1532v1r1: Feb. 19, 2003) specified separate
	 * signatures for ATA and ATAPI devices attached on SerialATA,
	 * 0x3c/0xc3 and 0x69/0x96 respectively.  However, SerialATA
	 * spec has never mentioned about using different signatures
	 * for ATA/ATAPI devices.  Then, Serial ATA II: Port
	 * Multiplier specification began to use 0x69/0x96 to identify
	 * port multpliers and 0x3c/0xc3 to identify SEMB device.
	 * ATA/ATAPI-7 dropped descriptions about 0x3c/0xc3 and
	 * 0x69/0x96 shortly and described them as reserved for
	 * SerialATA.
	 *
	 * We follow the current spec and consider that 0x69/0x96
	 * identifies a port multiplier and 0x3c/0xc3 a SEMB device.
	 * Unfortunately, WDC WD1600JS-62MHB5 (a hard drive) reports
	 * SEMB signature.  This is worked around in
	 * ata_dev_read_id().
	 */
	if ((tf->lbam == 0) && (tf->lbah == 0)) {
		DPRINTK("found ATA device by sig\n");
		return ATA_DEV_ATA;
	}

	if ((tf->lbam == 0x14) && (tf->lbah == 0xeb)) {
		DPRINTK("found ATAPI device by sig\n");
		return ATA_DEV_ATAPI;
	}

	if ((tf->lbam == 0x69) && (tf->lbah == 0x96)) {
		DPRINTK("found PMP device by sig\n");
		return ATA_DEV_PMP;
	}

	if ((tf->lbam == 0x3c) && (tf->lbah == 0xc3)) {
		DPRINTK("found SEMB device by sig (could be ATA device)\n");
		return ATA_DEV_SEMB;
	}

	if ((tf->lbam == 0xcd) && (tf->lbah == 0xab)) {
		DPRINTK("found ZAC device by sig\n");
		return ATA_DEV_ZAC;
	}

	DPRINTK("unknown device\n");
	return ATA_DEV_UNKNOWN;
}