#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct us_data {int last_sector_retries; scalar_t__ use_last_sector_hacks; } ;
struct scsi_disk {int capacity; } ;
struct scsi_cmnd {int* cmnd; scalar_t__ result; int /*<<< orphan*/  sense_buffer; TYPE_1__* request; } ;
struct gendisk {int dummy; } ;
typedef  int /*<<< orphan*/  record_not_found ;
struct TYPE_2__ {struct gendisk* rq_disk; } ;

/* Variables and functions */
#define  MEDIUM_ERROR 128 
 int READ_10 ; 
 scalar_t__ SAM_STAT_CHECK_CONDITION ; 
 scalar_t__ SAM_STAT_GOOD ; 
 int TEST_UNIT_READY ; 
 int WRITE_10 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 struct scsi_disk* scsi_disk (struct gendisk*) ; 
 scalar_t__ scsi_get_resid (struct scsi_cmnd*) ; 

__attribute__((used)) static void last_sector_hacks(struct us_data *us, struct scsi_cmnd *srb)
{
	struct gendisk *disk;
	struct scsi_disk *sdkp;
	u32 sector;

	/* To Report "Medium Error: Record Not Found */
	static unsigned char record_not_found[18] = {
		[0]	= 0x70,			/* current error */
		[2]	= MEDIUM_ERROR,		/* = 0x03 */
		[7]	= 0x0a,			/* additional length */
		[12]	= 0x14			/* Record Not Found */
	};

	/*
	 * If last-sector problems can't occur, whether because the
	 * capacity was already decremented or because the device is
	 * known to report the correct capacity, then we don't need
	 * to do anything.
	 */
	if (!us->use_last_sector_hacks)
		return;

	/* Was this command a READ(10) or a WRITE(10)? */
	if (srb->cmnd[0] != READ_10 && srb->cmnd[0] != WRITE_10)
		goto done;

	/* Did this command access the last sector? */
	sector = (srb->cmnd[2] << 24) | (srb->cmnd[3] << 16) |
			(srb->cmnd[4] << 8) | (srb->cmnd[5]);
	disk = srb->request->rq_disk;
	if (!disk)
		goto done;
	sdkp = scsi_disk(disk);
	if (!sdkp)
		goto done;
	if (sector + 1 != sdkp->capacity)
		goto done;

	if (srb->result == SAM_STAT_GOOD && scsi_get_resid(srb) == 0) {

		/*
		 * The command succeeded.  We know this device doesn't
		 * have the last-sector bug, so stop checking it.
		 */
		us->use_last_sector_hacks = 0;

	} else {
		/*
		 * The command failed.  Allow up to 3 retries in case this
		 * is some normal sort of failure.  After that, assume the
		 * capacity is wrong and we're trying to access the sector
		 * beyond the end.  Replace the result code and sense data
		 * with values that will cause the SCSI core to fail the
		 * command immediately, instead of going into an infinite
		 * (or even just a very long) retry loop.
		 */
		if (++us->last_sector_retries < 3)
			return;
		srb->result = SAM_STAT_CHECK_CONDITION;
		memcpy(srb->sense_buffer, record_not_found,
				sizeof(record_not_found));
	}

 done:
	/*
	 * Don't reset the retry counter for TEST UNIT READY commands,
	 * because they get issued after device resets which might be
	 * caused by a failed last-sector access.
	 */
	if (srb->cmnd[0] != TEST_UNIT_READY)
		us->last_sector_retries = 0;
}