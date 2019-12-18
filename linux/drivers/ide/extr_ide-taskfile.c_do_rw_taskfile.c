#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ide_tp_ops {int /*<<< orphan*/  (* exec_command ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* tf_load ) (TYPE_4__*,struct ide_taskfile*,int) ;int /*<<< orphan*/  (* output_data ) (TYPE_4__*,struct ide_cmd*,int*,int) ;int /*<<< orphan*/  (* write_devctl ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct ide_taskfile {int data; int device; int /*<<< orphan*/  command; } ;
struct ide_dma_ops {int /*<<< orphan*/  (* dma_start ) (TYPE_4__*) ;int /*<<< orphan*/  dma_timer_expiry; } ;
struct TYPE_15__ {int tf; int hob; } ;
struct TYPE_16__ {TYPE_1__ out; } ;
struct ide_cmd {scalar_t__ protocol; int tf_flags; int ftf_flags; TYPE_2__ valid; struct ide_taskfile tf; struct ide_taskfile hob; } ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_17__ {int /*<<< orphan*/  expiry; struct ide_dma_ops* dma_ops; struct ide_tp_ops* tp_ops; struct ide_cmd cmd; } ;
typedef  TYPE_3__ ide_hwif_t ;
typedef  int /*<<< orphan*/  ide_handler_t ;
struct TYPE_18__ {scalar_t__ mult_count; int select; int /*<<< orphan*/  name; TYPE_3__* hwif; } ;
typedef  TYPE_4__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_DEVCTL_OBS ; 
#define  ATA_PROT_DMA 130 
#define  ATA_PROT_NODATA 129 
#define  ATA_PROT_PIO 128 
 int IDE_FTFLAG_FLAGGED ; 
 int IDE_FTFLAG_OUT_DATA ; 
 int IDE_FTFLAG_SET_IN_FLAGS ; 
 int IDE_TFLAG_DMA_PIO_FALLBACK ; 
 int IDE_TFLAG_LBA48 ; 
 int IDE_TFLAG_MULTI_PIO ; 
 int IDE_TFLAG_WRITE ; 
 int IDE_VALID_DEVICE ; 
 int WAIT_CMD ; 
 int WAIT_WORSTCASE ; 
 int /*<<< orphan*/ * ide_dma_intr ; 
 int /*<<< orphan*/  ide_dma_prepare (TYPE_4__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  ide_execute_command (TYPE_4__*,struct ide_cmd*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ide_started ; 
 int /*<<< orphan*/  ide_stopped ; 
 int /*<<< orphan*/  ide_tf_dump (int /*<<< orphan*/ ,struct ide_cmd*) ; 
 int /*<<< orphan*/  memcpy (struct ide_cmd*,struct ide_cmd*,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pre_task_out_intr (TYPE_4__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,struct ide_cmd*,int*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,struct ide_taskfile*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,struct ide_taskfile*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_4__*) ; 
 int /*<<< orphan*/ * task_no_data_intr ; 
 int /*<<< orphan*/ * task_pio_intr ; 

ide_startstop_t do_rw_taskfile(ide_drive_t *drive, struct ide_cmd *orig_cmd)
{
	ide_hwif_t *hwif = drive->hwif;
	struct ide_cmd *cmd = &hwif->cmd;
	struct ide_taskfile *tf = &cmd->tf;
	ide_handler_t *handler = NULL;
	const struct ide_tp_ops *tp_ops = hwif->tp_ops;
	const struct ide_dma_ops *dma_ops = hwif->dma_ops;

	if (orig_cmd->protocol == ATA_PROT_PIO &&
	    (orig_cmd->tf_flags & IDE_TFLAG_MULTI_PIO) &&
	    drive->mult_count == 0) {
		pr_err("%s: multimode not set!\n", drive->name);
		return ide_stopped;
	}

	if (orig_cmd->ftf_flags & IDE_FTFLAG_FLAGGED)
		orig_cmd->ftf_flags |= IDE_FTFLAG_SET_IN_FLAGS;

	memcpy(cmd, orig_cmd, sizeof(*cmd));

	if ((cmd->tf_flags & IDE_TFLAG_DMA_PIO_FALLBACK) == 0) {
		ide_tf_dump(drive->name, cmd);
		tp_ops->write_devctl(hwif, ATA_DEVCTL_OBS);

		if (cmd->ftf_flags & IDE_FTFLAG_OUT_DATA) {
			u8 data[2] = { cmd->tf.data, cmd->hob.data };

			tp_ops->output_data(drive, cmd, data, 2);
		}

		if (cmd->valid.out.tf & IDE_VALID_DEVICE) {
			u8 HIHI = (cmd->tf_flags & IDE_TFLAG_LBA48) ?
				  0xE0 : 0xEF;

			if (!(cmd->ftf_flags & IDE_FTFLAG_FLAGGED))
				cmd->tf.device &= HIHI;
			cmd->tf.device |= drive->select;
		}

		tp_ops->tf_load(drive, &cmd->hob, cmd->valid.out.hob);
		tp_ops->tf_load(drive, &cmd->tf,  cmd->valid.out.tf);
	}

	switch (cmd->protocol) {
	case ATA_PROT_PIO:
		if (cmd->tf_flags & IDE_TFLAG_WRITE) {
			tp_ops->exec_command(hwif, tf->command);
			ndelay(400);	/* FIXME */
			return pre_task_out_intr(drive, cmd);
		}
		handler = task_pio_intr;
		/* fall through */
	case ATA_PROT_NODATA:
		if (handler == NULL)
			handler = task_no_data_intr;
		ide_execute_command(drive, cmd, handler, WAIT_WORSTCASE);
		return ide_started;
	case ATA_PROT_DMA:
		if (ide_dma_prepare(drive, cmd))
			return ide_stopped;
		hwif->expiry = dma_ops->dma_timer_expiry;
		ide_execute_command(drive, cmd, ide_dma_intr, 2 * WAIT_CMD);
		dma_ops->dma_start(drive);
		/* fall through */
	default:
		return ide_started;
	}
}