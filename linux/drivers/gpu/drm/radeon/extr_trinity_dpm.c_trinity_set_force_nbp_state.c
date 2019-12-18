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
typedef  int u32 ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int FORCE_NBPS1 (int) ; 
 int FORCE_NBPS1_MASK ; 
 int RREG32_SMC (int) ; 
 int SMU_SCLK_DPM_STATE_0_CNTL_3 ; 
 int TRINITY_SIZEOF_DPM_STATE_TABLE ; 
 int /*<<< orphan*/  WREG32_SMC (int,int) ; 

__attribute__((used)) static void trinity_set_force_nbp_state(struct radeon_device *rdev,
					u32 index, u32 force_nbp_state)
{
	u32 value;
	u32 ix = index * TRINITY_SIZEOF_DPM_STATE_TABLE;

	value = RREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_3 + ix);
	value &= ~FORCE_NBPS1_MASK;
	value |= FORCE_NBPS1(force_nbp_state);
	WREG32_SMC(SMU_SCLK_DPM_STATE_0_CNTL_3 + ix, value);
}