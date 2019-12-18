#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 scalar_t__ blk_rq_is_scsi (struct request*) ; 
 int ide_cdrom_prep_fs (int /*<<< orphan*/ ,struct request*) ; 
 int ide_cdrom_prep_pc (struct request*) ; 
 int /*<<< orphan*/  scsi_req (struct request*) ; 
 int /*<<< orphan*/  scsi_req_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ide_cdrom_prep_rq(ide_drive_t *drive, struct request *rq)
{
	if (!blk_rq_is_passthrough(rq)) {
		scsi_req_init(scsi_req(rq));

		return ide_cdrom_prep_fs(drive->queue, rq);
	} else if (blk_rq_is_scsi(rq))
		return ide_cdrom_prep_pc(rq);

	return true;
}