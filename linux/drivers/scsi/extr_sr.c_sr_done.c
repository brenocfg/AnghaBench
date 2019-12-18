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
struct scsi_cmnd {int result; int* sense_buffer; TYPE_2__* request; } ;
struct scsi_cd {int /*<<< orphan*/  disk; int /*<<< orphan*/  capacity; TYPE_1__* device; } ;
struct TYPE_4__ {int /*<<< orphan*/ * bio; int /*<<< orphan*/  rq_disk; } ;
struct TYPE_3__ {int sector_size; } ;

/* Variables and functions */
#define  ILLEGAL_REQUEST 131 
 int /*<<< orphan*/  KERN_INFO ; 
#define  MEDIUM_ERROR 130 
#define  RECOVERED_ERROR 129 
#define  VOLUME_OVERFLOW 128 
 int bio_sectors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_rq_pos (TYPE_2__*) ; 
 scalar_t__ driver_byte (int) ; 
 long get_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,int) ; 
 int scsi_bufflen (struct scsi_cmnd*) ; 
 struct scsi_cd* scsi_cd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int sr_done(struct scsi_cmnd *SCpnt)
{
	int result = SCpnt->result;
	int this_count = scsi_bufflen(SCpnt);
	int good_bytes = (result == 0 ? this_count : 0);
	int block_sectors = 0;
	long error_sector;
	struct scsi_cd *cd = scsi_cd(SCpnt->request->rq_disk);

#ifdef DEBUG
	scmd_printk(KERN_INFO, SCpnt, "done: %x\n", result);
#endif

	/*
	 * Handle MEDIUM ERRORs or VOLUME OVERFLOWs that indicate partial
	 * success.  Since this is a relatively rare error condition, no
	 * care is taken to avoid unnecessary additional work such as
	 * memcpy's that could be avoided.
	 */
	if (driver_byte(result) != 0 &&		/* An error occurred */
	    (SCpnt->sense_buffer[0] & 0x7f) == 0x70) { /* Sense current */
		switch (SCpnt->sense_buffer[2]) {
		case MEDIUM_ERROR:
		case VOLUME_OVERFLOW:
		case ILLEGAL_REQUEST:
			if (!(SCpnt->sense_buffer[0] & 0x90))
				break;
			error_sector = (SCpnt->sense_buffer[3] << 24) |
				(SCpnt->sense_buffer[4] << 16) |
				(SCpnt->sense_buffer[5] << 8) |
				SCpnt->sense_buffer[6];
			if (SCpnt->request->bio != NULL)
				block_sectors =
					bio_sectors(SCpnt->request->bio);
			if (block_sectors < 4)
				block_sectors = 4;
			if (cd->device->sector_size == 2048)
				error_sector <<= 2;
			error_sector &= ~(block_sectors - 1);
			good_bytes = (error_sector -
				      blk_rq_pos(SCpnt->request)) << 9;
			if (good_bytes < 0 || good_bytes >= this_count)
				good_bytes = 0;
			/*
			 * The SCSI specification allows for the value
			 * returned by READ CAPACITY to be up to 75 2K
			 * sectors past the last readable block.
			 * Therefore, if we hit a medium error within the
			 * last 75 2K sectors, we decrease the saved size
			 * value.
			 */
			if (error_sector < get_capacity(cd->disk) &&
			    cd->capacity - error_sector < 4 * 75)
				set_capacity(cd->disk, error_sector);
			break;

		case RECOVERED_ERROR:
			good_bytes = this_count;
			break;

		default:
			break;
		}
	}

	return good_bytes;
}