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
struct scsi_cmnd {struct request* request; } ;
struct request {int /*<<< orphan*/  rq_disk; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  provisioning_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_NOTSUPP ; 
 int /*<<< orphan*/  BLK_STS_TARGET ; 
#define  REQ_OP_DISCARD 139 
#define  REQ_OP_FLUSH 138 
#define  REQ_OP_READ 137 
#define  REQ_OP_WRITE 136 
#define  REQ_OP_WRITE_SAME 135 
#define  REQ_OP_WRITE_ZEROES 134 
#define  REQ_OP_ZONE_RESET 133 
#define  REQ_OP_ZONE_RESET_ALL 132 
#define  SD_LBP_UNMAP 131 
#define  SD_LBP_WS10 130 
#define  SD_LBP_WS16 129 
#define  SD_LBP_ZERO 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int req_op (struct request*) ; 
 TYPE_1__* scsi_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_setup_flush_cmnd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sd_setup_read_write_cmnd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sd_setup_unmap_cmnd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sd_setup_write_same10_cmnd (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  sd_setup_write_same16_cmnd (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  sd_setup_write_same_cmnd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sd_setup_write_zeroes_cmnd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sd_zbc_setup_reset_cmnd (struct scsi_cmnd*,int) ; 

__attribute__((used)) static blk_status_t sd_init_command(struct scsi_cmnd *cmd)
{
	struct request *rq = cmd->request;

	switch (req_op(rq)) {
	case REQ_OP_DISCARD:
		switch (scsi_disk(rq->rq_disk)->provisioning_mode) {
		case SD_LBP_UNMAP:
			return sd_setup_unmap_cmnd(cmd);
		case SD_LBP_WS16:
			return sd_setup_write_same16_cmnd(cmd, true);
		case SD_LBP_WS10:
			return sd_setup_write_same10_cmnd(cmd, true);
		case SD_LBP_ZERO:
			return sd_setup_write_same10_cmnd(cmd, false);
		default:
			return BLK_STS_TARGET;
		}
	case REQ_OP_WRITE_ZEROES:
		return sd_setup_write_zeroes_cmnd(cmd);
	case REQ_OP_WRITE_SAME:
		return sd_setup_write_same_cmnd(cmd);
	case REQ_OP_FLUSH:
		return sd_setup_flush_cmnd(cmd);
	case REQ_OP_READ:
	case REQ_OP_WRITE:
		return sd_setup_read_write_cmnd(cmd);
	case REQ_OP_ZONE_RESET:
		return sd_zbc_setup_reset_cmnd(cmd, false);
	case REQ_OP_ZONE_RESET_ALL:
		return sd_zbc_setup_reset_cmnd(cmd, true);
	default:
		WARN_ON_ONCE(1);
		return BLK_STS_NOTSUPP;
	}
}