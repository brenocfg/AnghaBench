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
typedef  int u64 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct megasas_instance {scalar_t__ adapter_type; struct fusion_context* ctrl_context; } ;
struct fusion_context {int dummy; } ;
struct RAID_CONTEXT_G35 {int span_arm; } ;
struct RAID_CONTEXT {int span_arm; int /*<<< orphan*/  reg_lock_flags; } ;
struct MR_LD_RAID {scalar_t__ rowDataSize; int level; scalar_t__ rowSize; scalar_t__ modFactor; int spanDepth; int stripeShift; scalar_t__ regTypeReqOnRead; } ;
struct MR_DRV_RAID_MAP_ALL {int dummy; } ;
struct IO_REQUEST_INFO {int pdBlock; int pd_interface; int span_arm; int pd_after_lb; void* r1_alt_dev_handle; int /*<<< orphan*/  isRead; void* devHandle; } ;
typedef  void* __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  startBlk; } ;

/* Variables and functions */
 scalar_t__ INVADER_SERIES ; 
 int MR_ArPdGet (int,int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int /*<<< orphan*/  MR_DEVHANDLE_INVALID ; 
 scalar_t__ MR_GetSpanBlock (int,int,int*,struct MR_DRV_RAID_MAP_ALL*) ; 
 int MR_LdDataArmGet (int,int,struct MR_DRV_RAID_MAP_ALL*) ; 
 struct MR_LD_RAID* MR_LdRaidGet (int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int MR_LdSpanArrayGet (int,int,struct MR_DRV_RAID_MAP_ALL*) ; 
 TYPE_1__* MR_LdSpanPtrGet (int,int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int MR_PD_INVALID ; 
 void* MR_PdDevHandleGet (int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int MR_PdInterfaceTypeGet (int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int RAID_CTX_SPANARM_SPAN_SHIFT ; 
 int /*<<< orphan*/  REGION_TYPE_EXCLUSIVE ; 
 scalar_t__ REGION_TYPE_UNUSED ; 
 int SPAN_INVALID ; 
 scalar_t__ THUNDERBOLT_SERIES ; 
 scalar_t__ VENTURA_SERIES ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int mega_div64_32 (int,scalar_t__) ; 
 int mega_mod64 (int,scalar_t__) ; 

u8 MR_GetPhyParams(struct megasas_instance *instance, u32 ld, u64 stripRow,
		u16 stripRef, struct IO_REQUEST_INFO *io_info,
		struct RAID_CONTEXT *pRAID_Context,
		struct MR_DRV_RAID_MAP_ALL *map)
{
	struct MR_LD_RAID  *raid = MR_LdRaidGet(ld, map);
	u32         pd, arRef, r1_alt_pd;
	u8          physArm, span;
	u64         row;
	u8	    retval = true;
	u64	    *pdBlock = &io_info->pdBlock;
	__le16	    *pDevHandle = &io_info->devHandle;
	u8	    *pPdInterface = &io_info->pd_interface;
	struct fusion_context *fusion;

	fusion = instance->ctrl_context;
	*pDevHandle = cpu_to_le16(MR_DEVHANDLE_INVALID);

	row =  mega_div64_32(stripRow, raid->rowDataSize);

	if (raid->level == 6) {
		/* logical arm within row */
		u32 logArm =  mega_mod64(stripRow, raid->rowDataSize);
		u32 rowMod, armQ, arm;

		if (raid->rowSize == 0)
			return false;
		/* get logical row mod */
		rowMod = mega_mod64(row, raid->rowSize);
		armQ = raid->rowSize-1-rowMod; /* index of Q drive */
		arm = armQ+1+logArm; /* data always logically follows Q */
		if (arm >= raid->rowSize) /* handle wrap condition */
			arm -= raid->rowSize;
		physArm = (u8)arm;
	} else  {
		if (raid->modFactor == 0)
			return false;
		physArm = MR_LdDataArmGet(ld,  mega_mod64(stripRow,
							  raid->modFactor),
					  map);
	}

	if (raid->spanDepth == 1) {
		span = 0;
		*pdBlock = row << raid->stripeShift;
	} else {
		span = (u8)MR_GetSpanBlock(ld, row, pdBlock, map);
		if (span == SPAN_INVALID)
			return false;
	}

	/* Get the array on which this span is present */
	arRef       = MR_LdSpanArrayGet(ld, span, map);
	pd          = MR_ArPdGet(arRef, physArm, map); /* Get the pd */

	if (pd != MR_PD_INVALID) {
		/* Get dev handle from Pd. */
		*pDevHandle = MR_PdDevHandleGet(pd, map);
		*pPdInterface = MR_PdInterfaceTypeGet(pd, map);
		/* get second pd also for raid 1/10 fast path writes*/
		if ((instance->adapter_type >= VENTURA_SERIES) &&
		    (raid->level == 1) &&
		    !io_info->isRead) {
			r1_alt_pd = MR_ArPdGet(arRef, physArm + 1, map);
			if (r1_alt_pd != MR_PD_INVALID)
				io_info->r1_alt_dev_handle =
					MR_PdDevHandleGet(r1_alt_pd, map);
		}
	} else {
		if ((raid->level >= 5) &&
			((instance->adapter_type == THUNDERBOLT_SERIES)  ||
			((instance->adapter_type == INVADER_SERIES) &&
			(raid->regTypeReqOnRead != REGION_TYPE_UNUSED))))
			pRAID_Context->reg_lock_flags = REGION_TYPE_EXCLUSIVE;
		else if (raid->level == 1) {
			/* Get alternate Pd. */
			physArm = physArm + 1;
			pd = MR_ArPdGet(arRef, physArm, map);
			if (pd != MR_PD_INVALID) {
				/* Get dev handle from Pd */
				*pDevHandle = MR_PdDevHandleGet(pd, map);
				*pPdInterface = MR_PdInterfaceTypeGet(pd, map);
			}
		}
	}

	*pdBlock += stripRef + le64_to_cpu(MR_LdSpanPtrGet(ld, span, map)->startBlk);
	if (instance->adapter_type >= VENTURA_SERIES) {
		((struct RAID_CONTEXT_G35 *)pRAID_Context)->span_arm =
				(span << RAID_CTX_SPANARM_SPAN_SHIFT) | physArm;
		io_info->span_arm =
				(span << RAID_CTX_SPANARM_SPAN_SHIFT) | physArm;
	} else {
		pRAID_Context->span_arm =
			(span << RAID_CTX_SPANARM_SPAN_SHIFT) | physArm;
		io_info->span_arm = pRAID_Context->span_arm;
	}
	io_info->pd_after_lb = pd;
	return retval;
}