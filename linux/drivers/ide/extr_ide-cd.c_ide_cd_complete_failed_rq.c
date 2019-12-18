#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  bio; } ;
typedef  int /*<<< orphan*/  ide_drive_t ;
struct TYPE_4__ {struct request* special; } ;
struct TYPE_3__ {int /*<<< orphan*/  sense_len; int /*<<< orphan*/  sense; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BUG () ; 
 void* bio_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  cdrom_analyze_sense_data (int /*<<< orphan*/ *,struct request*) ; 
 scalar_t__ ide_end_rq (int /*<<< orphan*/ *,struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ide_req (struct request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 TYPE_1__* scsi_req (struct request*) ; 

__attribute__((used)) static void ide_cd_complete_failed_rq(ide_drive_t *drive, struct request *rq)
{
	/*
	 * For ATA_PRIV_SENSE, "ide_req(rq)->special" points to the original
	 * failed request.  Also, the sense data should be read
	 * directly from rq which might be different from the original
	 * sense buffer if it got copied during mapping.
	 */
	struct request *failed = ide_req(rq)->special;
	void *sense = bio_data(rq->bio);

	if (failed) {
		/*
		 * Sense is always read into drive->sense_data, copy back to the
		 * original request.
		 */
		memcpy(scsi_req(failed)->sense, sense, 18);
		scsi_req(failed)->sense_len = scsi_req(rq)->sense_len;
		cdrom_analyze_sense_data(drive, failed);

		if (ide_end_rq(drive, failed, BLK_STS_IOERR, blk_rq_bytes(failed)))
			BUG();
	} else
		cdrom_analyze_sense_data(drive, NULL);
}