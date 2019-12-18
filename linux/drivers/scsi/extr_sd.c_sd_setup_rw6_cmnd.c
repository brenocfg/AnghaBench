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
struct scsi_cmnd {int cmd_len; int* cmnd; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int READ_6 ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int WRITE_6 ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,struct scsi_cmnd*,char*) ; 
 scalar_t__ unlikely (unsigned char) ; 

__attribute__((used)) static blk_status_t sd_setup_rw6_cmnd(struct scsi_cmnd *cmd, bool write,
				      sector_t lba, unsigned int nr_blocks,
				      unsigned char flags)
{
	/* Avoid that 0 blocks gets translated into 256 blocks. */
	if (WARN_ON_ONCE(nr_blocks == 0))
		return BLK_STS_IOERR;

	if (unlikely(flags & 0x8)) {
		/*
		 * This happens only if this drive failed 10byte rw
		 * command with ILLEGAL_REQUEST during operation and
		 * thus turned off use_10_for_rw.
		 */
		scmd_printk(KERN_ERR, cmd, "FUA write on READ/WRITE(6) drive\n");
		return BLK_STS_IOERR;
	}

	cmd->cmd_len = 6;
	cmd->cmnd[0] = write ? WRITE_6 : READ_6;
	cmd->cmnd[1] = (lba >> 16) & 0x1f;
	cmd->cmnd[2] = (lba >> 8) & 0xff;
	cmd->cmnd[3] = lba & 0xff;
	cmd->cmnd[4] = nr_blocks;
	cmd->cmnd[5] = 0;

	return BLK_STS_OK;
}