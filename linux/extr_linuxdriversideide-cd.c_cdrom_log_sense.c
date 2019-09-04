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
struct request_sense {int sense_key; int asc; } ;
struct request {int rq_flags; } ;
struct TYPE_5__ {struct request_sense sense_data; } ;
typedef  TYPE_1__ ide_drive_t ;
struct TYPE_6__ {int /*<<< orphan*/ * cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPCMD_START_STOP_UNIT ; 
 int /*<<< orphan*/  IDE_DBG_SENSE ; 
#define  ILLEGAL_REQUEST 132 
#define  NOT_READY 131 
#define  NO_SENSE 130 
#define  RECOVERED_ERROR 129 
 int RQF_QUIET ; 
#define  UNIT_ATTENTION 128 
 int /*<<< orphan*/  cdrom_saw_media_change (TYPE_1__*) ; 
 int /*<<< orphan*/  ide_debug_log (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* scsi_req (struct request*) ; 

__attribute__((used)) static int cdrom_log_sense(ide_drive_t *drive, struct request *rq)
{
	struct request_sense *sense = &drive->sense_data;
	int log = 0;

	if (!sense || !rq || (rq->rq_flags & RQF_QUIET))
		return 0;

	ide_debug_log(IDE_DBG_SENSE, "sense_key: 0x%x", sense->sense_key);

	switch (sense->sense_key) {
	case NO_SENSE:
	case RECOVERED_ERROR:
		break;
	case NOT_READY:
		/*
		 * don't care about tray state messages for e.g. capacity
		 * commands or in-progress or becoming ready
		 */
		if (sense->asc == 0x3a || sense->asc == 0x04)
			break;
		log = 1;
		break;
	case ILLEGAL_REQUEST:
		/*
		 * don't log START_STOP unit with LoEj set, since we cannot
		 * reliably check if drive can auto-close
		 */
		if (scsi_req(rq)->cmd[0] == GPCMD_START_STOP_UNIT && sense->asc == 0x24)
			break;
		log = 1;
		break;
	case UNIT_ATTENTION:
		/*
		 * Make good and sure we've seen this potential media change.
		 * Some drives (i.e. Creative) fail to present the correct sense
		 * key in the error register.
		 */
		cdrom_saw_media_change(drive);
		break;
	default:
		log = 1;
		break;
	}
	return log;
}