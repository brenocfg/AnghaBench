#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct request {int /*<<< orphan*/  timeout; int /*<<< orphan*/ * cmd; } ;
struct ide_cmd {struct request* rq; int /*<<< orphan*/  tf_flags; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  ide_startstop_t ;
struct TYPE_10__ {int debug_mask; } ;
typedef  TYPE_1__ ide_drive_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_11__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATAPI_WAIT_PC ; 
#define  ATA_PRIV_MISC 134 
#define  ATA_PRIV_PC 133 
#define  ATA_PRIV_SENSE 132 
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BUG () ; 
 int IDE_DBG_RQ ; 
 int /*<<< orphan*/  IDE_TFLAG_WRITE ; 
#define  REQ_OP_DRV_IN 131 
#define  REQ_OP_DRV_OUT 130 
#define  REQ_OP_SCSI_IN 129 
#define  REQ_OP_SCSI_OUT 128 
 int /*<<< orphan*/  blk_dump_rq_flags (struct request*,char*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_is_passthrough (struct request*) ; 
 unsigned int blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  cdrom_do_block_pc (TYPE_1__*,struct request*) ; 
 int /*<<< orphan*/  cdrom_start_rw (TYPE_1__*,struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ide_debug_log (int,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ide_init_sg_cmd (struct ide_cmd*,scalar_t__) ; 
 int /*<<< orphan*/  ide_issue_pc (TYPE_1__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  ide_map_sg (TYPE_1__*,struct ide_cmd*) ; 
 int /*<<< orphan*/  ide_prep_sense (TYPE_1__*,struct request*) ; 
 TYPE_2__* ide_req (struct request*) ; 
 int /*<<< orphan*/  ide_stopped ; 
 int /*<<< orphan*/  memset (struct ide_cmd*,int /*<<< orphan*/ ,int) ; 
 int req_op (struct request*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 

__attribute__((used)) static ide_startstop_t ide_cd_do_request(ide_drive_t *drive, struct request *rq,
					sector_t block)
{
	struct ide_cmd cmd;
	int uptodate = 0;
	unsigned int nsectors;

	ide_debug_log(IDE_DBG_RQ, "cmd: 0x%x, block: %llu",
				  rq->cmd[0], (unsigned long long)block);

	if (drive->debug_mask & IDE_DBG_RQ)
		blk_dump_rq_flags(rq, "ide_cd_do_request");

	switch (req_op(rq)) {
	default:
		if (cdrom_start_rw(drive, rq) == ide_stopped)
			goto out_end;
		break;
	case REQ_OP_SCSI_IN:
	case REQ_OP_SCSI_OUT:
	handle_pc:
		if (!rq->timeout)
			rq->timeout = ATAPI_WAIT_PC;
		cdrom_do_block_pc(drive, rq);
		break;
	case REQ_OP_DRV_IN:
	case REQ_OP_DRV_OUT:
		switch (ide_req(rq)->type) {
		case ATA_PRIV_MISC:
			/* right now this can only be a reset... */
			uptodate = 1;
			goto out_end;
		case ATA_PRIV_SENSE:
		case ATA_PRIV_PC:
			goto handle_pc;
		default:
			BUG();
		}
	}

	/* prepare sense request for this command */
	ide_prep_sense(drive, rq);

	memset(&cmd, 0, sizeof(cmd));

	if (rq_data_dir(rq))
		cmd.tf_flags |= IDE_TFLAG_WRITE;

	cmd.rq = rq;

	if (!blk_rq_is_passthrough(rq) || blk_rq_bytes(rq)) {
		ide_init_sg_cmd(&cmd, blk_rq_bytes(rq));
		ide_map_sg(drive, &cmd);
	}

	return ide_issue_pc(drive, &cmd);
out_end:
	nsectors = blk_rq_sectors(rq);

	if (nsectors == 0)
		nsectors = 1;

	ide_complete_rq(drive, uptodate ? BLK_STS_OK : BLK_STS_IOERR, nsectors << 9);

	return ide_stopped;
}