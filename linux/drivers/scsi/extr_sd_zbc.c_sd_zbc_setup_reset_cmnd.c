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
struct scsi_disk {TYPE_1__* device; } ;
struct scsi_cmnd {int cmd_len; int* cmnd; scalar_t__ allowed; scalar_t__ transfersize; int /*<<< orphan*/  sc_data_direction; struct request* request; } ;
struct request {int /*<<< orphan*/  timeout; int /*<<< orphan*/  rq_disk; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {scalar_t__ changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 int ZBC_OUT ; 
 int ZO_RESET_WRITE_POINTER ; 
 int blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int,int*) ; 
 struct scsi_disk* scsi_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_is_zoned (struct scsi_disk*) ; 
 int sd_zbc_zone_sectors (struct scsi_disk*) ; 
 int sectors_to_logical (TYPE_1__*,int) ; 

blk_status_t sd_zbc_setup_reset_cmnd(struct scsi_cmnd *cmd, bool all)
{
	struct request *rq = cmd->request;
	struct scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	sector_t sector = blk_rq_pos(rq);
	sector_t block = sectors_to_logical(sdkp->device, sector);

	if (!sd_is_zoned(sdkp))
		/* Not a zoned device */
		return BLK_STS_IOERR;

	if (sdkp->device->changed)
		return BLK_STS_IOERR;

	if (sector & (sd_zbc_zone_sectors(sdkp) - 1))
		/* Unaligned request */
		return BLK_STS_IOERR;

	cmd->cmd_len = 16;
	memset(cmd->cmnd, 0, cmd->cmd_len);
	cmd->cmnd[0] = ZBC_OUT;
	cmd->cmnd[1] = ZO_RESET_WRITE_POINTER;
	if (all)
		cmd->cmnd[14] = 0x1;
	else
		put_unaligned_be64(block, &cmd->cmnd[2]);

	rq->timeout = SD_TIMEOUT;
	cmd->sc_data_direction = DMA_NONE;
	cmd->transfersize = 0;
	cmd->allowed = 0;

	return BLK_STS_OK;
}