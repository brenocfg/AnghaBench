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
struct scsi_sense_hdr {int sense_key; int asc; } ;
struct scsi_disk {TYPE_2__* device; scalar_t__ medium_access_timed_out; } ;
struct scsi_cmnd {int result; int* cmnd; int /*<<< orphan*/  sense_buffer; struct request* request; TYPE_1__* device; } ;
struct request {int /*<<< orphan*/  rq_flags; int /*<<< orphan*/  rq_disk; } ;
struct TYPE_4__ {int no_write_same; } ;
struct TYPE_3__ {unsigned int sector_size; } ;

/* Variables and functions */
#define  ABORTED_COMMAND 141 
 scalar_t__ DRIVER_SENSE ; 
#define  HARDWARE_ERROR 140 
#define  ILLEGAL_REQUEST 139 
 int /*<<< orphan*/  KERN_INFO ; 
#define  MEDIUM_ERROR 138 
#define  NO_SENSE 137 
#define  RECOVERED_ERROR 136 
#define  REQ_OP_DISCARD 135 
#define  REQ_OP_WRITE_SAME 134 
#define  REQ_OP_WRITE_ZEROES 133 
#define  REQ_OP_ZONE_RESET 132 
#define  REQ_OP_ZONE_RESET_ALL 131 
 int /*<<< orphan*/  RQF_QUIET ; 
 int /*<<< orphan*/  SCSI_LOG_HLCOMPLETE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  SD_LBP_DISABLE ; 
#define  UNMAP 130 
#define  WRITE_SAME 129 
#define  WRITE_SAME_16 128 
 unsigned int blk_rq_bytes (struct request*) ; 
 scalar_t__ driver_byte (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int req_op (struct request*) ; 
 int /*<<< orphan*/  round_up (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*,unsigned int,unsigned int) ; 
 unsigned int scsi_bufflen (struct scsi_cmnd*) ; 
 int scsi_command_normalize_sense (struct scsi_cmnd*,struct scsi_sense_hdr*) ; 
 struct scsi_disk* scsi_disk (int /*<<< orphan*/ ) ; 
 unsigned int scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_print_command (struct scsi_cmnd*) ; 
 int scsi_sense_is_deferred (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,unsigned int) ; 
 unsigned int sd_completed_bytes (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sd_config_discard (struct scsi_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_config_write_same (struct scsi_disk*) ; 
 scalar_t__ sd_is_zoned (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  sd_zbc_complete (struct scsi_cmnd*,unsigned int,struct scsi_sense_hdr*) ; 

__attribute__((used)) static int sd_done(struct scsi_cmnd *SCpnt)
{
	int result = SCpnt->result;
	unsigned int good_bytes = result ? 0 : scsi_bufflen(SCpnt);
	unsigned int sector_size = SCpnt->device->sector_size;
	unsigned int resid;
	struct scsi_sense_hdr sshdr;
	struct scsi_disk *sdkp = scsi_disk(SCpnt->request->rq_disk);
	struct request *req = SCpnt->request;
	int sense_valid = 0;
	int sense_deferred = 0;

	switch (req_op(req)) {
	case REQ_OP_DISCARD:
	case REQ_OP_WRITE_ZEROES:
	case REQ_OP_WRITE_SAME:
	case REQ_OP_ZONE_RESET:
	case REQ_OP_ZONE_RESET_ALL:
		if (!result) {
			good_bytes = blk_rq_bytes(req);
			scsi_set_resid(SCpnt, 0);
		} else {
			good_bytes = 0;
			scsi_set_resid(SCpnt, blk_rq_bytes(req));
		}
		break;
	default:
		/*
		 * In case of bogus fw or device, we could end up having
		 * an unaligned partial completion. Check this here and force
		 * alignment.
		 */
		resid = scsi_get_resid(SCpnt);
		if (resid & (sector_size - 1)) {
			sd_printk(KERN_INFO, sdkp,
				"Unaligned partial completion (resid=%u, sector_sz=%u)\n",
				resid, sector_size);
			scsi_print_command(SCpnt);
			resid = min(scsi_bufflen(SCpnt),
				    round_up(resid, sector_size));
			scsi_set_resid(SCpnt, resid);
		}
	}

	if (result) {
		sense_valid = scsi_command_normalize_sense(SCpnt, &sshdr);
		if (sense_valid)
			sense_deferred = scsi_sense_is_deferred(&sshdr);
	}
	sdkp->medium_access_timed_out = 0;

	if (driver_byte(result) != DRIVER_SENSE &&
	    (!sense_valid || sense_deferred))
		goto out;

	switch (sshdr.sense_key) {
	case HARDWARE_ERROR:
	case MEDIUM_ERROR:
		good_bytes = sd_completed_bytes(SCpnt);
		break;
	case RECOVERED_ERROR:
		good_bytes = scsi_bufflen(SCpnt);
		break;
	case NO_SENSE:
		/* This indicates a false check condition, so ignore it.  An
		 * unknown amount of data was transferred so treat it as an
		 * error.
		 */
		SCpnt->result = 0;
		memset(SCpnt->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		break;
	case ABORTED_COMMAND:
		if (sshdr.asc == 0x10)  /* DIF: Target detected corruption */
			good_bytes = sd_completed_bytes(SCpnt);
		break;
	case ILLEGAL_REQUEST:
		switch (sshdr.asc) {
		case 0x10:	/* DIX: Host detected corruption */
			good_bytes = sd_completed_bytes(SCpnt);
			break;
		case 0x20:	/* INVALID COMMAND OPCODE */
		case 0x24:	/* INVALID FIELD IN CDB */
			switch (SCpnt->cmnd[0]) {
			case UNMAP:
				sd_config_discard(sdkp, SD_LBP_DISABLE);
				break;
			case WRITE_SAME_16:
			case WRITE_SAME:
				if (SCpnt->cmnd[1] & 8) { /* UNMAP */
					sd_config_discard(sdkp, SD_LBP_DISABLE);
				} else {
					sdkp->device->no_write_same = 1;
					sd_config_write_same(sdkp);
					req->rq_flags |= RQF_QUIET;
				}
				break;
			}
		}
		break;
	default:
		break;
	}

 out:
	if (sd_is_zoned(sdkp))
		sd_zbc_complete(SCpnt, good_bytes, &sshdr);

	SCSI_LOG_HLCOMPLETE(1, scmd_printk(KERN_INFO, SCpnt,
					   "sd_done: completed %d of %d bytes\n",
					   good_bytes, scsi_bufflen(SCpnt)));

	return good_bytes;
}