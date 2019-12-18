#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  rq_flags; } ;
struct cdrom_info {int /*<<< orphan*/  disk; } ;
struct cdrom_device_info {TYPE_1__* handle; } ;
struct TYPE_5__ {int atapi_flags; int /*<<< orphan*/  queue; struct cdrom_info* driver_data; } ;
typedef  TYPE_1__ ide_drive_t ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {scalar_t__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATA_PRIV_MISC ; 
 int EIO ; 
 int IDE_AFLAG_DOOR_LOCKED ; 
 int /*<<< orphan*/  REQ_OP_DRV_IN ; 
 int /*<<< orphan*/  RQF_QUIET ; 
 int /*<<< orphan*/  blk_execute_rq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct request*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_put_request (struct request*) ; 
 int /*<<< orphan*/  ide_cd_lockdoor (TYPE_1__*,int) ; 
 TYPE_3__* ide_req (struct request*) ; 
 TYPE_2__* scsi_req (struct request*) ; 

int ide_cdrom_reset(struct cdrom_device_info *cdi)
{
	ide_drive_t *drive = cdi->handle;
	struct cdrom_info *cd = drive->driver_data;
	struct request *rq;
	int ret;

	rq = blk_get_request(drive->queue, REQ_OP_DRV_IN, 0);
	ide_req(rq)->type = ATA_PRIV_MISC;
	rq->rq_flags = RQF_QUIET;
	blk_execute_rq(drive->queue, cd->disk, rq, 0);
	ret = scsi_req(rq)->result ? -EIO : 0;
	blk_put_request(rq);
	/*
	 * A reset will unlock the door. If it was previously locked,
	 * lock it again.
	 */
	if (drive->atapi_flags & IDE_AFLAG_DOOR_LOCKED)
		(void)ide_cd_lockdoor(drive, 1);

	return ret;
}