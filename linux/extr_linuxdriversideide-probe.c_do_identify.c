#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {TYPE_1__* tp_ops; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev_flags; TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* input_data ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ATA_CMD_ID_ATAPI ; 
 size_t ATA_ID_FW_REV ; 
 int ATA_ID_FW_REV_LEN ; 
 size_t ATA_ID_PROD ; 
 int ATA_ID_PROD_LEN ; 
 size_t ATA_ID_SERNO ; 
 int ATA_ID_SERNO_LEN ; 
 int /*<<< orphan*/  IDE_DFLAG_ID_READ ; 
 int /*<<< orphan*/  IDE_DFLAG_PRESENT ; 
 int /*<<< orphan*/  SECTOR_SIZE ; 
 int /*<<< orphan*/  ide_fix_driveid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ide_fixstring (char*,int,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ strstr (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_identify(ide_drive_t *drive, u8 cmd, u16 *id)
{
	ide_hwif_t *hwif = drive->hwif;
	char *m = (char *)&id[ATA_ID_PROD];
	unsigned long flags;
	int bswap = 1;

	/* local CPU only; some systems need this */
	local_irq_save(flags);
	/* read 512 bytes of id info */
	hwif->tp_ops->input_data(drive, NULL, id, SECTOR_SIZE);
	local_irq_restore(flags);

	drive->dev_flags |= IDE_DFLAG_ID_READ;
#ifdef DEBUG
	printk(KERN_INFO "%s: dumping identify data\n", drive->name);
	ide_dump_identify((u8 *)id);
#endif
	ide_fix_driveid(id);

	/*
	 *  ATA_CMD_ID_ATA returns little-endian info,
	 *  ATA_CMD_ID_ATAPI *usually* returns little-endian info.
	 */
	if (cmd == ATA_CMD_ID_ATAPI) {
		if ((m[0] == 'N' && m[1] == 'E') ||  /* NEC */
		    (m[0] == 'F' && m[1] == 'X') ||  /* Mitsumi */
		    (m[0] == 'P' && m[1] == 'i'))    /* Pioneer */
			/* Vertos drives may still be weird */
			bswap ^= 1;
	}

	ide_fixstring(m, ATA_ID_PROD_LEN, bswap);
	ide_fixstring((char *)&id[ATA_ID_FW_REV], ATA_ID_FW_REV_LEN, bswap);
	ide_fixstring((char *)&id[ATA_ID_SERNO], ATA_ID_SERNO_LEN, bswap);

	/* we depend on this a lot! */
	m[ATA_ID_PROD_LEN - 1] = '\0';

	if (strstr(m, "E X A B Y T E N E S T"))
		drive->dev_flags &= ~IDE_DFLAG_PRESENT;
	else
		drive->dev_flags |= IDE_DFLAG_PRESENT;
}