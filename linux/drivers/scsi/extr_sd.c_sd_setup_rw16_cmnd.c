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
struct scsi_cmnd {int cmd_len; unsigned char* cmnd; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 unsigned char READ_16 ; 
 unsigned char WRITE_16 ; 
 int /*<<< orphan*/  put_unaligned_be32 (unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,unsigned char*) ; 

__attribute__((used)) static blk_status_t sd_setup_rw16_cmnd(struct scsi_cmnd *cmd, bool write,
				       sector_t lba, unsigned int nr_blocks,
				       unsigned char flags)
{
	cmd->cmd_len  = 16;
	cmd->cmnd[0]  = write ? WRITE_16 : READ_16;
	cmd->cmnd[1]  = flags;
	cmd->cmnd[14] = 0;
	cmd->cmnd[15] = 0;
	put_unaligned_be64(lba, &cmd->cmnd[2]);
	put_unaligned_be32(nr_blocks, &cmd->cmnd[10]);

	return BLK_STS_OK;
}