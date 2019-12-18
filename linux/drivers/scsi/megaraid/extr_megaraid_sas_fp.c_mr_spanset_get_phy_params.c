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
typedef  int /*<<< orphan*/  u64 ;
typedef  unsigned int u32 ;
typedef  scalar_t__ u16 ;
struct megasas_instance {scalar_t__ adapter_type; struct fusion_context* ctrl_context; } ;
struct fusion_context {int dummy; } ;
struct RAID_CONTEXT_G35 {int span_arm; } ;
struct RAID_CONTEXT {int span_arm; int /*<<< orphan*/  reg_lock_flags; } ;
struct MR_LD_RAID {int level; scalar_t__ regTypeReqOnRead; } ;
struct MR_DRV_RAID_MAP_ALL {int dummy; } ;
struct IO_REQUEST_INFO {int pd_interface; int start_span; int span_arm; unsigned int pd_after_lb; void* r1_alt_dev_handle; int /*<<< orphan*/  isRead; int /*<<< orphan*/  start_row; void* devHandle; int /*<<< orphan*/  pdBlock; } ;
typedef  void* __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  startBlk; } ;

/* Variables and functions */
 scalar_t__ INVADER_SERIES ; 
 unsigned int MR_ArPdGet (unsigned int,int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int /*<<< orphan*/  MR_DEVHANDLE_INVALID ; 
 struct MR_LD_RAID* MR_LdRaidGet (unsigned int,struct MR_DRV_RAID_MAP_ALL*) ; 
 unsigned int MR_LdSpanArrayGet (unsigned int,int,struct MR_DRV_RAID_MAP_ALL*) ; 
 TYPE_1__* MR_LdSpanPtrGet (unsigned int,int,struct MR_DRV_RAID_MAP_ALL*) ; 
 unsigned int MR_PD_INVALID ; 
 void* MR_PdDevHandleGet (unsigned int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int MR_PdInterfaceTypeGet (unsigned int,struct MR_DRV_RAID_MAP_ALL*) ; 
 int RAID_CTX_SPANARM_SPAN_SHIFT ; 
 int /*<<< orphan*/  REGION_TYPE_EXCLUSIVE ; 
 scalar_t__ REGION_TYPE_UNUSED ; 
 unsigned int SPAN_ROW_SIZE (struct MR_DRV_RAID_MAP_ALL*,unsigned int,int) ; 
 scalar_t__ THUNDERBOLT_SERIES ; 
 scalar_t__ VENTURA_SERIES ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int get_arm (struct megasas_instance*,unsigned int,int,int /*<<< orphan*/ ,struct MR_DRV_RAID_MAP_ALL*) ; 
 unsigned int get_arm_from_strip (struct megasas_instance*,unsigned int,int /*<<< orphan*/ ,struct MR_DRV_RAID_MAP_ALL*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int mega_mod64 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static u8 mr_spanset_get_phy_params(struct megasas_instance *instance, u32 ld,
		u64 stripRow, u16 stripRef, struct IO_REQUEST_INFO *io_info,
		struct RAID_CONTEXT *pRAID_Context,
		struct MR_DRV_RAID_MAP_ALL *map)
{
	struct MR_LD_RAID  *raid = MR_LdRaidGet(ld, map);
	u32     pd, arRef, r1_alt_pd;
	u8      physArm, span;
	u64     row;
	u8	retval = true;
	u64	*pdBlock = &io_info->pdBlock;
	__le16	*pDevHandle = &io_info->devHandle;
	u8	*pPdInterface = &io_info->pd_interface;
	u32	logArm, rowMod, armQ, arm;
	struct fusion_context *fusion;

	fusion = instance->ctrl_context;
	*pDevHandle = cpu_to_le16(MR_DEVHANDLE_INVALID);

	/*Get row and span from io_info for Uneven Span IO.*/
	row	    = io_info->start_row;
	span	    = io_info->start_span;


	if (raid->level == 6) {
		logArm = get_arm_from_strip(instance, ld, stripRow, map);
		if (logArm == -1U)
			return false;
		rowMod = mega_mod64(row, SPAN_ROW_SIZE(map, ld, span));
		armQ = SPAN_ROW_SIZE(map, ld, span) - 1 - rowMod;
		arm = armQ + 1 + logArm;
		if (arm >= SPAN_ROW_SIZE(map, ld, span))
			arm -= SPAN_ROW_SIZE(map, ld, span);
		physArm = (u8)arm;
	} else
		/* Calculate the arm */
		physArm = get_arm(instance, ld, span, stripRow, map);
	if (physArm == 0xFF)
		return false;

	arRef       = MR_LdSpanArrayGet(ld, span, map);
	pd          = MR_ArPdGet(arRef, physArm, map);

	if (pd != MR_PD_INVALID) {
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
			physArm = physArm + 1;
			pd = MR_ArPdGet(arRef, physArm, map);
			if (pd != MR_PD_INVALID) {
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