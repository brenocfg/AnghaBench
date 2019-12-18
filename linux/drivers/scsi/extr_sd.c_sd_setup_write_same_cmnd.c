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
typedef  int u64 ;
typedef  int u32 ;
struct scsi_disk {scalar_t__ ws16; TYPE_1__* device; } ;
struct scsi_device {scalar_t__ sector_size; } ;
struct scsi_cmnd {int cmd_len; scalar_t__ transfersize; int /*<<< orphan*/  allowed; int /*<<< orphan*/ * cmnd; struct scsi_device* device; struct request* request; } ;
struct request {scalar_t__ __data_len; int /*<<< orphan*/  timeout; struct bio* bio; int /*<<< orphan*/  rq_disk; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_4__ {scalar_t__ bv_len; } ;
struct TYPE_3__ {scalar_t__ no_write_same; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_TARGET ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SD_WRITE_SAME_TIMEOUT ; 
 int /*<<< orphan*/  WRITE_SAME ; 
 int /*<<< orphan*/  WRITE_SAME_16 ; 
 TYPE_2__ bio_iovec (struct bio*) ; 
 scalar_t__ bio_offset (struct bio*) ; 
 scalar_t__ blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int,int /*<<< orphan*/ *) ; 
 struct scsi_disk* scsi_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_init_io (struct scsi_cmnd*) ; 
 int sectors_to_logical (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t sd_setup_write_same_cmnd(struct scsi_cmnd *cmd)
{
	struct request *rq = cmd->request;
	struct scsi_device *sdp = cmd->device;
	struct scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	struct bio *bio = rq->bio;
	u64 lba = sectors_to_logical(sdp, blk_rq_pos(rq));
	u32 nr_blocks = sectors_to_logical(sdp, blk_rq_sectors(rq));
	blk_status_t ret;

	if (sdkp->device->no_write_same)
		return BLK_STS_TARGET;

	BUG_ON(bio_offset(bio) || bio_iovec(bio).bv_len != sdp->sector_size);

	rq->timeout = SD_WRITE_SAME_TIMEOUT;

	if (sdkp->ws16 || lba > 0xffffffff || nr_blocks > 0xffff) {
		cmd->cmd_len = 16;
		cmd->cmnd[0] = WRITE_SAME_16;
		put_unaligned_be64(lba, &cmd->cmnd[2]);
		put_unaligned_be32(nr_blocks, &cmd->cmnd[10]);
	} else {
		cmd->cmd_len = 10;
		cmd->cmnd[0] = WRITE_SAME;
		put_unaligned_be32(lba, &cmd->cmnd[2]);
		put_unaligned_be16(nr_blocks, &cmd->cmnd[7]);
	}

	cmd->transfersize = sdp->sector_size;
	cmd->allowed = SD_MAX_RETRIES;

	/*
	 * For WRITE SAME the data transferred via the DATA OUT buffer is
	 * different from the amount of data actually written to the target.
	 *
	 * We set up __data_len to the amount of data transferred via the
	 * DATA OUT buffer so that blk_rq_map_sg sets up the proper S/G list
	 * to transfer a single sector of data first, but then reset it to
	 * the amount of data to be written right after so that the I/O path
	 * knows how much to actually write.
	 */
	rq->__data_len = sdp->sector_size;
	ret = scsi_init_io(cmd);
	rq->__data_len = blk_rq_bytes(rq);

	return ret;
}