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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct megasas_instance {scalar_t__ UnevenSpanSupport; } ;
struct MR_LD_RAID {int rowSize; } ;
struct MR_DRV_RAID_MAP_ALL {int dummy; } ;
struct LD_LOAD_BALANCE_INFO {scalar_t__* last_accessed_block; int /*<<< orphan*/ * scsi_pending_cmds; } ;
struct IO_REQUEST_INFO {scalar_t__ ldStartBlock; int numBlocks; int span_arm; int pd_after_lb; int /*<<< orphan*/  ldTgtId; } ;

/* Variables and functions */
 scalar_t__ ABS_DIFF (scalar_t__,scalar_t__) ; 
 int MR_ArPdGet (int,int,struct MR_DRV_RAID_MAP_ALL*) ; 
 scalar_t__ MR_DEVHANDLE_INVALID ; 
 struct MR_LD_RAID* MR_LdRaidGet (scalar_t__,struct MR_DRV_RAID_MAP_ALL*) ; 
 int MR_LdSpanArrayGet (scalar_t__,int,struct MR_DRV_RAID_MAP_ALL*) ; 
 scalar_t__ MR_PdDevHandleGet (int,struct MR_DRV_RAID_MAP_ALL*) ; 
 scalar_t__ MR_TargetIdToLdGet (int /*<<< orphan*/ ,struct MR_DRV_RAID_MAP_ALL*) ; 
 int RAID_CTX_SPANARM_ARM_MASK ; 
 int RAID_CTX_SPANARM_SPAN_MASK ; 
 int RAID_CTX_SPANARM_SPAN_SHIFT ; 
 int SPAN_ROW_SIZE (struct MR_DRV_RAID_MAP_ALL*,scalar_t__,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ lb_pending_cmds ; 

u8 megasas_get_best_arm_pd(struct megasas_instance *instance,
			   struct LD_LOAD_BALANCE_INFO *lbInfo,
			   struct IO_REQUEST_INFO *io_info,
			   struct MR_DRV_RAID_MAP_ALL *drv_map)
{
	struct MR_LD_RAID  *raid;
	u16	pd1_dev_handle;
	u16     pend0, pend1, ld;
	u64     diff0, diff1;
	u8      bestArm, pd0, pd1, span, arm;
	u32     arRef, span_row_size;

	u64 block = io_info->ldStartBlock;
	u32 count = io_info->numBlocks;

	span = ((io_info->span_arm & RAID_CTX_SPANARM_SPAN_MASK)
			>> RAID_CTX_SPANARM_SPAN_SHIFT);
	arm = (io_info->span_arm & RAID_CTX_SPANARM_ARM_MASK);

	ld = MR_TargetIdToLdGet(io_info->ldTgtId, drv_map);
	raid = MR_LdRaidGet(ld, drv_map);
	span_row_size = instance->UnevenSpanSupport ?
			SPAN_ROW_SIZE(drv_map, ld, span) : raid->rowSize;

	arRef = MR_LdSpanArrayGet(ld, span, drv_map);
	pd0 = MR_ArPdGet(arRef, arm, drv_map);
	pd1 = MR_ArPdGet(arRef, (arm + 1) >= span_row_size ?
		(arm + 1 - span_row_size) : arm + 1, drv_map);

	/* Get PD1 Dev Handle */

	pd1_dev_handle = MR_PdDevHandleGet(pd1, drv_map);

	if (pd1_dev_handle == MR_DEVHANDLE_INVALID) {
		bestArm = arm;
	} else {
		/* get the pending cmds for the data and mirror arms */
		pend0 = atomic_read(&lbInfo->scsi_pending_cmds[pd0]);
		pend1 = atomic_read(&lbInfo->scsi_pending_cmds[pd1]);

		/* Determine the disk whose head is nearer to the req. block */
		diff0 = ABS_DIFF(block, lbInfo->last_accessed_block[pd0]);
		diff1 = ABS_DIFF(block, lbInfo->last_accessed_block[pd1]);
		bestArm = (diff0 <= diff1 ? arm : arm ^ 1);

		/* Make balance count from 16 to 4 to
		 *  keep driver in sync with Firmware
		 */
		if ((bestArm == arm && pend0 > pend1 + lb_pending_cmds)  ||
		    (bestArm != arm && pend1 > pend0 + lb_pending_cmds))
			bestArm ^= 1;

		/* Update the last accessed block on the correct pd */
		io_info->span_arm =
			(span << RAID_CTX_SPANARM_SPAN_SHIFT) | bestArm;
		io_info->pd_after_lb = (bestArm == arm) ? pd0 : pd1;
	}

	lbInfo->last_accessed_block[io_info->pd_after_lb] = block + count - 1;
	return io_info->pd_after_lb;
}