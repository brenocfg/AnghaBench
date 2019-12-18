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
typedef  int u8 ;
typedef  int u32 ;
struct bnx2x {int fw_seq; int /*<<< orphan*/  fw_mb_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw_mb_header; int /*<<< orphan*/  drv_mb_header; int /*<<< orphan*/  drv_mb_param; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_MCP ; 
 int BP_FW_MB_IDX (struct bnx2x*) ; 
 scalar_t__ CHIP_REV_IS_SLOW (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int FW_MSG_CODE_MASK ; 
 int FW_MSG_SEQ_NUMBER_MASK ; 
 int SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_fw_dump (struct bnx2x*) ; 
 TYPE_1__* func_mb ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

u32 bnx2x_fw_command(struct bnx2x *bp, u32 command, u32 param)
{
	int mb_idx = BP_FW_MB_IDX(bp);
	u32 seq;
	u32 rc = 0;
	u32 cnt = 1;
	u8 delay = CHIP_REV_IS_SLOW(bp) ? 100 : 10;

	mutex_lock(&bp->fw_mb_mutex);
	seq = ++bp->fw_seq;
	SHMEM_WR(bp, func_mb[mb_idx].drv_mb_param, param);
	SHMEM_WR(bp, func_mb[mb_idx].drv_mb_header, (command | seq));

	DP(BNX2X_MSG_MCP, "wrote command (%x) to FW MB param 0x%08x\n",
			(command | seq), param);

	do {
		/* let the FW do it's magic ... */
		msleep(delay);

		rc = SHMEM_RD(bp, func_mb[mb_idx].fw_mb_header);

		/* Give the FW up to 5 second (500*10ms) */
	} while ((seq != (rc & FW_MSG_SEQ_NUMBER_MASK)) && (cnt++ < 500));

	DP(BNX2X_MSG_MCP, "[after %d ms] read (%x) seq is (%x) from FW MB\n",
	   cnt*delay, rc, seq);

	/* is this a reply to our command? */
	if (seq == (rc & FW_MSG_SEQ_NUMBER_MASK))
		rc &= FW_MSG_CODE_MASK;
	else {
		/* FW BUG! */
		BNX2X_ERR("FW failed to respond!\n");
		bnx2x_fw_dump(bp);
		rc = 0;
	}
	mutex_unlock(&bp->fw_mb_mutex);

	return rc;
}