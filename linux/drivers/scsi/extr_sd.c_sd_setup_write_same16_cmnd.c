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
typedef  void* u64 ;
typedef  void* u32 ;
struct scsi_device {void* sector_size; } ;
struct scsi_cmnd {int cmd_len; int* cmnd; void* transfersize; int /*<<< orphan*/  allowed; struct request* request; struct scsi_device* device; } ;
struct TYPE_2__ {void* bv_len; scalar_t__ bv_offset; int /*<<< orphan*/  bv_page; } ;
struct request {int /*<<< orphan*/  timeout; int /*<<< orphan*/  rq_flags; TYPE_1__ special_vec; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RQF_SPECIAL_PAYLOAD ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 int /*<<< orphan*/  SD_WRITE_SAME_TIMEOUT ; 
 int WRITE_SAME_16 ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  blk_rq_sectors (struct request*) ; 
 int /*<<< orphan*/  clear_highpage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_be32 (void*,int*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (void*,int*) ; 
 int /*<<< orphan*/  scsi_init_io (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sd_page_pool ; 
 void* sectors_to_logical (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t sd_setup_write_same16_cmnd(struct scsi_cmnd *cmd,
		bool unmap)
{
	struct scsi_device *sdp = cmd->device;
	struct request *rq = cmd->request;
	u64 lba = sectors_to_logical(sdp, blk_rq_pos(rq));
	u32 nr_blocks = sectors_to_logical(sdp, blk_rq_sectors(rq));
	u32 data_len = sdp->sector_size;

	rq->special_vec.bv_page = mempool_alloc(sd_page_pool, GFP_ATOMIC);
	if (!rq->special_vec.bv_page)
		return BLK_STS_RESOURCE;
	clear_highpage(rq->special_vec.bv_page);
	rq->special_vec.bv_offset = 0;
	rq->special_vec.bv_len = data_len;
	rq->rq_flags |= RQF_SPECIAL_PAYLOAD;

	cmd->cmd_len = 16;
	cmd->cmnd[0] = WRITE_SAME_16;
	if (unmap)
		cmd->cmnd[1] = 0x8; /* UNMAP */
	put_unaligned_be64(lba, &cmd->cmnd[2]);
	put_unaligned_be32(nr_blocks, &cmd->cmnd[10]);

	cmd->allowed = SD_MAX_RETRIES;
	cmd->transfersize = data_len;
	rq->timeout = unmap ? SD_TIMEOUT : SD_WRITE_SAME_TIMEOUT;

	return scsi_init_io(cmd);
}