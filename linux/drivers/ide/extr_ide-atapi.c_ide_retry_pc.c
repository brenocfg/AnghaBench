#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct ide_atapi_pc {int /*<<< orphan*/  c; } ;
struct TYPE_10__ {scalar_t__ media; TYPE_1__* hwif; int /*<<< orphan*/  atapi_flags; struct ide_atapi_pc request_sense_pc; struct request* sense_rq; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_11__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_9__ {struct request* rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  IDE_AFLAG_IGNORE_DSC ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 
 scalar_t__ ide_queue_sense_rq (TYPE_2__*,struct ide_atapi_pc*) ; 
 int /*<<< orphan*/  ide_read_error (TYPE_2__*) ; 
 int /*<<< orphan*/  ide_requeue_and_plug (TYPE_2__*,struct request*) ; 
 scalar_t__ ide_tape ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* scsi_req (struct request*) ; 

void ide_retry_pc(ide_drive_t *drive)
{
	struct request *failed_rq = drive->hwif->rq;
	struct request *sense_rq = drive->sense_rq;
	struct ide_atapi_pc *pc = &drive->request_sense_pc;

	(void)ide_read_error(drive);

	/* init pc from sense_rq */
	ide_init_pc(pc);
	memcpy(pc->c, scsi_req(sense_rq)->cmd, 12);

	if (drive->media == ide_tape)
		drive->atapi_flags |= IDE_AFLAG_IGNORE_DSC;

	/*
	 * Push back the failed request and put request sense on top
	 * of it.  The failed command will be retried after sense data
	 * is acquired.
	 */
	drive->hwif->rq = NULL;
	ide_requeue_and_plug(drive, failed_rq);
	if (ide_queue_sense_rq(drive, pc))
		ide_complete_rq(drive, BLK_STS_IOERR, blk_rq_bytes(failed_rq));
}