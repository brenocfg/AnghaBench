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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct megasas_instance {int dummy; } ;
struct TYPE_2__ {int r56_arm_map; } ;
struct RAID_CONTEXT_G35 {int span_arm; int raid_flags; TYPE_1__ flow_specific; int /*<<< orphan*/  reg_lock_row_lba; } ;
struct MR_LD_RAID {int rowDataSize; int rowSize; int spanDepth; int level; } ;
struct MR_DRV_RAID_MAP_ALL {int dummy; } ;
struct IO_REQUEST_INFO {int pdBlock; } ;
typedef  int s8 ;

/* Variables and functions */
 scalar_t__ MR_GetSpanBlock (int /*<<< orphan*/ ,int,int*,struct MR_DRV_RAID_MAP_ALL*) ; 
 struct MR_LD_RAID* MR_LdRaidGet (int /*<<< orphan*/ ,struct MR_DRV_RAID_MAP_ALL*) ; 
 int MR_RAID_CTX_RAID_FLAGS_IO_SUB_TYPE_SHIFT ; 
 int MR_RAID_FLAGS_IO_SUB_TYPE_R56_DIV_OFFLOAD ; 
 int RAID_CTX_R56_LOG_ARM_SHIFT ; 
 int RAID_CTX_R56_P_ARM_SHIFT ; 
 int RAID_CTX_SPANARM_SPAN_SHIFT ; 
 int SPAN_INVALID ; 
 int /*<<< orphan*/  cpu_to_le16s (int*) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int mega_div64_32 (int,int) ; 
 int mega_mod64 (int,int) ; 

__attribute__((used)) static void mr_get_phy_params_r56_rmw(struct megasas_instance *instance,
			    u32 ld, u64 stripNo,
			    struct IO_REQUEST_INFO *io_info,
			    struct RAID_CONTEXT_G35 *pRAID_Context,
			    struct MR_DRV_RAID_MAP_ALL *map)
{
	struct MR_LD_RAID  *raid = MR_LdRaidGet(ld, map);
	u8          span, dataArms, arms, dataArm, logArm;
	s8          rightmostParityArm, PParityArm;
	u64         rowNum;
	u64 *pdBlock = &io_info->pdBlock;

	dataArms = raid->rowDataSize;
	arms = raid->rowSize;

	rowNum =  mega_div64_32(stripNo, dataArms);
	/* parity disk arm, first arm is 0 */
	rightmostParityArm = (arms - 1) - mega_mod64(rowNum, arms);

	/* logical arm within row */
	logArm =  mega_mod64(stripNo, dataArms);
	/* physical arm for data */
	dataArm = mega_mod64((rightmostParityArm + 1 + logArm), arms);

	if (raid->spanDepth == 1) {
		span = 0;
	} else {
		span = (u8)MR_GetSpanBlock(ld, rowNum, pdBlock, map);
		if (span == SPAN_INVALID)
			return;
	}

	if (raid->level == 6) {
		/* P Parity arm, note this can go negative adjust if negative */
		PParityArm = (arms - 2) - mega_mod64(rowNum, arms);

		if (PParityArm < 0)
			PParityArm += arms;

		/* rightmostParityArm is P-Parity for RAID 5 and Q-Parity for RAID */
		pRAID_Context->flow_specific.r56_arm_map = rightmostParityArm;
		pRAID_Context->flow_specific.r56_arm_map |=
				    (u16)(PParityArm << RAID_CTX_R56_P_ARM_SHIFT);
	} else {
		pRAID_Context->flow_specific.r56_arm_map |=
				    (u16)(rightmostParityArm << RAID_CTX_R56_P_ARM_SHIFT);
	}

	pRAID_Context->reg_lock_row_lba = cpu_to_le64(rowNum);
	pRAID_Context->flow_specific.r56_arm_map |=
				   (u16)(logArm << RAID_CTX_R56_LOG_ARM_SHIFT);
	cpu_to_le16s(&pRAID_Context->flow_specific.r56_arm_map);
	pRAID_Context->span_arm = (span << RAID_CTX_SPANARM_SPAN_SHIFT) | dataArm;
	pRAID_Context->raid_flags = (MR_RAID_FLAGS_IO_SUB_TYPE_R56_DIV_OFFLOAD <<
				    MR_RAID_CTX_RAID_FLAGS_IO_SUB_TYPE_SHIFT);

	return;
}