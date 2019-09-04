#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct ide_tp_ops {int /*<<< orphan*/  (* tf_read ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_devctl ) (TYPE_3__*,int) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  hob; int /*<<< orphan*/  tf; } ;
struct TYPE_11__ {TYPE_1__ in; } ;
struct ide_cmd {int tf_flags; TYPE_2__ valid; int /*<<< orphan*/  hob; int /*<<< orphan*/  tf; } ;
struct TYPE_12__ {struct ide_tp_ops* tp_ops; } ;
typedef  TYPE_3__ ide_hwif_t ;
struct TYPE_13__ {TYPE_3__* hwif; } ;
typedef  TYPE_4__ ide_drive_t ;

/* Variables and functions */
 int ATA_DEVCTL_OBS ; 
 int ATA_HOB ; 
 int IDE_TFLAG_LBA48 ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ide_tf_readback(ide_drive_t *drive, struct ide_cmd *cmd)
{
	ide_hwif_t *hwif = drive->hwif;
	const struct ide_tp_ops *tp_ops = hwif->tp_ops;

	/* Be sure we're looking at the low order bytes */
	tp_ops->write_devctl(hwif, ATA_DEVCTL_OBS);

	tp_ops->tf_read(drive, &cmd->tf, cmd->valid.in.tf);

	if (cmd->tf_flags & IDE_TFLAG_LBA48) {
		tp_ops->write_devctl(hwif, ATA_HOB | ATA_DEVCTL_OBS);

		tp_ops->tf_read(drive, &cmd->hob, cmd->valid.in.hob);
	}
}