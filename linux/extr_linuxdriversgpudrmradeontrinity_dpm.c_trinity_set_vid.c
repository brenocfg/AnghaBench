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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  vid_mapping_table; } ;
struct trinity_power_info {TYPE_1__ sys_info; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int LVRT (int /*<<< orphan*/ ) ; 
 int LVRT_MASK ; 
 int RREG32_SMC (int) ; 
 int SMU_SCLK_DPM_STATE_0_CNTL_0 ; 
 int TRINITY_SIZEOF_DPM_STATE_TABLE ; 
 int VID (int) ; 
 int VID_MASK ; 
 int /*<<< orphan*/  WREG32_SMC (int,int) ; 
 int sumo_convert_vid2_to_vid7 (struct radeon_device*,int /*<<< orphan*/ *,int) ; 
 struct trinity_power_info* trinity_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void trinity_set_vid(struct radeon_device *rdev, u32 index, u32 vid)
{
	struct trinity_power_info *pi = trinity_get_pi(rdev);
	u32 vid_7bit = sumo_convert_vid2_to_vid7(rdev, &pi->sys_info.vid_mapping_table, vid);
	u32 value;
	u32 ix = index * TRINITY_SIZEOF_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix);
	value &= ~VID_MASK;
	value |= VID(vid_7bit);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix, value);

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix);
	value &= ~LVRT_MASK;
	value |= LVRT(0);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_0 + ix, value);
}