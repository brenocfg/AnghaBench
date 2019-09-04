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
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int vf_sbs_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int BP_FUNC (struct bnx2x*) ; 
 TYPE_1__* BP_VFDB (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int IGU_FID_ENCODE_IS_PF ; 
 int IGU_FID_PF_NUM_MASK ; 
 int IGU_FID_VF_NUM_MASK ; 
 scalar_t__ IGU_REG_MAPPING_MEMORY ; 
 int /*<<< orphan*/  IGU_REG_MAPPING_MEMORY_FID ; 
 int IGU_REG_MAPPING_MEMORY_SIZE ; 
 int IGU_REG_MAPPING_MEMORY_VALID ; 
 int /*<<< orphan*/  IGU_REG_MAPPING_MEMORY_VECTOR ; 
 int REG_RD (struct bnx2x*,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_vf_set_igu_info (struct bnx2x*,int,int) ; 

__attribute__((used)) static int
bnx2x_get_vf_igu_cam_info(struct bnx2x *bp)
{
	int sb_id;
	u32 val;
	u8 fid, current_pf = 0;

	/* IGU in normal mode - read CAM */
	for (sb_id = 0; sb_id < IGU_REG_MAPPING_MEMORY_SIZE; sb_id++) {
		val = REG_RD(bp, IGU_REG_MAPPING_MEMORY + sb_id * 4);
		if (!(val & IGU_REG_MAPPING_MEMORY_VALID))
			continue;
		fid = GET_FIELD((val), IGU_REG_MAPPING_MEMORY_FID);
		if (fid & IGU_FID_ENCODE_IS_PF)
			current_pf = fid & IGU_FID_PF_NUM_MASK;
		else if (current_pf == BP_FUNC(bp))
			bnx2x_vf_set_igu_info(bp, sb_id,
					      (fid & IGU_FID_VF_NUM_MASK));
		DP(BNX2X_MSG_IOV, "%s[%d], igu_sb_id=%d, msix=%d\n",
		   ((fid & IGU_FID_ENCODE_IS_PF) ? "PF" : "VF"),
		   ((fid & IGU_FID_ENCODE_IS_PF) ? (fid & IGU_FID_PF_NUM_MASK) :
		   (fid & IGU_FID_VF_NUM_MASK)), sb_id,
		   GET_FIELD((val), IGU_REG_MAPPING_MEMORY_VECTOR));
	}
	DP(BNX2X_MSG_IOV, "vf_sbs_pool is %d\n", BP_VFDB(bp)->vf_sbs_pool);
	return BP_VFDB(bp)->vf_sbs_pool;
}