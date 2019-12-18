#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct scsi_disk {int zeroing_mode; scalar_t__ ws16; } ;
struct scsi_device {scalar_t__ no_write_same; } ;
struct scsi_cmnd {struct scsi_device* device; struct request* request; } ;
struct request {int cmd_flags; int /*<<< orphan*/  rq_disk; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_TARGET ; 
 int REQ_NOUNMAP ; 
#define  SD_ZERO_WS10_UNMAP 129 
#define  SD_ZERO_WS16_UNMAP 128 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 struct scsi_disk* scsi_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_setup_write_same10_cmnd (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  sd_setup_write_same16_cmnd (struct scsi_cmnd*,int) ; 
 int sectors_to_logical (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t sd_setup_write_zeroes_cmnd(struct scsi_cmnd *cmd)
{
	struct request *rq = cmd->request;
	struct scsi_device *sdp = cmd->device;
	struct scsi_disk *sdkp = scsi_disk(rq->rq_disk);
	u64 lba = sectors_to_logical(sdp, blk_rq_pos(rq));
	u32 nr_blocks = sectors_to_logical(sdp, blk_rq_sectors(rq));

	if (!(rq->cmd_flags & REQ_NOUNMAP)) {
		switch (sdkp->zeroing_mode) {
		case SD_ZERO_WS16_UNMAP:
			return sd_setup_write_same16_cmnd(cmd, true);
		case SD_ZERO_WS10_UNMAP:
			return sd_setup_write_same10_cmnd(cmd, true);
		}
	}

	if (sdp->no_write_same)
		return BLK_STS_TARGET;

	if (sdkp->ws16 || lba > 0xffffffff || nr_blocks > 0xffff)
		return sd_setup_write_same16_cmnd(cmd, false);

	return sd_setup_write_same10_cmnd(cmd, false);
}