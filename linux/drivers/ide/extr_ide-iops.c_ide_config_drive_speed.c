#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/  tf ;
struct ide_tp_ops {int /*<<< orphan*/  (* write_devctl ) (TYPE_2__*,int) ;int /*<<< orphan*/  (* exec_command ) (TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* tf_load ) (TYPE_3__*,struct ide_taskfile*,int) ;int /*<<< orphan*/  (* dev_select ) (TYPE_3__*) ;} ;
struct ide_taskfile {int nsect; int /*<<< orphan*/  feature; } ;
struct TYPE_17__ {TYPE_1__* dma_ops; struct ide_tp_ops* tp_ops; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_18__ {int* id; int dev_flags; int init_speed; int current_speed; int /*<<< orphan*/  ready_stat; TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* dma_host_set ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 int ATA_BUSY ; 
 int /*<<< orphan*/  ATA_CMD_SET_FEATURES ; 
 int ATA_DEVCTL_OBS ; 
 int ATA_DRQ ; 
 int ATA_ERR ; 
 size_t ATA_ID_CFA_MODES ; 
 size_t ATA_ID_MWDMA_MODES ; 
 size_t ATA_ID_SWDMA_MODES ; 
 size_t ATA_ID_UDMA_MODES ; 
 int ATA_NIEN ; 
 int IDE_DFLAG_NIEN_QUIRK ; 
 int IDE_DFLAG_USING_DMA ; 
 int IDE_VALID_FEATURE ; 
 int IDE_VALID_NSECT ; 
 int /*<<< orphan*/  SELECT_MASK (TYPE_3__*,int) ; 
 int /*<<< orphan*/  SETFEATURES_XFER ; 
 int /*<<< orphan*/  WAIT_CMD ; 
 int XFER_MW_DMA_0 ; 
 int XFER_MW_DMA_2 ; 
 int XFER_MW_DMA_3 ; 
 int XFER_PIO_0 ; 
 int XFER_PIO_4 ; 
 int XFER_PIO_5 ; 
 int XFER_SW_DMA_0 ; 
 int XFER_UDMA_0 ; 
 int __ide_wait_stat (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ ata_id_has_iordy (int*) ; 
 scalar_t__ ata_id_is_cfa (int*) ; 
 int /*<<< orphan*/  ide_dma_off_quietly (TYPE_3__*) ; 
 int /*<<< orphan*/  ide_dump_status (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  memset (struct ide_taskfile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,struct ide_taskfile*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int ide_config_drive_speed(ide_drive_t *drive, u8 speed)
{
	ide_hwif_t *hwif = drive->hwif;
	const struct ide_tp_ops *tp_ops = hwif->tp_ops;
	struct ide_taskfile tf;
	u16 *id = drive->id, i;
	int error = 0;
	u8 stat;

#ifdef CONFIG_BLK_DEV_IDEDMA
	if (hwif->dma_ops)	/* check if host supports DMA */
		hwif->dma_ops->dma_host_set(drive, 0);
#endif

	/* Skip setting PIO flow-control modes on pre-EIDE drives */
	if ((speed & 0xf8) == XFER_PIO_0 && ata_id_has_iordy(drive->id) == 0)
		goto skip;

	/*
	 * Don't use ide_wait_cmd here - it will
	 * attempt to set_geometry and recalibrate,
	 * but for some reason these don't work at
	 * this point (lost interrupt).
	 */

	udelay(1);
	tp_ops->dev_select(drive);
	SELECT_MASK(drive, 1);
	udelay(1);
	tp_ops->write_devctl(hwif, ATA_NIEN | ATA_DEVCTL_OBS);

	memset(&tf, 0, sizeof(tf));
	tf.feature = SETFEATURES_XFER;
	tf.nsect   = speed;

	tp_ops->tf_load(drive, &tf, IDE_VALID_FEATURE | IDE_VALID_NSECT);

	tp_ops->exec_command(hwif, ATA_CMD_SET_FEATURES);

	if (drive->dev_flags & IDE_DFLAG_NIEN_QUIRK)
		tp_ops->write_devctl(hwif, ATA_DEVCTL_OBS);

	error = __ide_wait_stat(drive, drive->ready_stat,
				ATA_BUSY | ATA_DRQ | ATA_ERR,
				WAIT_CMD, &stat);

	SELECT_MASK(drive, 0);

	if (error) {
		(void) ide_dump_status(drive, "set_drive_speed_status", stat);
		return error;
	}

	if (speed >= XFER_SW_DMA_0) {
		id[ATA_ID_UDMA_MODES]  &= ~0xFF00;
		id[ATA_ID_MWDMA_MODES] &= ~0x0700;
		id[ATA_ID_SWDMA_MODES] &= ~0x0700;
		if (ata_id_is_cfa(id))
			id[ATA_ID_CFA_MODES] &= ~0x0E00;
	} else	if (ata_id_is_cfa(id))
		id[ATA_ID_CFA_MODES] &= ~0x01C0;

 skip:
#ifdef CONFIG_BLK_DEV_IDEDMA
	if (speed >= XFER_SW_DMA_0 && (drive->dev_flags & IDE_DFLAG_USING_DMA))
		hwif->dma_ops->dma_host_set(drive, 1);
	else if (hwif->dma_ops)	/* check if host supports DMA */
		ide_dma_off_quietly(drive);
#endif

	if (speed >= XFER_UDMA_0) {
		i = 1 << (speed - XFER_UDMA_0);
		id[ATA_ID_UDMA_MODES] |= (i << 8 | i);
	} else if (ata_id_is_cfa(id) && speed >= XFER_MW_DMA_3) {
		i = speed - XFER_MW_DMA_2;
		id[ATA_ID_CFA_MODES] |= i << 9;
	} else if (speed >= XFER_MW_DMA_0) {
		i = 1 << (speed - XFER_MW_DMA_0);
		id[ATA_ID_MWDMA_MODES] |= (i << 8 | i);
	} else if (speed >= XFER_SW_DMA_0) {
		i = 1 << (speed - XFER_SW_DMA_0);
		id[ATA_ID_SWDMA_MODES] |= (i << 8 | i);
	} else if (ata_id_is_cfa(id) && speed >= XFER_PIO_5) {
		i = speed - XFER_PIO_4;
		id[ATA_ID_CFA_MODES] |= i << 6;
	}

	if (!drive->init_speed)
		drive->init_speed = speed;
	drive->current_speed = speed;
	return error;
}