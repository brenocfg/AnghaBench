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
struct request {int dummy; } ;
struct TYPE_7__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
typedef  scalar_t__ blk_status_t ;
struct TYPE_8__ {scalar_t__* cmd; int /*<<< orphan*/  result; } ;
struct TYPE_6__ {struct request* rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ REQ_DRIVE_RESET ; 
 scalar_t__ ata_misc_request (struct request*) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* scsi_req (struct request*) ; 

__attribute__((used)) static inline void ide_complete_drive_reset(ide_drive_t *drive, blk_status_t err)
{
	struct request *rq = drive->hwif->rq;

	if (rq && ata_misc_request(rq) &&
	    scsi_req(rq)->cmd[0] == REQ_DRIVE_RESET) {
		if (err <= 0 && scsi_req(rq)->result == 0)
			scsi_req(rq)->result = -EIO;
		ide_complete_rq(drive, err, blk_rq_bytes(rq));
	}
}