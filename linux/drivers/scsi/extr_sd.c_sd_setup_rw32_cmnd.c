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
struct scsi_cmnd {int* cmnd; int /*<<< orphan*/  cmd_len; } ;
typedef  unsigned int sector_t ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_OK ; 
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int READ_32 ; 
 int /*<<< orphan*/  SD_EXT_CDB_SIZE ; 
 int VARIABLE_LENGTH_CMD ; 
 int WRITE_32 ; 
 int* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_unaligned_be32 (unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  sd_cdb_pool ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t sd_setup_rw32_cmnd(struct scsi_cmnd *cmd, bool write,
				       sector_t lba, unsigned int nr_blocks,
				       unsigned char flags)
{
	cmd->cmnd = mempool_alloc(sd_cdb_pool, GFP_ATOMIC);
	if (unlikely(cmd->cmnd == NULL))
		return BLK_STS_RESOURCE;

	cmd->cmd_len = SD_EXT_CDB_SIZE;
	memset(cmd->cmnd, 0, cmd->cmd_len);

	cmd->cmnd[0]  = VARIABLE_LENGTH_CMD;
	cmd->cmnd[7]  = 0x18; /* Additional CDB len */
	cmd->cmnd[9]  = write ? WRITE_32 : READ_32;
	cmd->cmnd[10] = flags;
	put_unaligned_be64(lba, &cmd->cmnd[12]);
	put_unaligned_be32(lba, &cmd->cmnd[20]); /* Expected Indirect LBA */
	put_unaligned_be32(nr_blocks, &cmd->cmnd[28]);

	return BLK_STS_OK;
}