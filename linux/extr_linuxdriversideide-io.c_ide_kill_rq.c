#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct request {scalar_t__ rq_disk; } ;
struct TYPE_5__ {scalar_t__ media; int /*<<< orphan*/ * failed_pc; } ;
typedef  TYPE_1__ ide_drive_t ;
struct TYPE_6__ {int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  IDE_DRV_ERROR_GENERAL ; 
 scalar_t__ ata_misc_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 scalar_t__ blk_rq_is_passthrough (struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ide_floppy ; 
 scalar_t__ ide_tape ; 
 TYPE_2__* scsi_req (struct request*) ; 

void ide_kill_rq(ide_drive_t *drive, struct request *rq)
{
	u8 drv_req = ata_misc_request(rq) && rq->rq_disk;
	u8 media = drive->media;

	drive->failed_pc = NULL;

	if ((media == ide_floppy || media == ide_tape) && drv_req) {
		scsi_req(rq)->result = 0;
	} else {
		if (media == ide_tape)
			scsi_req(rq)->result = IDE_DRV_ERROR_GENERAL;
		else if (blk_rq_is_passthrough(rq) && scsi_req(rq)->result == 0)
			scsi_req(rq)->result = -EIO;
	}

	ide_complete_rq(drive, BLK_STS_IOERR, blk_rq_bytes(rq));
}